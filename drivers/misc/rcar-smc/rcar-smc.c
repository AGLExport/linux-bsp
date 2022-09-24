// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * R-Car smc based helper driver
 *
 */
#include <linux/arm-smccc.h>
#include <linux/string.h>
#include <linux/module.h>
#include <misc/rcar-smc/rcar-smc.h>

#define	ARM_SMCC_RCAR_BSP		(16u)

#define	RCAR_BSP_SVC_CALL_COUNT				(0xff00u)
#define	RCAR_BSP_SVC_UID					(0xff01u)
#define	RCAR_BSP_SVC_VERSION				(0xff03u)

#define	RCAR_BSP_SVC_LOCKED_REGSET_LINUX	(0x0501u)
#define	RCAR_BSP_SVC_LOCKED_REGSET_RTOS1	(0x0502u)


#define RCAR_BSP_SMC_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_64, \
	ARM_SMCC_RCAR_BSP, (func_num))

#define RCAR_BSP_SVC_UID_0	(0xa9bf7a10u)
#define RCAR_BSP_SVC_UID_1	(0x3e42c748u)
#define RCAR_BSP_SVC_UID_2	(0x7dccd805u)
#define RCAR_BSP_SVC_UID_3	(0x924957d9u)


static int rcar_smc_atf_support = 0;

/*
 * locked regster bit change healper
 */
#ifdef CONFIG_RCAR_SMC_PFC
int rcar_smc_locked_regbit_change(uint32_t regaddr, uint32_t mask, uint32_t value)
{
	struct arm_smccc_res res;
	int ret = -2;

	if (rcar_smc_atf_support == 0)
		return -1;	//SMC helper is not support in ATF

	memset(&res, 0, sizeof(res));

	arm_smccc_smc(RCAR_BSP_SMC_CALL_VAL(RCAR_BSP_SVC_LOCKED_REGSET_LINUX)
				, regaddr, mask, value, 0, 0, 0, 0, &res);

	if (res.a0 == 0)
		ret = 0;

	return ret;
}
#else
int rcar_smc_locked_regbit_change(uint32_t regaddr, uint32_t mask, uint32_t value)
{
	return -1;	//SMC helper is not support.
}
#endif //#ifdef CONFIG_RCAR_SMC_PFC
EXPORT_SYMBOL(rcar_smc_locked_regbit_change);


/*
 * ATF Check
 */
static int rcar_smc_support_check(void)
{
	struct arm_smccc_res res;

	memset(&res, 0, sizeof(res));

	arm_smccc_smc(RCAR_BSP_SMC_CALL_VAL(RCAR_BSP_SVC_UID)
				, 0, 0, 0, 0, 0, 0, 0, &res);

	if ((res.a0 == RCAR_BSP_SVC_UID_0) && (res.a1 == RCAR_BSP_SVC_UID_1)
		&& (res.a2 == RCAR_BSP_SVC_UID_2) && (res.a3 == RCAR_BSP_SVC_UID_3)) {
		rcar_smc_atf_support = 1;
	}

	return 0;
}

static int __init rcar_smc_init(void)
{
	return rcar_smc_support_check();
}
core_initcall(rcar_smc_init);

MODULE_LICENSE("GPL");
