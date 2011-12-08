/*
 *  AVR32 translation
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
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "cpu.h"
#include "disas.h"
#include "tcg-op.h"
#include "qemu-log.h"

#include "helper.h"
#define GEN_HELPER 1
#include "helper.h"

/* SN: TBD - internal defines */ 
typedef struct DisasContext {
   target_ulong pc;
   struct TranslationBlock *tb;
   int singlestep_enabled;
   int user;
} DisasContext;

#if defined(CONFIG_USER_ONLY)
#define IS_USER(s) 1
#else
#define IS_USER(s) (s->user)
#endif

/* These instructions trap after executing, so defer them until after the
   conditional executions state has been updated.  */
#define DISAS_WFI 4
#define DISAS_SWI 5

static TCGv_ptr cpu_env;
static TCGv_i32 cpu_gregs[16];

#include "gen-icount.h"

static const char *regnames[] =
   { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
     "r8", "r9", "r10", "r11", "r12", "r13", "r14", "pc" };

/* initialize TCG globals.  */
void avr32_translate_init(void)
{
   int i;

   cpu_env = tcg_global_reg_new_ptr(TCG_AREG0, "env");

   for (i = 0; i < 16; i++) {
      cpu_gregs[i] = tcg_global_mem_new_i32(TCG_AREG0,
                                            offsetof(CPUState, gregs[i]),
                                            regnames[i]);
   }

   /* SN: TBD */

#define GEN_HELPER 2
#include "helper.h"
}

void cpu_dump_state(CPUState *env, FILE *f, fprintf_function cpu_fprintf,
                    int flags)
{
   /* SN: TBD */
}

static inline void gen_set_pc_im(uint32_t val)
{
    tcg_gen_movi_i32(cpu_gregs[15], val);
}

static inline void gen_goto_tb(DisasContext *s, int n, uint32_t dest)
{
   TranslationBlock *tb;

   tb = s->tb;
   if ((tb->pc & TARGET_PAGE_MASK) == (dest & TARGET_PAGE_MASK)) {
      tcg_gen_goto_tb(n);
      gen_set_pc_im(dest);
      tcg_gen_exit_tb((tcg_target_long)tb + n);
   } else {
      gen_set_pc_im(dest);
      tcg_gen_exit_tb(0);
   }
   /* SN: TBD */
}

/* generate intermediate code in gen_opc_buf and gen_opparam_buf for
   basic block 'tb'. If search_pc is TRUE, also generate PC
   information for each intermediate instruction. */
static inline void gen_intermediate_code_internal(CPUState *env,
                                                  TranslationBlock *tb,
                                                  int search_pc)
{
   int num_insns = 0;
   /* SN: TBD */
   gen_icount_end(tb, num_insns);
}

void gen_intermediate_code(CPUState *env, TranslationBlock *tb)
{
   gen_intermediate_code_internal(env, tb, 0);
}

void gen_intermediate_code_pc(CPUState *env, TranslationBlock *tb)
{
   gen_intermediate_code_internal(env, tb, 1);
}

void restore_state_to_opc(CPUState *env, TranslationBlock *tb, int pc_pos)
{
   env->gregs[15] = gen_opc_pc[pc_pos];
   /* SN: TBD */
}
