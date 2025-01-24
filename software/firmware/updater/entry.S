/*-
 * Copyright (c) 2016-2019
 *      Bill Paul <wpaul@windriver.com>.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Bill Paul.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _ASM
#include "updater.h"

	.cpu		cortex-m4
	.fpu		fpv4-sp-d16

	.thumb

	.file		"entry.S"
	.text

	.arch		armv7e-m
	.syntax		unified

	.section	.text.main,"ax",%progbits
	.align		1
	.code		16
	.thumb_func
	.type		main, %function

	.globl		main
	.globl		chMtxObjectInit
	.globl		chMtxLock
	.globl		chMtxUnlock
	.globl		_port_irq_epilogue

	/* Load an initial stack, then jump to the updater code */
main:
	ldr	r0, = #UPDATER_STACK
	mov	sp, r0
	bl	updater

/*
 * We're using some ChibiOS drivers in the updater, but not using ChibiOS
 * itself. We're careful to use APIs that don't require the ChibiOS kernel
 * or scheduler, however in a couple of cases we still have some unresolved
 * linker references. We need to stub these routines out. To save space,
 * we can create one routine as a stub and alias all the other functions
 * to it.
 *
 * Note that a few of these only show up when we build without LTO.
 */

chMtxObjectInit:
chMtxLock:
chMtxUnlock:
_port_irq_epilogue:
	bx	lr
