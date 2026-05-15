/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _TVM_SBI_H
#define _TVM_SBI_H

#include <asm/sbi.h>

#define TVM_SBI_EXT_ID 0x8424b45

#define SBI_SM_REGISTER_SHARED_MEM_WITH_REE 1030
#define SBI_SM_FREE_SHARED_MEM_WITH_REE 1031

static inline long zion_register_shared_mem(unsigned long addr,
					    unsigned long nr_pages)
{
	struct sbiret ret;

	ret = sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_REGISTER_SHARED_MEM_WITH_REE,
			addr, nr_pages, 0, 0, 0, 0);
	return ret.error;
}

static inline long zion_free_shared_mem(unsigned long addr,
					unsigned long nr_pages)
{
	struct sbiret ret;

	ret = sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_FREE_SHARED_MEM_WITH_REE,
			addr, nr_pages, 0, 0, 0, 0);
	return ret.error;
}

#endif
