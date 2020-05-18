/*
 * RZ/N1 Clocks
 *
 * All clocks are controlled using the SYSCTRL registers.
 * There is a required sequence for enabling the IP clock, taking the IP out of
 * reset, and if the IP is a bus master, enabling it.
 * We use a table to define the SYSCTRL registers and bits for each clock.
 *
 * Copyright (c) 2017 Renesas Electronics Europe Ltd
 * SPDX-License-Identifier: MIT
 */
#include <stdint.h>
#include "clock.h"
#include "rzn1-memory-map.h"
#include "rzn1-clocks.h"

/* Generic register/bit group descriptor */
struct rzn1_onereg {
	uint16_t reg : 7,	/* Register number (word) */
		pos : 5,	/* Bit number */
		size : 4;	/* Optional: size in bits */
} __attribute__((packed));

struct rzn1_clkdesc {
	struct rzn1_onereg clock, reset, ready, masteridle, scon, mirack, mistat;
} __attribute__((packed));

#define _BIT(_r, _p) { .reg = _r, .pos = _p }

#define _CLK(_n, _clk, _rst, _rdy, _midle, _scon, _mirack, _mistat) \
	{ .clock = _clk, .reset = _rst, .ready = _rdy, .masteridle = _midle, \
	  .scon = _scon, .mirack = _mirack, .mistat = _mistat }

#define BUG_ON(x)
      
#include "rzn1-clkctrl-tables.h"
          
          /* Basic read/write */
#define readl(pAddress)          (* (volatile unsigned int *) (pAddress))
#define writel(data, pAddress)    (* (volatile unsigned int *) (pAddress) = (data))

#define clk_readl readl
#define clk_writel writel

static void *clk_mgr_base_addr = (void *)RZN1_SYSTEM_CTRL_BASE;

static void clk_mgr_desc_set(const struct rzn1_onereg *one, int on)
{
	uint32_t *reg = ((uint32_t *)clk_mgr_base_addr) + one->reg;
	uint32_t val = clk_readl(reg);
	val = (val & ~(1 << one->pos)) | ((!!on) << one->pos);
	clk_writel(val, reg);
}

static uint32_t clk_mgr_desc_get(const struct rzn1_onereg *one)
{
	uint32_t *reg = ((uint32_t *)clk_mgr_base_addr) + one->reg;
	uint32_t val = clk_readl(reg);
	val = (val >> one->pos) & 1;
	return val;
}

int rzn1_clk_set_gate(int clkdesc_id, int on)
{
	const struct rzn1_clkdesc *g = &rzn1_clock_list[clkdesc_id];
	uint32_t timeout;
    uint32_t i;
	BUG_ON(!clk_mgr_base_addr);
	BUG_ON(!g->clock.reg);

	if (!on && g->masteridle.reg) {
		/* Set 'Master Idle Request' bit */
		clk_mgr_desc_set(&g->masteridle, 1);

		/* Wait for Master Idle Request acknowledge */
		if (g->mirack.reg) {
			for (timeout = 100000; timeout &&
				!clk_mgr_desc_get(&g->mirack); timeout--)
					;
			if (!timeout)
				return -1;
		}

		/* Wait for Master Idle Status signal */
		if (g->mistat.reg) {
			for (timeout = 100000; timeout &&
				!clk_mgr_desc_get(&g->mistat); timeout--)
					;
			if (!timeout)
				return -1;
		}
	}

	/* Enable/disable the clock */
	clk_mgr_desc_set(&g->clock, on);

	/* De-assert reset */
	if (g->reset.reg)
		clk_mgr_desc_set(&g->reset, 1);

	/* Hardware manual recommends 5us delay after enabling clock & reset */
    for (i=0;i<12000;i++) {
        asm("nop");
    }
   
	/* If the peripheral is memory mapped (i.e. an AXI slave), there is an
	 * associated SLVRDY bit in the System Controller that needs to be set
	 * so that the FlexWAY bus fabric passes on the read/write requests.
	 */
	if (g->ready.reg)
		clk_mgr_desc_set(&g->ready, on);

	/* Wait for FlexWAY Socket Connection signal */
	if (on && g->scon.reg) {
		for (timeout = 100000; timeout &&
			!clk_mgr_desc_get(&g->scon); timeout--)
				;
		if (!timeout)
			return -1;
	}

	/* Clear 'Master Idle Request' bit */
	if (g->masteridle.reg)
		clk_mgr_desc_set(&g->masteridle, !on);


	/* Wait for Master Idle Request acknowledge */
	if (g->mirack.reg) {
		for (timeout = 100000; timeout &&
			clk_mgr_desc_get(&g->mirack); timeout--)
				;
		if (!timeout)
			return -1;
	}

	return 0;
}

void rzn1_clk_reset(int clkdesc_id)
{
	const struct rzn1_clkdesc *g = &rzn1_clock_list[clkdesc_id];
    uint32_t i;
	BUG_ON(!clk_mgr_base_addr);
	BUG_ON(!g->clock.reg);

	if (g->reset.reg) {
		clk_mgr_desc_set(&g->reset, 0);
        for (i=0;i<12000;i++) {
          asm("nop");
        }
		clk_mgr_desc_set(&g->reset, 1);
	}
}

void rzn1_clk_reset_state(int clkdesc_id, int level)
{
	const struct rzn1_clkdesc *g = &rzn1_clock_list[clkdesc_id];

	BUG_ON(!clk_mgr_base_addr);
	BUG_ON(!g->clock.reg);

	if (g->reset.reg)
		clk_mgr_desc_set(&g->reset, level);
}

/*
 * Note: this driver just checks against min and max values that is supported by
 * each PLL register. Some registers also have other restricitions.
 */
struct pll_data {
	uint16_t reg;
	uint16_t min;
	uint16_t max;
};
static const struct pll_data pll[] = {
	[RZN1_CLKDIV_PGEXT2_PR6] = { 0x48, 12, 64},
	[RZN1_CLKDIV_QSPI2] = { 0x64, 4, 64 },
	[RZN1_CLKDIV_SWITCH] = { 0x94, 5, 40 },
	[RZN1_CLKDIV_OPP] = { 0xE0, 2, 16 },
	[RZN1_CLKDIV_CA7] = { 0xE4, 1, 4 },
	[RZN1_CLKDIV_PG1_PR2] = { 0xF8, 12, 128 },
	[RZN1_CLKDIV_PG1_PR3] = { 0x100, 8, 128 },
	[RZN1_CLKDIV_PG1_PR4] = { 0x108, 8, 128 },
	[RZN1_CLKDIV_PG4_PR1] = { 0x110, 12, 200 },
	[RZN1_CLKDIV_PG5_PR5] = { 0x11C, 10, 40 },
	[RZN1_CLKDIV_QSPI1] = { 0x124, 4, 64 },
	[RZN1_CLKDIV_SDIO1] = { 0x128, 20, 128 },
	[RZN1_CLKDIV_SDIO2] = { 0x12C, 20, 128 },
	[RZN1_CLKDIV_PG0_ADC] = { 0x134, 50, 250 },
	[RZN1_CLKDIV_PG0_I2C] = { 0x138, 12, 64 },
	[RZN1_CLKDIV_PG0_UART] = { 0x13C, 12, 128 },
	[RZN1_CLKDIV_NFLASH] = { 0x148, 12, 64 },
	[RZN1_CLKDIV_PG0_MOTOR] = { 0x150, 2, 8 },
	[RZN1_CLKDIV_HWRTOS_MDC] = { 0x190, 80, 640 },
};

/* System Controller */
#define sysctrl_readl(addr) \
	readl(RZN1_SYSTEM_CTRL_BASE + addr)
#define sysctrl_writel(val, addr) \
	writel(val, RZN1_SYSTEM_CTRL_BASE + addr)

void rzn1_sysctrl_div(uint32_t reg, uint32_t div)
{
	/* Wait for busy bit to be cleared */
	while (sysctrl_readl(reg) & (1UL << 31))
		;

	/* New divider setting */
	sysctrl_writel((1UL << 31) | div, reg);

	/* Wait for busy bit to be cleared */
	while (sysctrl_readl(reg) & (1UL << 31))
		;
}

int rzn1_clk_set_divider(int pll_id, uint32_t divider)
{
	/* Check for valid ID */
	if (pll_id > RZN1_CLKDIV_HWRTOS_MDC)
		return -1;

	/* Check for valid divider setting */
	if ((divider < pll[pll_id].min) || (divider > pll[pll_id].max))
		return -1;

	rzn1_sysctrl_div(pll[pll_id].reg, divider);

	return 0;
}

int rzn1_clk_get_divider(int pll_id)
{
	int div;

	/* Check for valid ID */
	if (pll_id > RZN1_CLKDIV_HWRTOS_MDC)
		return -1;

	div = sysctrl_readl(pll[pll_id].reg & 0x7fffffff);

	return (1000000000 / div);
}
