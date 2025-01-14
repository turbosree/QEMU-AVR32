#ifndef QEMU_ARCH_INIT_H
#define QEMU_ARCH_INIT_H

extern const char arch_config_name[];

enum {
    QEMU_ARCH_ALL = -1,
    QEMU_ARCH_ALPHA = 1,
    QEMU_ARCH_ARM = 2,
    QEMU_ARCH_CRIS = 4,
    QEMU_ARCH_I386 = 8,
    QEMU_ARCH_M68K = 16,
    QEMU_ARCH_LM32 = 32,
    QEMU_ARCH_MICROBLAZE = 64,
    QEMU_ARCH_MIPS = 128,
    QEMU_ARCH_PPC = 256,
    QEMU_ARCH_S390X = 512,
    QEMU_ARCH_SH4 = 1024,
    QEMU_ARCH_SPARC = 2048,
    QEMU_ARCH_XTENSA = 4096,
    QEMU_ARCH_AVR32 = 8192,
};

extern const uint32_t arch_type;

void select_soundhw(const char *optarg);
void do_acpitable_option(const char *optarg);
void do_smbios_option(const char *optarg);
void cpudef_init(void);
int audio_available(void);
void audio_init(qemu_irq *isa_pic, PCIBus *pci_bus);
int tcg_available(void);
int kvm_available(void);
int xen_available(void);

#endif
