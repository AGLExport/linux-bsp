// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * R-Car smc based helper driver
 *
 */
#ifndef _RCAR_SMC_HELPER_DRV_
#define _RCAR_SMC_HELPER_DRV_

#include <linux/types.h>


int rcar_smc_locked_regbit_change(uint32_t regaddr, uint32_t mask, uint32_t value);

#endif //#ifndef _RCAR_SMC_HELPER_DRV_
