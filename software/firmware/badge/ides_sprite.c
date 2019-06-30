
#include "ch.h"
#include "hal.h"

#include "orchard-app.h"
#include "string.h"
#include "fontlist.h"
#include "ides_gfx.h"
#include "scroll_lld.h"

#include "gfx.h"
#include "src/gdisp/gdisp_driver.h"

#include "ffconf.h"
#include "ff.h"

#include "async_io_lld.h"
#include "badge.h"
#include "ides_sprite.h"
#include <math.h>


/* stored default structs for initializing */
static const ISPBUF isbuf_default = {
  .buf = NULL,
  .x=0,
  .y=0,
  .xs=0,
  .ys=0
};

const ISPRITE isprite_default = {
  .type = ISP_DRAW_BLOCK,
  .bgtype = ISP_BG_DYNAMIC,
  .active = FALSE,
  .visible = FALSE,
  .bgcolor = HTML2COLOR(0x000000),
  .fname[0] = '\0'
};

typedef struct _4rect {
  RECT bx[4];
} FOUR_RECTS;

/* This is a library for simplifying sprite usage.
 * it supports
 *

ISPRITESYS *sl; // the sprite system.
ISPID s1, s2, s3; // ID numbers for each sprite.
int i=0;

// initialize a sprite system.  each ISPRITESYS does up to ISP_MAX_SPRITES at a time.
// you can create and destroy sprites all you want.
// it's often better to hide them if it's a re-used asset like a bullet.
// more than one spite system can be open and/or active at a time.
sl = isp_init();

// each new sprite has an ID number.
s1 = isp_make_sprite(sl); // make sprites.  none are drawn yet.
s2 = isp_make_sprite(sl); // they have no position or pixel data yet.
s3 = isp_make_sprite(sl);




  while()
  {
    i++;
    do_stuff();

    // pretend xpos/ypos are functions that return some position value
    // this is how you change the positional values for the sprites.
    isp_set_sprite_xy(sl, s1, xpos(i), ypos(i));
    isp_set_sprite_xy(sl, s2, xpos(i)+10, ypos(i)+10);
    isp_set_sprite_xy(sl, s3, xpos(i)+20, ypos(i)+20);


    // example of turning a sprite off.
    // maybe it's off screen, maybe it's not needed at the moment, but this is faster
    // than creating and destroying sprites constantly.
    if(should_s3_be_invisible())
    {
      hide_sprite(sl, s3);
    }
    else
    {
      show_sprite(sl, s3);
    }

    isp_draw_all_sprites(sl);
  }



  isp_shutdown(sl);  // close and free this sprite system.


*/




/*
static void release_bg_buffer(ISPRITESYS *iss, ISPID id)
{
  if( (id < ISP_MAX_SPRITES) &&
      (iss->list[id].active) )
  {
    if(NULL != iss->list[id].bg_buf.buf)
    {
      free(iss->list[id].bg_buf.buf);
      iss->list[id].bg_buf = isbuf_default;
    }
  }
}

*/
void print_rect(char *s, RECT r)
{
  printf("%s: x%d y%d xr %d yb%d\n", s, r.x, r.y, r.xr, r.yb);
}

bool_t do_rects_clip(RECT a, RECT b)
{
  /* check for lack-of-collision, and invet value.
   * so if leftside of box2 is to the right of of the right-side of box1, they can't be intersecting
   */

 return( !(b.x > a.xr ||
           b.xr < a.x ||
           b.y > a.yb || /* larger Y values are lower on screen */
           b.yb < a.y) );
}



RECT make_rect(ISPBUF ib)
{
  static RECT r;
  r.x  = ib.x;
  r.y  = ib.y;
  r.xr = ib.x + ib.xs;
  r.yb = ib.y + ib.ys;
  return(r);
}

/* makes a RECT that encmopases both passed ISBUF areas
*/
RECT make_bounding_rect(ISPBUF a, ISPBUF b)
{
  static RECT r;
  coord_t aa, bb;
  r.x  = (a.x < b.x) ? a.x : b.x;
  r.y  = (a.y < b.y) ? a.y : b.y;
  aa = a.x + a.xs;
  bb = b.x + b.xs;
  r.xr = (aa > bb) ? aa : bb;
  aa = a.y + a.ys;
  bb = b.y + b.ys;
  r.yb = (aa > bb) ? aa : bb;
  return(r);
}

FOUR_RECTS get_exposed_bg_boxes(ISPRITESYS *iss, ISPID id)
{
  RECT bg, sp, zro = { .x=0, .y=0, .xr=0, .yb=0 } ;
  FOUR_RECTS ret;
  coord_t lln, rln;

  if( (id < ISP_MAX_SPRITES) &&
      (iss->list[id].active) &&
      (iss->list[id].visible) &&
      (iss->list[id].bg_buf.xs > 0) &&
      (iss->list[id].sp_buf.xs > 0))
  {
    bg = make_rect(iss->list[id].bg_buf);
    sp = make_rect(iss->list[id].sp_buf);
    if(do_rects_clip(bg, sp))
    {
      /* there are up to 4 rectangles possible.  if the sprite is smaller than the BG, but wholy contained by it, all 4 are possible */


      /* is there left rec?
       * bg left edge is to the left of sprite left edge. */
      if(bg.x < sp.x)
      {
        ret.bx[0].x  = bg.x;
        ret.bx[0].xr = sp.x;
        ret.bx[0].y  = bg.y;
        ret.bx[0].yb = bg.yb;
        lln = sp.x;

      }
      else
      {
        lln=bg.x;
        ret.bx[0]=zro;
      }

      /* right? */
      if(bg.xr > sp.xr)
      {
        ret.bx[1].x  = sp.xr;
        ret.bx[1].xr = bg.xr;
        ret.bx[1].y  = bg.y;
        ret.bx[1].yb = bg.yb;
        rln = sp.xr;
      }
     else
     {
       rln = bg.xr;
       ret.bx[1] = zro;
     }

      /* top */
      if(bg.y < sp.y)
      {
        ret.bx[2].x  = lln;
        ret.bx[2].xr = rln;
        ret.bx[2].y  = bg.y;
        ret.bx[2].yb = sp.y;
      }
      else
      {
        ret.bx[2]=zro;
      }

      /* bot */
      if(bg.yb > sp.yb)
      {
        ret.bx[3].x  = lln;
        ret.bx[3].xr = rln;
        ret.bx[3].y  = sp.yb;
        ret.bx[3].yb = bg.yb;
      }
      else
      {
        ret.bx[3]=zro;
      }
    }
  }
  return(ret);
}



/* restores BG for visible sprites */
static void isp_restore_bg(ISPRITESYS *iss, ISPID id)
{
  FOUR_RECTS rects;
  int i;
  coord_t xs, ys;
  if( (id < ISP_MAX_SPRITES) &&
      (iss->list[id].active) &&
      (ISP_STAT_DIRTY_BOTH == iss->list[id].status)  )
  {
    switch(iss->list[id].bgtype)
    {
      /* add code to fill only the exposed parts of the BG rectangle.
       * don't need to fill areas that will be covered by the sprite
       */
      case ISP_BG_FIXEDCOLOR:
        rects = get_exposed_bg_boxes(iss, id);
        for(i=0; i< 4; i++)
        {
          if(rects.bx[i].xr > 0)
          {
            xs=rects.bx[i].xr - rects.bx[i].x;
            ys=rects.bx[i].yb - rects.bx[i].y;
            gdispFillArea(rects.bx[i].x,
                          rects.bx[i].y,
                          xs, ys,
                          iss->list[id].bgcolor);
          }
        }

/*        gdispFillArea(iss->list[id].bg_buf.x,
                      iss->list[id].bg_buf.y,
                      iss->list[id].bg_buf.xs,
                      iss->list[id].bg_buf.ys,
                      iss->list[id].bgcolor);
*/
        break;
      case ISP_BG_DYNAMIC:
        if( NULL != iss->list[id].bg_buf.buf)
        {
          putPixelBlock(iss->list[id].bg_buf.x,
                        iss->list[id].bg_buf.y,
                        iss->list[id].bg_buf.xs,
                        iss->list[id].bg_buf.ys,
                        iss->list[id].bg_buf.buf);
        }
        break;
    }
  }
}

/* returns true if it was able to capture.  false if not */
static bool_t isp_capture_bg(ISPRITESYS *iss, ISPID id)
{
  bool_t ret = FALSE;
  int size;
  if( (id < ISP_MAX_SPRITES) &&
      (iss->list[id].active) &&
      (iss->list[id].visible)  )
  {
    if(ISP_BG_DYNAMIC == iss->list[id].bgtype)
    {
      size = iss->list[id].sp_buf.xs * iss->list[id].sp_buf.ys * sizeof(pixel_t);
      /* create or realloc buffer space as needed */
      if((NULL == iss->list[id].bg_buf.buf))
      {
        iss->list[id].bg_buf.buf = (pixel_t *)malloc(size);
      }
      else if( (iss->list[id].bg_buf.xs != iss->list[id].sp_buf.xs) ||
          (iss->list[id].bg_buf.ys != iss->list[id].sp_buf.ys) )
      {
        iss->list[id].bg_buf.buf = (pixel_t *)realloc(iss->list[id].bg_buf.buf, size);
      }

      /* */
      getPixelBlock(iss->list[id].sp_buf.x, iss->list[id].sp_buf.y,
                    iss->list[id].sp_buf.xs, iss->list[id].sp_buf.ys,
                    iss->list[id].bg_buf.buf);
    }
    iss->list[id].bg_buf.x  = iss->list[id].sp_buf.x;
    iss->list[id].bg_buf.y  = iss->list[id].sp_buf.y;
    iss->list[id].bg_buf.xs = iss->list[id].sp_buf.xs;
    iss->list[id].bg_buf.ys = iss->list[id].sp_buf.ys;

    ret = TRUE;
  }
  return(ret);
}

/* */
static void isp_draw_sprite(ISPRITESYS *iss, ISPID id)
{
  if( (id < ISP_MAX_SPRITES) &&
      (iss->list[id].active) &&
      (iss->list[id].visible) &&
      (ISP_STAT_CLEAN != iss->list[id].status)  )
  {
    if( (ISP_DRAW_BLOCK == iss->list[id].type) || (ISP_DRAW_PTR == iss->list[id].type) )
    {
      if( NULL != iss->list[id].sp_buf.buf)
      {
        putPixelBlock(iss->list[id].sp_buf.x,
                      iss->list[id].sp_buf.y,
                      iss->list[id].sp_buf.xs,
                      iss->list[id].sp_buf.ys,
                      iss->list[id].sp_buf.buf);
      }
    }
    iss->list[id].status = ISP_STAT_CLEAN;
  }
}



/* this just initialises the sprite system, does not create any sprites.
 *
 */
ISPRITESYS *isp_init(void)
{
  ISPID i;
  ISPRITESYS *iss=NULL;
  iss = (ISPRITESYS *)malloc(sizeof(ISPRITESYS));
  if(NULL != iss)
  {
    for(i=0; i < ISP_MAX_SPRITES; i++)
    {
      iss->list[i] = isprite_default;
      iss->list[i].bg_buf = isbuf_default;
      iss->list[i].sp_buf = isbuf_default;
    }
  }
  return(iss);
}

static bool_t isp_is_live(ISPRITESYS *iss, ISPID id)
{
  return( (id < ISP_MAX_SPRITES) && (iss->list[id].active) );
}

bool_t isp_is_sprite_visible(ISPRITESYS *iss, ISPID id)
{
  return( (id < ISP_MAX_SPRITES) &&
           (iss->list[id].active) &&
           (iss->list[id].visible) );
}


/* overlap is TRUE if they have to overlap, not just touch to be considered a colision */
/* TODO: make overlap do something. have to adjust one set of values
  * currently it only detects overlaps, not touch
 */
bool_t isp_check_sprites_collision(ISPRITESYS *iss, ISPID id1, ISPID id2, bool_t overlap, bool_t drawtest)
{
  RECT a, b;
  bool_t ret=FALSE;


  /* only check if they are both active and sprite data */
  if( (iss->list[id1].active) &&
      (iss->list[id2].active) &&
      (iss->list[id1].sp_buf.xs > 0) &&
      (iss->list[id2].sp_buf.xs > 0) )
  {
    /* for overlap tests, boxes have to overlap to trigger a collision.
     * we have to subrtact 1 because if pos=0, and size=4, it takes up 4 pixels
     * starting at 0: 0,1,2,3.  0+4 == 4 which is not accurate for size of box.
     * consider 2 adjacent 4-pixel boxes occupying the following pixels:
     * [0123][4567]
     * 4 is the L side of box2, and 3 is the R side of box1.
     * they are outide of each other, no overlap.
     *
     * if overlap is false, boxes can be adjacent or overlapping to trigger a collsion.
     * in this case, we want the boxes to be 1 larger
     * for this mode, Those same boxes are now:
     * [01234][45678]
     * L2 and R1 both == 4, which triggers collision.
     */
    if(drawtest)
    {
      a = make_bounding_rect(iss->list[id1].sp_buf, iss->list[id1].bg_buf);
      b = make_bounding_rect(iss->list[id2].sp_buf, iss->list[id1].bg_buf);
    }
    else
    {
      a = make_rect(iss->list[id1].sp_buf);
      b = make_rect(iss->list[id2].sp_buf);
    }

    if(overlap)
    {
      a.xr -= 1;
      a.yb -= 1;
      b.xr -= 1;
      b.yb -= 1;

    }

   ret = do_rects_clip(a,b);
  }
  return(ret);
}



/* if one dirty sprite has any coordinate overlap with another sprite, they both must become dirty
 * if visible_only is true, it will only compare against visible sprites.
 * if it's false, it will compare against visible and invisible sprites.
 */
static void isp_flag_dirty_sprite_collisions(ISPRITESYS *iss, bool_t visible_only)
{
  int i,j,ii,jj, max=0;
  ISPID sl[ISP_MAX_SPRITES];

  /* first make the list of the ones we want to compare against */
  for(i=0; i < ISP_MAX_SPRITES; i++)
  {
    if( (iss->list[i].active) &&
        (!visible_only || iss->list[i].visible) )
    {
      sl[max]=i;
      max++;
    }
  }

  for(i=0; i < max; i++)
  {
    ii = sl[i];
    for(j=ii+1; j < max; j++)
    {
      jj = sl[j];
      /* if BG isn't dirty, check for overlap with other sprites and flag both as dirty_BG if they overlap
       * we don't know which one will move first, so BG needs to be restored for both so we get full, fresh BG collection
       * only check for collisions of at least one of them is dynamic BG.  if boith are solid color BG, they can collide all they want, and it won't affect BG redraw
       */
      if( ((ISP_STAT_DIRTY_BOTH != iss->list[ii].status) || (ISP_STAT_DIRTY_BOTH != iss->list[jj].status)) &&
          ( (ISP_BG_DYNAMIC == iss->list[ii].bgtype) || (ISP_BG_DYNAMIC == iss->list[jj].bgtype) ) &&
          isp_check_sprites_collision(iss, ii, jj, TRUE, TRUE) )
      {
        iss->list[ii].status = ISP_STAT_DIRTY_BOTH;
        iss->list[jj].status = ISP_STAT_DIRTY_BOTH;
      }
    }
  }
}





/* creates a spite, does not draw anything */
/* returns the ID number for the sprite, or ISP_MAX_SPRITES on fail */
ISPID isp_make_sprite(ISPRITESYS *iss)
{
  ISPID i;
  for(i=0; i < ISP_MAX_SPRITES; i++)
  {
    if(!isp_is_live(iss, i))
    {
      iss->list[i].visible = TRUE;
      iss->list[i].active = TRUE;
      iss->list[i].status = ISP_STAT_DIRTY_BOTH;
      break;
    }
  }
  return(i);
}




void isp_hide_sprite(ISPRITESYS *iss, ISPID id)
{
  if( (id < ISP_MAX_SPRITES) && (iss->list[id].visible) )
  {
    iss->list[id].status = ISP_STAT_DIRTY_BOTH; /* flag it so BG gets restored */
    iss->list[id].visible = FALSE;         /* flag it so it doesn't draw */
  }
}

void isp_show_sprite(ISPRITESYS *iss, ISPID id)
{
  if( (id < ISP_MAX_SPRITES) && (!iss->list[id].visible) )
  {
    iss->list[id].status = ISP_STAT_DIRTY_BOTH; /* flag it so BG gets captured */
    iss->list[id].visible = TRUE;         /* flag it so it does draw */
  }
}



/* todo: restore background before destroying */
/* this will immediately repaint the background */
void isp_destroy_sprite(ISPRITESYS *iss, ISPID id)
{
  if(id < ISP_MAX_SPRITES)
  {
    isp_hide_sprite(iss, id);
    isp_restore_bg(iss, id);
    if(NULL != iss->list[id].bg_buf.buf)
    {
      free(iss->list[id].bg_buf.buf);
    }
    if( (ISP_DRAW_BLOCK == iss->list[id].type) &&
        (NULL != iss->list[id].sp_buf.buf) )
    {
      free(iss->list[id].sp_buf.buf);
    }
    iss->list[id] = isprite_default;
    iss->list[id].bg_buf = isbuf_default;
    iss->list[id].bg_buf = isbuf_default;
  }
}

/* just set the position, don't flag it.  all that's handled later.*/
void isp_set_sprite_xy(ISPRITESYS *iss, ISPID id, coord_t x, coord_t y)
{
  if(id < ISP_MAX_SPRITES)
  {
    iss->list[id].sp_buf.x = x;
    iss->list[id].sp_buf.y = y;
  }
}


/* if copy_buf == TRUE this copies buf into it's own allocated memory.
 * if FALSE, it treats buf as a pointer, and does not save locally.  if buf is
 * changed, just call this again to flag it for re-draw, otherwise it assumes
 * the sprite is unchanged.
 */
void isp_set_sprite_block(ISPRITESYS *iss, ISPID id, coord_t xs, coord_t ys, pixel_t * buf, bool_t copy_buf)
{
  int size=0;
  /* if coords and size are same as BG, don't flag BG as dirty */
  if( (id < ISP_MAX_SPRITES) && (xs > 0) && (ys > 0) && (NULL != buf) )

  {
    iss->list[id].sp_buf.xs  = xs;
    iss->list[id].sp_buf.ys  = ys;
    if(copy_buf)
    {
      iss->list[id].type = ISP_DRAW_BLOCK;
      size = xs * ys *sizeof(pixel_t);
      if(NULL != iss->list[id].sp_buf.buf)
      {
        iss->list[id].sp_buf.buf = realloc(iss->list[id].sp_buf.buf, size);
      }
      else
      {
        iss->list[id].sp_buf.buf = malloc(size);
      }
      memcpy(iss->list[id].sp_buf.buf, buf, size);
    }
    else
    {
      iss->list[id].type = ISP_DRAW_PTR;
      iss->list[id].sp_buf.buf = buf;
    }
    /* flag it dity so it redraws */
    if(ISP_STAT_DIRTY_BOTH != iss->list[id].status) /* if BG is dirty, FG is dirty, so don't change status */
    {
      iss->list[id].status = ISP_STAT_DIRTY_SP;
    }
  }
}

void isp_set_sprite_file(ISPRITESYS *iss, ISPID id, coord_t x, coord_t y, char *fname)
{
  strcpy(iss->list[id].fname, fname);
}
/* feed this a color_t value.  like from HTML2COLOR(h) or RGB2COLOR(r,g,b);
 *  it will fill the sprite's former position with solid block of that color.
 */
void isp_set_sprite_bgcolor(ISPRITESYS *iss, ISPID id, color_t col)
{
  if(id < ISP_MAX_SPRITES)
  {
    iss->list[id].bgcolor = col;
    iss->list[id].bgtype = ISP_BG_FIXEDCOLOR;
    /* maybe free BG buffer if it exists? */
  }
}

/* releases the background color mode, and switches sprite to dynamic background mode
 */

void isp_release_sprite_bgcolor(ISPRITESYS *iss, ISPID id)
{
  if(id < ISP_MAX_SPRITES)
  {
    iss->list[id].bgcolor = isprite_default.bgcolor;
    iss->list[id].bgtype = ISP_BG_DYNAMIC;
  }
}





void  isp_draw_all_sprites(ISPRITESYS *iss)
{
  ISPID i, id, max, slist[ISP_MAX_SPRITES];

  /* make list of active only.  This way we don't have to perform that check constantly */
  max=0;
  for(i=0; i< ISP_MAX_SPRITES; i++)
  {
    if(iss->list[i].active)
    {
      slist[max] = i;
      max++;
    }
  }
  /* Check if position and size of sprite and BG are the same, don't copy BG again. */
  for(i=0; i< max; i++)
  {
    id = slist[i];
    /* if the stored BG is not same size and position as sprite, flag as dirty */
    if( (iss->list[id].visible) &&
        ((ISP_DRAW_GIF == iss->list[id].type) ||
         (iss->list[id].bg_buf.x != iss->list[id].sp_buf.x) ||
         (iss->list[id].bg_buf.y != iss->list[id].sp_buf.y) ||
         (iss->list[id].bg_buf.xs != iss->list[id].sp_buf.xs) ||
         (iss->list[id].bg_buf.ys != iss->list[id].sp_buf.ys)) )
    {
      iss->list[id].status = ISP_STAT_DIRTY_BOTH;
    }
  }

  /* check for box collisions here.  if there is any overlap, both have dirty BG.  can't have one buffer a BG that has sprite data on it */
  isp_flag_dirty_sprite_collisions(iss, false);


  /* first restore all dirty BG blocks*/
  for(i=0; i< max; i++)
  {
    id = slist[i];
    if(ISP_STAT_DIRTY_BOTH == iss->list[id].status)
    {
      isp_restore_bg(iss, id);
    }
  }
  /* now collect BG block from new sprite postitions */
  for(i=0; i< max; i++)
  {
    id = slist[i];

  /* only save BG if sprite is visibe AND either status is Dirty, or we have no BG */
    if( (iss->list[id].visible) &&
        ((ISP_STAT_DIRTY_BOTH == iss->list[id].status ) || (NULL == iss->list[id].bg_buf.buf))  )
    {
      isp_capture_bg(iss, id);
      iss->list[id].status = ISP_STAT_DIRTY_SP;
    }

  }
  /* now paint all dirty sprites */
  for(i=0; i< max; i++)
  {
    id = slist[i];
    /* this handles visibility checks and changes flag status.  just let it  figure it out. */
    isp_draw_sprite(iss, id);
  }
}

void isp_shutdown(ISPRITESYS *iss)
{
  ISPID i;
  if(NULL != iss)
  {
    for(i=0; i < ISP_MAX_SPRITES; i++)
    {
      isp_destroy_sprite(iss, i);
    }
  }
  free(iss);
}


pixel_t *boxmaker(coord_t x, coord_t y, color_t col)
{

  int i, max;
  pixel_t *buf;
  max = x * y;
  buf = malloc(max*sizeof(pixel_t));
  for(i=0; i < max; i++)
  {
    buf[i] = col;
  }
  return(buf);
}

void sprite_tester(void)
{
  static ISPRITESYS *sl=NULL;
  static double i = 0.0;
  static int col=0;
  static ISPID s1, s2, s3, s4, s5, s6, s7, s8,s9;
  pixel_t *buf;
  coord_t xs,ys;


  if(NULL == sl)
  {
    sl = isp_init();
    s1 = isp_make_sprite(sl); // make sprites.  none are drawn yet.
    s2 = isp_make_sprite(sl); // they have no position or pixel data yet.
    s3 = isp_make_sprite(sl);
    s4 = isp_make_sprite(sl); // make sprites.  none are drawn yet.
    s5 = isp_make_sprite(sl); // they have no position or pixel data yet.
    s6 = isp_make_sprite(sl);
    s7 = isp_make_sprite(sl); // make sprites.  none are drawn yet.
    s8 = isp_make_sprite(sl); // they have no position or pixel data yet.
    s9 = isp_make_sprite(sl);

    xs=8;
    ys=15;
    buf = boxmaker(xs,ys, HTML2COLOR(0xff00ff));
    isp_set_sprite_block(sl, s1, xs, ys, buf, TRUE);
    free(buf);
    xs=10;
    ys=11;
    buf = boxmaker(xs,ys, HTML2COLOR(0x00FFff));
    isp_set_sprite_block(sl, s2, xs, ys, buf, TRUE);
    free(buf);

    xs=15;
    ys=9;
    buf = boxmaker(xs,ys, HTML2COLOR(0x4488ff));
    isp_set_sprite_block(sl, s3, xs, ys, buf, TRUE);
    free(buf);

    xs=5;
    ys=5;
    buf = boxmaker(xs,ys, HTML2COLOR(0xff0000));
    isp_set_sprite_block(sl, s4, xs, ys, buf, TRUE);
    free(buf);

    xs=20;
    ys=20;
    buf = boxmaker(xs,ys, HTML2COLOR(0x00ff00));
    isp_set_sprite_block(sl, s5, xs, ys, buf, TRUE);
    free(buf);

    xs=35;
    ys=3;
    buf = boxmaker(xs,ys, HTML2COLOR(0x0000ff));
    isp_set_sprite_block(sl, s6, xs, ys, buf, TRUE);
    free(buf);

    xs=15;
    ys=13;
    buf = boxmaker(xs,ys, HTML2COLOR(0x000000));
    isp_set_sprite_block(sl, s7, xs, ys, buf, TRUE);
    free(buf);

    xs=5;
    ys=23;
    buf = boxmaker(xs,ys, HTML2COLOR(0xffffff));
    isp_set_sprite_block(sl, s8, xs, ys, buf, TRUE);
    free(buf);

    xs=12;
    ys=12;
    buf = boxmaker(xs,ys, HTML2COLOR(0xffff00));
    isp_set_sprite_block(sl, s9, xs, ys, buf, TRUE);
    free(buf);

/* switch to this instead of the block of code below it to have all sprites moving
  isp_set_sprite_xy(sl, s1, 160 + (sin(i) * 25), 120 + (cos(i) * 25) );
  isp_set_sprite_xy(sl, s2, 160 + (sin(i+2) * 35), 120 + (cos(i+2) * 35) );
  isp_set_sprite_xy(sl, s3, 160 + (sin(i+4) * 55), 120 + (cos(i+4) * 55) );
  isp_set_sprite_xy(sl, s4, 160 + (sin(-i) * 25), 120 + (cos(-i) * 25) );
  isp_set_sprite_xy(sl, s5, 160 + (sin(-i+2) * 45), 120 + (cos(-i+2) * 35) );
  isp_set_sprite_xy(sl, s6, 160 + (sin(-i+4) * 65), 120 + (cos(-i+4) * 65) );
  isp_set_sprite_xy(sl, s7, 160 + (sin(-1.2*i+1) * 25), 120 + (cos(-i) * 15) );
  isp_set_sprite_xy(sl, s8, 160 + (sin(1.1*i+2.5) * 5), 120 + (cos(-i+2) * 35) );
  isp_set_sprite_xy(sl, s9, 160 + (sin(1.3*-i+4.5) * 75), 120 + (cos(-i+4) * 60) );
*/

  isp_set_sprite_xy(sl, s1, 160 + (sin(2) * 25), 120 + (cos(2) * 25) );
  isp_set_sprite_xy(sl, s2, 160 + (sin(2+2) * 35), 120 + (cos(2+2) * 35) );
  isp_set_sprite_xy(sl, s3, 160 + (sin(2+4) * 55), 120 + (cos(2+4) * 55) );
  isp_set_sprite_xy(sl, s4, 160 + (sin(-2) * 25), 120 + (cos(-2) * 25) );
  isp_set_sprite_xy(sl, s5, 160 + (sin(-3+2) * 45), 120 + (cos(-3+2) * 35) );
  isp_set_sprite_xy(sl, s6, 160 + (sin(-3+4) * 65), 120 + (cos(-3+4) * 65) );
  isp_set_sprite_xy(sl, s7, 160 + (sin(-1.2*4+1) * 45), 120 + (cos(-1.2) * 45) );
  isp_set_sprite_xy(sl, s8, 160 + (sin(-4+4.3) * 95), 120 + (cos(-5+3.8) * 90) );
  isp_set_sprite_bgcolor(sl, s9, HTML2COLOR(0x0000ff));
}
isp_set_sprite_xy(sl, s9, 160 + (sin(-i+4.5) * 75), 120 + (cos(-i+4) * 60) );


xs=(int)25;
ys=(int)25;

buf = boxmaker(xs,ys, HTML2COLOR(col));

free(buf);
col += 0x010101;
if(col > 0xffffff)
{
  col=0;
}

  i += 0.15;

  isp_draw_all_sprites(sl);

}