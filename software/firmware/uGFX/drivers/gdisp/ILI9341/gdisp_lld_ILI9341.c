/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"
#include <stdio.h>

#if GFX_USE_GDISP

#if defined(GDISP_SCREEN_HEIGHT) || defined(GDISP_SCREEN_HEIGHT)
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GDISP: This low level driver does not support setting a screen size. It is being ignored.")
	#endif
	#undef GDISP_SCREEN_WIDTH
	#undef GDISP_SCREEN_HEIGHT
#endif

#define GDISP_DRIVER_VMT			GDISPVMT_ILI9341
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "board_ILI9341.h"


/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		320
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		240
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

#include "ILI9341.h"

#define DISPLAY_BUF GDISP_SCREEN_HEIGHT

static uint16_t pixelbuf[DISPLAY_BUF];
static int pixelpos;

static int saved_x;
static int saved_y;
static int saved_cx;
static int saved_cy;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define dummy_read(g)				{ volatile uint16_t dummy; dummy = read_data(g); (void) dummy; }
#define write_reg(g, reg, data)		{ write_index(g, reg); write_data(g, data); }
#define write_data16(g, data)		{ write_data(g, data >> 8); write_data(g, (uint8_t)data); }
#define delay(us)					gfxSleepMicroseconds(us)
#define delayms(ms)					gfxSleepMilliseconds(ms)

static void set_viewport(GDisplay *g) {

	/*
	 * The ILI9341 is very inefficient when it comes to drawing
	 * single pixels: you need to constantly update the viewport.
	 * We want to optimize this as much as possible. It turns out
	 * that there are many cases where either the column address (0x2A)
	 * or the page address (0x2B) stay the same. If we detect this,
	 * we can avoid several DMA transfers.
	 */

	if (saved_cx != g->p.cx || saved_x != g->p.x) {
		saved_x = g->p.x;
		saved_cx = g->p.cx;
		write_index(g, 0x2A);
		pixelbuf[0] = __builtin_bswap16 (g->p.x);
		pixelbuf[1] = __builtin_bswap16 (g->p.x + g->p.cx - 1);
		spiSend (&SPI_BUS, 4, pixelbuf);
	}

	if (saved_cy != g->p.cy || saved_y != g->p.y) {
		saved_y = g->p.y;
		saved_cy = g->p.cy;
		write_index(g, 0x2B);
		pixelbuf[0] = __builtin_bswap16 (g->p.y);
		pixelbuf[1] = __builtin_bswap16 (g->p.y + g->p.cy - 1);
		spiSend (&SPI_BUS, 4, pixelbuf);
	}

	return;
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {
	// No private area for this controller
	g->priv = 0;

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, TRUE);
	gfxSleepMilliseconds(20);
	setpin_reset(g, FALSE);
	gfxSleepMilliseconds(20);

	// Get the bus for the following initialisation commands
	acquire_bus(g);

	write_index(g, 0x01); //software reset
	gfxSleepMilliseconds(5);
	write_index(g, 0x28);
	// display off
	//---------------------------------------------------------
	// magic?
	write_index(g, 0xcf);
	write_data(g, 0x00);
	write_data(g, 0x83);
	write_data(g, 0x30);

	write_index(g, 0xed);
	write_data(g, 0x64);
	write_data(g, 0x03);
	write_data(g, 0x12);
	write_data(g, 0x81);
	write_index(g, 0xe8);
	write_data(g, 0x85);
	write_data(g, 0x01);
	write_data(g, 0x79);
	write_index(g, 0xcb);
	write_data(g, 0x39);
	write_data(g, 0x2c);
	write_data(g, 0x00);
	write_data(g, 0x34);
	write_data(g, 0x02);
	write_index(g, 0xf7);
	write_data(g, 0x20);
	write_index(g, 0xea);
	write_data(g, 0x00);
	write_data(g, 0x00);
	//------------power control------------------------------
	write_index(g, 0xc0); //power control
	write_data(g, 0x26);
	write_index(g, 0xc1); //power control
	write_data(g, 0x11);
	//--------------VCOM
	write_index(g, 0xc5); //vcom control
	write_data(g, 0x35);//35
	write_data(g, 0x3e);//3E
	write_index(g, 0xc7); //vcom control
	write_data(g, 0xbe); // 0x94
	//------------memory access control------------------------
	write_index(g, 0x36);
	// memory access control
	write_data(g, 0x48); //0048 my,mx,mv,ml,BGR,mh,0.0
	write_index(g, 0x3a); // pixel format set
	write_data(g, 0x55);//16bit /pixel
	//----------------- frame rate------------------------------
	write_index(g, 0xb1);
	// frame rate
	write_data(g, 0x00);
	/* Set the refresh rate to max (119 fps) for cleaner scrolling */
	write_data(g, 0x10);
	//----------------Gamma---------------------------------
	write_index(g, 0xf2); // 3Gamma Function Disable
	write_data(g, 0x08);
	write_index(g, 0x26);
	write_data(g, 0x01); // gamma set 4 gamma curve 01/02/04/08

	write_index(g, 0xE0); //positive gamma correction
	write_data(g, 0x1f);
	write_data(g, 0x1a);
	write_data(g, 0x18);
	write_data(g, 0x0a);
	write_data(g, 0x0f);
	write_data(g, 0x06);
	write_data(g, 0x45);
	write_data(g, 0x87);
	write_data(g, 0x32);
	write_data(g, 0x0a);
	write_data(g, 0x07);
	write_data(g, 0x02);
	write_data(g, 0x07);
	write_data(g, 0x05);
	write_data(g, 0x00);
	write_index(g, 0xE1); //negamma correction
	write_data(g, 0x00);
	write_data(g, 0x25);
	write_data(g, 0x27);
	write_data(g, 0x05);
	write_data(g, 0x10);
	write_data(g, 0x09);
	write_data(g, 0x3a);
	write_data(g, 0x78);
	write_data(g, 0x4d);
	write_data(g, 0x05);
	write_data(g, 0x18);
	write_data(g, 0x0d);
	write_data(g, 0x38);
	write_data(g, 0x3a);
	write_data(g, 0x1f);
	//--------------ddram ---------------------
	write_index(g, 0x2a);
	// column set
	// size = 239
	write_data(g, 0x00);
	write_data(g, 0x00);
	write_data(g, 0x00);
	write_data(g, 0xEF);
	write_index(g, 0x2b);
	// page address set
	// size = 319
	write_data(g, 0x00);
	write_data(g, 0x00);
	write_data(g, 0x01);
	write_data(g, 0x3F);
	// write_index(g, 0x34);
	//write_index(g, 0x35);
	// tearing effect off
	// tearing effect on
	// write_index(g, 0xb4); // display inversion
	// write_data(g, 0x00);
	write_index(g, 0xb7); //entry mode set
	write_data(g, 0x07);
	//-----------------display---------------------
	write_index(g, 0xb6);
	// display function control
	write_data(g, 0x0a);
	write_data(g, 0x82);
	write_data(g, 0x27);
	write_data(g, 0x00);
	write_index(g, 0x11); //sleep out
	gfxSleepMilliseconds(100);
	write_index(g, 0x29); // display on
	gfxSleepMilliseconds(100);

    // Finish Init
    post_init_board(g);

 	// Release the bus
	release_bus(g);
	
	/* Turn on the back-light */
	set_backlight(g, GDISP_INITIAL_BACKLIGHT);

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = GDISP_ROTATE_0;
	g->g.Powermode = powerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return TRUE;
}

#if GDISP_HARDWARE_STREAM_WRITE
	LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
		acquire_bus(g);

		/*
		 * If the x and y coordinates are the special
		 * values -1/-1, then leave the viewport settings
		 * as they are. This is a special mode for the
		 * video player driver, which constantly streams
		 * data to the same viewport coordinates. The only
		 * thing it needs is the special mode and mutual
		 * exclusion handling so that it shares the SPI
		 * bus properly with the SD card and touch controller
		 * drivers.
		 */

		pixelpos = 0;
		if (g->p.x != -1 && g->p.y != -1) {
			set_viewport(g);
			write_index(g, 0x2C);
		}
		return;
	}
	LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
		pixelbuf[pixelpos] = g->p.color;
		pixelpos++;
		if (pixelpos == DISPLAY_BUF) {
			spiSend (&SPI_BUS, pixelpos * 2 , pixelbuf);
			pixelpos = 0;
		}
		return;
	}
	LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
		if (pixelpos != 0) {
			spiSend (&SPI_BUS, pixelpos * 2 , pixelbuf);
			pixelpos = 0;
		}
		release_bus(g);
	}
#endif

#if GDISP_HARDWARE_STREAM_READ
	LLDSPEC	void gdisp_lld_read_start(GDisplay *g) {
		uint8_t dummy;
		acquire_bus(g);
		set_viewport(g);
		write_index(g, 0x2E);
		setreadmode(g);
		spiReceive (&SPI_BUS, 1, &dummy);
	}
	/*
	 * The ILI9341 controller stores pixels in its internal memory
	 * using 3 bytes (24 bits): one byte each for red, green and blue
	 * color data. When you write pixels into the display in 16-bit
	 * RGB565 format, the hardware internally splits out the RGB data
	 * from that 16-bit block into its internal 24-bit pixel RAM.
	 * Unfortunately it does not provide a way to read data back out
	 * with the opposite translation: you can read the pixel RAM,
	 * but you have to read it in 3-byte RGB format, not 16-bit
	 * RGB565 format. Once you get the bytes, you then have to
	 * translate them back into 16-bit RGB565 form in software.
	 * This is not terribly fast, so you should avoid doing it for
	 * large display regions.
	 *
	 * Note that the ILI9341 supports two color modes: 16-bit
	 * (with 64K colors) and 18-bit (with 256K colors). With 18-bit
	 * mode, you get 6 bits each for red, green and blue color data.
	 * In the internal graphics RAM, each byte of RGB color data
	 * maps directly to the 6-bits of RGB data supplied when drawing.
	 * We have to be careful to reverse this when trandlating the
	 * data back.
	 */

	LLDSPEC	color_t gdisp_lld_read_color(GDisplay *g) {
		uint8_t		p[3];
		pixel_t		data;
		spiReceive (&SPI_BUS, 3, p);

		data = (p[0] >> 3) << 11;	/* Red */
		data |= p[1] << 3;		/* Green */
		data |= p[2] >> 3;		/* Blue */
		data = __builtin_bswap16 (data);

		return (data);
	}
	LLDSPEC	void gdisp_lld_read_stop(GDisplay *g) {
		/* Restore drawing mode */
		setwritemode(g);
		release_bus(g);
	}
#endif

#if GDISP_HARDWARE_BITFILLS
#if GDISP_PIXELFORMAT != GDISP_LLD_PIXELFORMAT
#error "GDISP: ILI9341: BitBlit is only available in RGB565 pixel format"
#endif
	LLDSPEC void gdisp_lld_blit_area(GDisplay *g) {
		const pixel_t *	buffer;
		coord_t		ycnt;

		buffer = (pixel_t *)g->p.ptr + g->p.x1 + g->p.y1 * g->p.x2;

		gdisp_lld_write_start (g);
		if (g->p.x2 == g->p.cx) {
			spiSend (&SPI_BUS, g->p.cx*g->p.cy * 2, buffer);
		} else {
			for (ycnt = g->p.cy; ycnt; ycnt--, buffer += g->p.x2)
				spiSend (&SPI_BUS, g->p.cy * 2, buffer);
		}
		gdisp_lld_write_stop (g);

		return;
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (powermode_t)g->p.ptr)
				return;
			switch((powermode_t)g->p.ptr) {
			case powerOff:
			case powerSleep:
			case powerDeepSleep:
				acquire_bus(g);
				write_reg(g, 0x0010, 0x0001);	/* enter sleep mode */
				release_bus(g);
				break;
			case powerOn:
				acquire_bus(g);
				write_reg(g, 0x0010, 0x0000);	/* leave sleep mode */
				release_bus(g);
				break;
			default:
				return;
			}
			g->g.Powermode = (powermode_t)g->p.ptr;
			return;

		case GDISP_CONTROL_ORIENTATION:
			if (g->g.Orientation == (orientation_t)g->p.ptr)
				return;
			switch((orientation_t)g->p.ptr) {
			case GDISP_ROTATE_0:
				acquire_bus(g);
				write_reg(g, 0x36, 0x48);	/* X and Y axes non-inverted */
				release_bus(g);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				break;
			case GDISP_ROTATE_90:
				acquire_bus(g);
				write_reg(g, 0x36, 0xE8);	/* Invert X and Y axes */
				release_bus(g);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				break;
			case GDISP_ROTATE_180:
				acquire_bus(g);
				write_reg(g, 0x36, 0x88);		/* X and Y axes non-inverted */
				release_bus(g);
				g->g.Height = GDISP_SCREEN_HEIGHT;
				g->g.Width = GDISP_SCREEN_WIDTH;
				break;
			case GDISP_ROTATE_270:
				acquire_bus(g);
				write_reg(g, 0x36, 0x28);	/* Invert X and Y axes */
				release_bus(g);
				g->g.Height = GDISP_SCREEN_WIDTH;
				g->g.Width = GDISP_SCREEN_HEIGHT;
				break;
			default:
				return;
			}
			g->g.Orientation = (orientation_t)g->p.ptr;
			return;

        case GDISP_CONTROL_BACKLIGHT:
            if ((unsigned)g->p.ptr > 100)
            	g->p.ptr = (void *)100;
            set_backlight(g, (unsigned)g->p.ptr);
            g->g.Backlight = (unsigned)g->p.ptr;
            return;

		//case GDISP_CONTROL_CONTRAST:
        default:
            return;
		}
	}
#endif

#endif /* GFX_USE_GDISP */
