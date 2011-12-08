
/* this struct defines the way the registers are stored on the
   stack during a system call. */

struct target_pt_regs {
    abi_long uregs[18];
};

#define AVR32_sr	   uregs[16]
#define AVR32_pc		uregs[15]
#define AVR32_lr		uregs[14]
#define AVR32_sp		uregs[13]
#define AVR32_r12		uregs[12]
#define AVR32_r11		uregs[11]
#define AVR32_r10		uregs[10]
#define AVR32_r9		uregs[9]
#define AVR32_r8		uregs[8]
#define AVR32_r7		uregs[7]
#define AVR32_r6		uregs[6]
#define AVR32_r5		uregs[5]
#define AVR32_r4		uregs[4]
#define AVR32_r3		uregs[3]
#define AVR32_r2		uregs[2]
#define AVR32_r1		uregs[1]
#define AVR32_r0		uregs[0]
#define AVR32_ORIG_r0	uregs[17]

/* SN: TBD */

#define UNAME_MACHINE "avr32"
