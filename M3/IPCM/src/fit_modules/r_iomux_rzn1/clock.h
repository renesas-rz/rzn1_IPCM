/*
 * RZ/N1 Clock and Reset control
 *
 * Copyright (c) 2017 Renesas Electronics Europe Ltd
 * SPDX-License-Identifier: MIT
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "rzn1-clocks.h"

/*
 * Enable or disable a clock. It does not turn on/off any parent clocks.
 *
 * clkdesc_id is one of the clocks defined in rzn1-clocks.h. They start with
 * either RZN1_HCLK_ (bus clock) or RZN1_CLK_ (additional clccks).
 * Note that the hardware manual uses names such as HCLK and PCLK due to the
 * type of bus interface, i.e. AHB or APB respectively, whereas the driver
 * uses HCLK for all bus clocks.
 */
int rzn1_clk_set_gate(int clkdesc_id, int on);

/*
 * Reset an IP block or clock domain.
 *
 * Most of the clocks have an associated bit to reset everything in that clock
 * domain. This can be used to reset IP blocks for example.
 */
void rzn1_clk_reset(int clkdesc_id);

/*
 * Set the reset state to a specific state.
 *
 * This sets the reset signal for a clock domain to a specific state. All the
 * resets are active low, so level = 0 means hold in reset, 1 means release
 * from reset.
 */
void rzn1_clk_reset_state(int clkdesc_id, int level);

/*
 * Set a PLL clock divider.
 *
 * reg is one of RZN1_CLKDIV_*
 * All of the clock dividers have 1GHz PLL clock input, except CA7DIV.
 * Call before enabling the associated clocks.
 */
int rzn1_clk_set_divider(int pll_id, uint32_t divider);

/*
 * Get a clock rate.
 *
 * reg is one of RZN1_CLKDIV_*
 */
int rzn1_clk_get_divider(int pll_id);

#endif /* __CLOCK_H__ */
