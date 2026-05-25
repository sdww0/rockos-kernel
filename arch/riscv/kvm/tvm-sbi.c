#include <asm/sbi.h>
#include "tvm/tvm-sbi.h"

struct sbiret sbi_tvm_init()
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_CREATE_CVM, 0, 0, 0, 0, 0, 0);
}

struct sbiret sbi_tvm_vcpu_init(unsigned int cvm_id,
				struct cvm_vcpu_shared_mem *shared_mem_ptr)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_INIT_CVM_VCPU, cvm_id,
			 (unsigned long)shared_mem_ptr, 0, 0, 0, 0);
}

struct sbiret sbi_tvm_vcpu_enter(unsigned int cvm_id, unsigned int vcpu_id)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_ENTER_CVM, cvm_id, vcpu_id, 0,
			 0, 0, 0);
}

struct sbiret sbi_tvm_set_mem_block(unsigned int cvm_id,
				    struct tvm_mem_block *mem_block)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_SET_CVM_MEM_INFO, cvm_id,
			 (unsigned long)mem_block, 0, 0, 0, 0);
}

struct sbiret sbi_tvm_load_page(unsigned int cvm_id,
				struct cvm_load_page_para *page_para)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_LOAD_PAGE, cvm_id,
			 (unsigned long)page_para, 0, 0, 0, 0);
}

struct sbiret sbi_cvm_load_mem(unsigned int cvm_id,
				struct cvm_load_mem_para *mem_para)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_LOAD_MEM, cvm_id,
			 (unsigned long)mem_para, 0, 0, 0, 0);
}

struct sbiret sbi_tvm_register_pt(unsigned int cvm_id,
				  struct tvm_sbi_register_pt *pt)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_REGISTER_PT, cvm_id,
			 (unsigned long)pt, 0, 0, 0, 0);
}

struct sbiret sbi_tvm_destory(unsigned int cvm_id)
{
	return sbi_ecall(TVM_SBI_EXT_ID, SBI_SM_DESTROY_CVM, cvm_id, 0, 0, 0, 0, 0);
}
