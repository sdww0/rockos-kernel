/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __TVM_SBI__
#define __TVM_SBI__
#include <linux/dma-mapping.h>
// #include <linux/kvm_host.h>
#include <linux/types.h>
#include <asm/sbi.h>
// #include <stdint.h>

#define FREE_SHARED_MEM_BASE 0x400000000000000ULL

struct cvm_extra_trap_info {
	unsigned long htinst;
	unsigned long htinst_len;
};

struct cvm_vcpu_shared_mem {
	uintptr_t guest_context;
	uintptr_t guest_csr;
	uintptr_t extra_trap;
};

struct cvm_load_kernel_para {
	unsigned long base;
	unsigned long size;
};

struct cvm_load_page_para {
	unsigned long stash;
	unsigned long pos;
};

struct cvm_load_mem_para {
	unsigned long stash;
	unsigned long pos;
	unsigned long size;
};

// struct tvm_sbi_set_shared_mem {
//     unsigned long addr;
//     unsigned long len;
// };

struct tvm_sbi_configure_shared_mem {
	unsigned long addr;
	unsigned long num;
};

struct tvm_sbi_register_pt {
	unsigned long gpa;
	unsigned long hfn;
	unsigned long level;
	unsigned int is_huge;
	unsigned int rdonly;
};

struct tvm_mem_block {
	unsigned int slot;
	unsigned int flags;
	unsigned long guest_phys_addr;
	unsigned long memory_size; /* bytes */
	unsigned long userspace_addr; /* start of the userspace allocated memory */
	unsigned int private; //[obsolete]
};

struct tvm_cpu_context {
	unsigned long zero;
	unsigned long ra;
	unsigned long sp;
	unsigned long gp;
	unsigned long tp;
	unsigned long t0;
	unsigned long t1;
	unsigned long t2;
	unsigned long s0;
	unsigned long s1;
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
	unsigned long a4;
	unsigned long a5;
	unsigned long a6;
	unsigned long a7;
	unsigned long s2;
	unsigned long s3;
	unsigned long s4;
	unsigned long s5;
	unsigned long s6;
	unsigned long s7;
	unsigned long s8;
	unsigned long s9;
	unsigned long s10;
	unsigned long s11;
	unsigned long t3;
	unsigned long t4;
	unsigned long t5;
	unsigned long t6;
	//unsigned long sepc;
	//unsigned long sstatus;
	unsigned long mepc;
	unsigned long mstatus;
	unsigned long hstatus;
	unsigned long htinst;
	//union __riscv_fp_state fp;
};

#define RISCV_SHARED_RAM 0x400000000000000ULL
#define FREE_SHARED_MEM_BASE 0x400000000000000ULL

#define TVMIO 0xCC

#define TVM_LOAD_KERNEL _IO(TVMIO, 0x01)
#define TVM_LOAD_KERNEL_PAGE _IO(TVMIO, 0x02)
#define CVM_LOAD_MEM _IO(TVMIO, 0x03)

//#define TVM_SBI_EXT_ID 0x8424b46
#define TVM_SBI_EXT_ID 0x8424b45

#define SBI_SM_INIT_CVM_VCPU 1012
#define SBI_SM_ENTER_CVM 1013
#define SBI_SM_RESERVE_MEM 1014
#define SBI_SM_CREATE_CVM 1015
#define SBI_SM_SET_CVM_MEM_INFO 1018
#define SBI_SM_LOAD_PAGE 1020
#define SBI_SM_REGISTER_PT 1021
#define SBI_SM_EXIT_CVM 1022
#define SBI_SM_DESTROY_CVM 1023
#define SBI_SM_LOAD_MEM 1025
#define SBI_SM_SET_INITED 1026
#define SBI_SM_CYCLE_BEGIN 1027
#define SBI_SM_CYCLE_END 1028
#define SBI_SM_CLEAN_SEC_MEM 1029
#define SBI_SM_REGISTER_SHARED_MEM_WITH_REE 1030
#define SBI_SM_FREE_SHARED_MEM_WITH_REE 1031
#define SBI_SM_SYNC_PT 1034

struct sbiret sbi_tvm_init(void);

struct sbiret sbi_tvm_vcpu_init(unsigned int cvm_id,
				struct cvm_vcpu_shared_mem *shared_mem_ptr);

struct sbiret sbi_tvm_vcpu_enter(unsigned int cvm_id, unsigned int vcpu_id);

struct sbiret sbi_tvm_set_mem_block(unsigned int cvm_id,
				    struct tvm_mem_block *mem_block);

struct sbiret sbi_tvm_load_page(unsigned int cvm_id,
				struct cvm_load_page_para *page_para);

struct sbiret sbi_cvm_load_mem(unsigned int cvm_id,
				struct cvm_load_mem_para *mem_para);

struct sbiret sbi_tvm_register_pt(unsigned int cvm_id,
				  struct tvm_sbi_register_pt *pt);

struct sbiret sbi_tvm_sync_pt(unsigned int cvm_id,
			      unsigned long gpa, unsigned long pt_paddr);

struct sbiret sbi_tvm_destroy(unsigned int cvm_id);

int tvm_remap_pfn(struct vm_area_struct *vma, unsigned long addr,
		  unsigned long pfn, unsigned long size, pgprot_t prot);

struct kvm_vcpu;

int tvm_register_shared_mem(struct kvm_vcpu *vcpu, unsigned long addr,
			    unsigned long nr_pages);
int tvm_unregister_shared_mem(struct kvm_vcpu *vcpu, unsigned long addr,
			      unsigned long nr_pages);

#endif
