// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * R-Car smc based helper driver
 *
 */
#ifndef _RCAR_SMC_HELPER_DRV_
#define _RCAR_SMC_HELPER_DRV_

#include <linux/types.h>


int rcar_smc_locked_regbit_change_pfc(uint32_t regaddr, uint32_t mask, uint32_t value);

// locked regster bit change healper for cpg
int rcar_smc_locked_regbit_change_cpg(uint32_t regaddr, uint32_t mask, uint32_t value);
// audit regster write healper for cpg
int rcar_smc_audit_regwrite_cpg(uint32_t regaddr, uint32_t value);

#endif //#ifndef _RCAR_SMC_HELPER_DRV_
