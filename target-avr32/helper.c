#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "gdbstub.h"
#include "helper.h"
#include "qemu-common.h"
#include "host-utils.h"
#if !defined(CONFIG_USER_ONLY)
#include "hw/loader.h"
#endif

uint32_t sr_read(CPUAVR32State *env)
{
   /* SN: TBD */
   return 0;
}

void sr_write(CPUAVR32State *env, uint32_t val, uint32_t mask)
{
   /* SN: TBD */
}

CPUAVR32State *cpu_avr32_init(const char *cpu_model)
{
   /* SN: TBD */
   CPUAVR32State *env;
   static int inited = 0;

   env = g_malloc0(sizeof(CPUAVR32State));
   cpu_exec_init(env);
   if (!inited) {
      inited = 1;
      avr32_translate_init();
   }
   cpu_reset(env);
   qemu_init_vcpu(env);

   return env;
}

void cpu_reset(CPUAVR32State *env)
{
   if (qemu_loglevel_mask(CPU_LOG_RESET)) {
      qemu_log("CPU Reset\n");
      log_cpu_state(env, 0);
   }

   memset(env, 0, offsetof(CPUAVR32State, breakpoints));

#if defined (CONFIG_USER_ONLY)
   env->sreg.sr = AVR32_SR_M_MASK & (AVR32_SR_M_APP << AVR32_SR_M_OFFSET);
   /* SN: TBD - Should we enable interrupts??  */
#else
   /* Supervisor mode with interrupts disabled.  */
   env->sreg.sr = (AVR32_SR_M_MASK & (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET)) | AVR32_SR_GM_MASK | AVR32_SR_EM_MASK;
#endif
   tlb_flush(env, 1);
}

void avr32_cpu_list(FILE *f, fprintf_function cpu_fprintf)
{
   /* SN: TBD */
}

#if defined(CONFIG_USER_ONLY)

void do_interrupt (CPUState *env)
{
   env->exception_index = -1;
}

int cpu_avr32_handle_mmu_fault (CPUState *env, target_ulong address, int rw,
                                int mmu_idx)
{
   if (rw == 2) {
      /* SN: TBD */
   } else {
      /* SN: TBD */
   }
   return 1;
}

#else /* !CONFIG_USER_ONLY */

/* Handle a CPU exception.  */
void do_interrupt(CPUAVR32State *env)
{
   /* SN: TBD */
}

int cpu_avr32_handle_mmu_fault (CPUState *env, target_ulong address,
                              int access_type, int mmu_idx)
{
   /* SN: TBD */
   return 1;
}

static inline int get_phys_addr(CPUState *env, uint32_t address,
                                int access_type, int is_user,
                                uint32_t *phys_ptr, int *prot,
                                target_ulong *page_size)
{
   return 0;
}

target_phys_addr_t cpu_get_phys_page_debug(CPUState *env, target_ulong addr)
{
   uint32_t phys_addr;
   target_ulong page_size;
   int prot;
   int ret;

   ret = get_phys_addr(env, addr, 0, 0, &phys_addr, &prot, &page_size);

   if (ret != 0)
      return -1;

   return phys_addr;
}

#endif
