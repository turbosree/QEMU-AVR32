/*
 * AVR32 virtual CPU header
 *
 *  Copyright (c) 2011 "Sreejith Naarakathil" <sreejith.naarakathil@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CPU_AVR32_H
#define CPU_AVR32_H

#define TARGET_LONG_BITS 32
#define ELF_MACHINE	EM_AVR32
#define CPUState struct CPUAVR32State
#define TARGET_HAS_ICE 1

#define TARGET_PAGE_BITS 12

#include "config.h"
#include "qemu-common.h"
#include "cpu-defs.h"
#include "softfloat.h"

typedef struct CPUAVR32State {
   /* Up to 15 general-purpose 32-bit registers and SR*/
   uint32_t gregs[16];
   CPU_COMMON
} CPUAVR32State;

/* Return the current SR value.  */
uint32_t sr_read(CPUAVR32State *env);
/* Set the SR.  Note that some bits of mask must be all-set or all-clear.  */
void sr_write(CPUAVR32State *env, uint32_t val, uint32_t mask);

CPUAVR32State *cpu_avr32_init(const char *cpu_model);
void avr32_translate_init(void);
int cpu_avr32_exec(CPUAVR32State *s);
void do_interrupt(CPUAVR32State *);

/* you can call this signal handler from your SIGBUS and SIGSEGV
   signal handlers to inform the virtual CPU of exceptions. non zero
   is returned if the signal was handled by the virtual CPU.  */
int cpu_avr32_signal_handler(int host_signum, void *pinfo,
                           void *puc);
int cpu_avr32_handle_mmu_fault (CPUAVR32State *env, target_ulong address, int rw,
                              int mmu_idx);
#define cpu_handle_mmu_fault cpu_avr32_handle_mmu_fault

static inline void cpu_set_tls(CPUAVR32State *env, target_ulong newtls)
{
  /* env->cp15.c13_tls2 = newtls; */
}

void avr32_cpu_list(FILE *f, fprintf_function cpu_fprintf);

#define TARGET_PHYS_ADDR_SPACE_BITS 32
#define TARGET_VIRT_ADDR_SPACE_BITS 32

#define cpu_init cpu_avr32_init
#define cpu_exec cpu_avr32_exec
#define cpu_gen_code cpu_avr32_gen_code
#define cpu_signal_handler cpu_avr32_signal_handler
#define cpu_list avr32_cpu_list

#define MMU_USER_IDX 1

static inline int cpu_mmu_index (CPUState *env)
{
   /* SN: TBD */
   return 0;
}

#if defined(CONFIG_USER_ONLY)
static inline void cpu_clone_regs(CPUState *env, target_ulong newsp)
{
    /* if (newsp) */
    /*     env->regs[13] = newsp; */
    /* env->regs[0] = 0; */
}
#endif

#include "cpu-all.h"

static inline void cpu_get_tb_cpu_state(CPUState *env, target_ulong *pc,
                                        target_ulong *cs_base, int *flags)
{
   /* SN: TBD */
}

static inline bool cpu_has_work(CPUState *env)
{
    /* return env->interrupt_request & */
    /*     (CPU_INTERRUPT_FIQ | CPU_INTERRUPT_HARD | CPU_INTERRUPT_EXITTB); */
   return false;
}

#include "exec-all.h"

static inline void cpu_pc_from_tb(CPUState *env, TranslationBlock *tb)
{
    /* env->regs[15] = tb->pc; */
}

#endif
