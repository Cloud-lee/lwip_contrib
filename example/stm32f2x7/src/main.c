/****************************************************************//**
 *
 * @file main.c
 *
 * @author   Logan Gunthorpe <logang@deltatee.com>
 *
 * @brief    LWIP STM32 Example Project
 *
 * Copyright (c) Deltatee Enterprises Ltd. 2013
 * All rights reserved.
 *
 ********************************************************************/

/* 
 * Redistribution and use in source and binary forms, with or without
 * modification,are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Logan Gunthorpe <logang@deltatee.com>
 *
 */

#include "config.h"
#include "version.h"
#include "network.h"

#include <stmlib/debug.h>
#include <stmlib/tick.h>
#include <stmlib/rand.h>

#include <cmsis/core_cmInstr.h>

#include <stdio.h>

unsigned long ticks = 0;

__attribute__((interrupt))
static void tick()
{
    tick_int_clear();
    ticks++;
}

int main()
{
    hw_init();
    debug_init();
    tick_init(tick);
    rand_init();

    printf("\n\nSTMLIB Example Code r" VERSION "\n");
    printf("System Clock: %d\n", clock_get_freq(NULL));

    network_init();

    while (1) {
        int more = network_loop(ticks);

        if (!more)
            __WFI();
    }
}
