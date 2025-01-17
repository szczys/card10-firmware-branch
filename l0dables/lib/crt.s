		/*
		 * C Runtime for l0dable.
		 *
		 * Also known as a startup file.
		 *
		 * We provide the following to l0dables:
		 *  - calling GCC initializers.
		 *  - an ISR vector.
		 *
		 * The stack is provided by l0der.
		 */

		.syntax unified
		.arch armv7-m

		/*
		 * ISR Vector.
		 *
		 * All of the following (apart from Reset_Handler, which calls main())
		 * are backed by weak referenced symbols, which you can override just
		 * by defining them in C code.
		 */
		.section .text.isr_vector
		.align 7
		.globl __isr_vector
__isr_vector:
		.long    0                             /* Top of Stack, overriden by l0der at load time */
		.long    Reset_Handler                 /* Reset Handler */
		.long    NMI_Handler                   /* NMI Handler */
		.long    HardFault_Handler             /* Hard Fault Handler */
		.long    MemManage_Handler             /* MPU Fault Handler */
		.long    BusFault_Handler              /* Bus Fault Handler */
		.long    UsageFault_Handler            /* Usage Fault Handler */
		.long    0                             /* Reserved */
		.long    0                             /* Reserved */
		.long    0                             /* Reserved */
		.long    0                             /* Reserved */
		.long    SVC_Handler                   /* SVCall Handler */
		.long    0                             /* Reserved */ /* @TODO: Is this the Debug Montior Interrupt? */
		.long    0                             /* Reserved */
		.long    PendSV_Handler                /* PendSV Handler */
		.long    SysTick_Handler               /* SysTick Handler */

		/* Device-specific Interrupts */
		.long    PF_IRQHandler                 /* 0x10  0x0040  16: Power Fail */
		.long    WDT0_IRQHandler               /* 0x11  0x0044  17: Watchdog 0 */
		.long    DefaultHandler                /* 0x12  0x0048  18: USB, used by core0, unoverridable */
		.long    RTC_IRQHandler                /* 0x13  0x004C  19: RTC */
		.long    TRNG_IRQHandler               /* 0x14  0x0050  20: True Random Number Generator */
		.long    TMR0_IRQHandler               /* 0x15  0x0054  21: Timer 0 */
		.long    TMR1_IRQHandler               /* 0x16  0x0058  22: Timer 1 */
		.long    TMR2_IRQHandler               /* 0x17  0x005C  23: Timer 2 */
		.long    TMR3_IRQHandler               /* 0x18  0x0060  24: Timer 3*/
		.long    TMR4_IRQHandler               /* 0x19  0x0064  25: Timer 4*/
		.long    TMR5_IRQHandler               /* 0x1A  0x0068  26: Timer 5 */
		.long    RSV11_IRQHandler              /* 0x1B  0x006C  27: Reserved */
		.long    RSV12_IRQHandler              /* 0x1C  0x0070  28: Reserved */
		.long    I2C0_IRQHandler               /* 0x1D  0x0074  29: I2C0 */
		.long    DefaultHandler                /* 0x1E  0x0078  30: UART 0, used by core0, unoverridable */
		.long    UART1_IRQHandler              /* 0x1F  0x007C  31: UART 1 */
		.long    SPI1_IRQHandler               /* 0x20  0x0080  32: SPI1 */
		.long    SPI2_IRQHandler               /* 0x21  0x0084  33: SPI2 */
		.long    RSV18_IRQHandler              /* 0x22  0x0088  34: Reserved */
		.long    RSV19_IRQHandler              /* 0x23  0x008C  35: Reserved */
		.long    ADC_IRQHandler                /* 0x24  0x0090  36: ADC */
		.long    RSV21_IRQHandler              /* 0x25  0x0094  37: Reserved */
		.long    RSV22_IRQHandler              /* 0x26  0x0098  38: Reserved */
		.long    FLC0_IRQHandler               /* 0x27  0x009C  39: Flash Controller */
		.long    DefaultHandler                /* 0x28  0x00A0  40: GPIO0, used by core0, unoverridable */
		.long    DefaultHandler                /* 0x29  0x00A4  41: GPIO2, used by core0, unoverridable */
		.long    RSV26_IRQHandler              /* 0x2A  0x00A8  42: GPIO3 */
		.long    TPU_IRQHandler                /* 0x2B  0x00AC  43: Crypto */
		.long    DMA0_IRQHandler               /* 0x2C  0x00B0  44: DMA0 */
		.long    DMA1_IRQHandler               /* 0x2D  0x00B4  45: DMA1 */
		.long    DMA2_IRQHandler               /* 0x2E  0x00B8  46: DMA2 */
		.long    DMA3_IRQHandler               /* 0x2F  0x00BC  47: DMA3 */
		.long    RSV32_IRQHandler              /* 0x30  0x00C0  48: Reserved */
		.long    RSV33_IRQHandler              /* 0x31  0x00C4  49: Reserved */
		.long    UART2_IRQHandler              /* 0x32  0x00C8  50: UART 2 */
		.long    RSV35_IRQHandler              /* 0x33  0x00CC  51: Reserved */
		.long    I2C1_IRQHandler               /* 0x34  0x00D0  52: I2C1 */
		.long    RSV37_IRQHandler              /* 0x35  0x00D4  53: Reserved */
		.long    SPIXFC_IRQHandler             /* 0x36  0x00D8  54: SPI execute in place */
		.long    BTLE_TX_DONE_IRQHandler       /* 0x37  0x00DC  55: BTLE TX Done */
		.long    BTLE_RX_RCVD_IRQHandler       /* 0x38  0x00E0  56: BTLE RX Recived */
		.long    BTLE_RX_ENG_DET_IRQHandler    /* 0x39  0x00E4  57: BTLE RX Energy Dectected */
		.long    BTLE_SFD_DET_IRQHandler       /* 0x3A  0x00E8  58: BTLE SFD Detected */
		.long    BTLE_SFD_TO_IRQHandler        /* 0x3B  0x00EC  59: BTLE SFD Timeout*/
		.long    BTLE_GP_EVENT_IRQHandler      /* 0x3C  0x00F0  60: BTLE Timestamp*/
		.long    BTLE_CFO_IRQHandler           /* 0x3D  0x00F4  61: BTLE CFO Done */
		.long    BTLE_SIG_DET_IRQHandler       /* 0x3E  0x00F8  62: BTLE Signal Detected */
		.long    BTLE_AGC_EVENT_IRQHandler     /* 0x3F  0x00FC  63: BTLE AGC Event */
		.long    BTLE_RFFE_SPIM_IRQHandler     /* 0x40  0x0100  64: BTLE RFFE SPIM Done */
		.long    BTLE_TX_AES_IRQHandler        /* 0x41  0x0104  65: BTLE TX AES Done */
		.long    BTLE_RX_AES_IRQHandler        /* 0x42  0x0108  66: BTLE RX AES Done */
		.long    BTLE_INV_APB_ADDR_IRQHandler  /* 0x43  0x010C  67: BTLE Invalid APB Address*/
		.long    BTLE_IQ_DATA_VALID_IRQHandler /* 0x44  0x0110  68: BTLE IQ Data Valid */
		.long    WUT_IRQHandler                /* 0x45  0x0114  69: WUT Wakeup */
		.long    GPIOWAKE_IRQHandler           /* 0x46  0x0118  70: GPIO Wakeup */
		.long    RSV55_IRQHandler              /* 0x47  0x011C  71: Reserved */
		.long    SPI0_IRQHandler               /* 0x48  0x0120  72: SPI AHB */
		.long    WDT1_IRQHandler               /* 0x49  0x0124  73: Watchdog 1 */
		.long    RSV58_IRQHandler              /* 0x4A  0x0128  74: Reserved */
		.long    PT_IRQHandler                 /* 0x4B  0x012C  75: Pulse train */
		.long    SDMA0_IRQHandler              /* 0x4C  0x0130  76: Smart DMA 0 */
		.long    RSV61_IRQHandler              /* 0x4D  0x0134  77: Reserved */
		.long    I2C2_IRQHandler               /* 0x4E  0x0138  78: I2C 2 */
		.long    RSV63_IRQHandler              /* 0x4F  0x013C  79: Reserved */
		.long    RSV64_IRQHandler              /* 0x50  0x0140  80: Reserved */
		.long    RSV65_IRQHandler              /* 0x51  0x0144  81: Reserved */
		.long    SDHC_IRQHandler               /* 0x52  0x0148  82: SDIO/SDHC */
		.long    OWM_IRQHandler                /* 0x53  0x014C  83: One Wire Master */
		.long    DMA4_IRQHandler               /* 0x54  0x0150  84: DMA4 */
		.long    DMA5_IRQHandler               /* 0x55  0x0154  85: DMA5 */
		.long    DMA6_IRQHandler               /* 0x56  0x0158  86: DMA6 */
		.long    DMA7_IRQHandler               /* 0x57  0x015C  87: DMA7 */
		.long    DMA8_IRQHandler               /* 0x58  0x0160  88: DMA8 */
		.long    DMA9_IRQHandler               /* 0x59  0x0164  89: DMA9 */
		.long    DMA10_IRQHandler              /* 0x5A  0x0168  90: DMA10 */
		.long    DMA11_IRQHandler              /* 0x5B  0x016C  91: DMA11 */
		.long    DMA12_IRQHandler              /* 0x5C  0x0170  92: DMA12 */
		.long    DMA13_IRQHandler              /* 0x5D  0x0174  93: DMA13 */
		.long    DMA14_IRQHandler              /* 0x5E  0x0178  94: DMA14 */
		.long    DMA15_IRQHandler              /* 0x5F  0x017C  95: DMA15 */
		.long    USBDMA_IRQHandler             /* 0x60  0x0180  96: USB DMA */
		.long    WDT2_IRQHandler               /* 0x61  0x0184  97: Watchdog Timer 2 */
		.long    ECC_IRQHandler                /* 0x62  0x0188  98: Error Correction */
		.long    DVS_IRQHandler                /* 0x63  0x018C  99: DVS Controller */
		.long    SIMO_IRQHandler               /* 0x64  0x0190  100: SIMO Controller */
		.long    RPU_IRQHandler                /* 0x65  0x0194  101: RPU */ /* @TODO: Is this correct? */
		.long    AUDIO_IRQHandler              /* 0x66  0x0198  102: Audio subsystem */
		.long    FLC1_IRQHandler               /* 0x67  0x019C  103: Flash Control 1 */
		.long    RSV88_IRQHandler              /* 0x68  0x01A0  104: UART 3 */
		.long    RSV89_IRQHandler              /* 0x69  0x01A4  105: UART 4 */
		.long    RSV90_IRQHandler              /* 0x6A  0x01A8  106: UART 5 */
		.long    RSV91_IRQHandler              /* 0x6B  0x01AC  107: Camera IF */
		.long    RSV92_IRQHandler              /* 0x6C  0x01B0  108: I3C */
		.long    HTMR0_IRQHandler              /* 0x6D  0x01B4  109: HTmr */
		.long    HTMR1_IRQHandler              /* 0x6E  0x01B8  109: HTmr */

		/*
		 * Reset_Handler, or, l0dable entrypoint.
		 */
		.text
		.thumb
		.thumb_func
		.align 2
Reset_Handler:
		/* Call system initialization from l0dables/lib/hardware.c. */
		blx SystemInit

		/* Call GCC constructors. */
		ldr r0, =__libc_init_array
		blx r0

		/* Jump to C code */
		ldr r0, =main
		blx r0

		/*
		 * C code done, spin forever.
		 * TODO(q3k): let epicardium know we're done.
		 */
.spin:
		bl .spin

		/*
		 * Used by __libc_init_array.
		 */
		.globl _init
_init:
		bx lr

		/*
		 * The default handler for all IRQs just spins forwever.
		 * TODO(q3k): let epicardium know we've reached an infinite loop due to
		 *            an exception and/or unhandled IRQ, perhaps by splitting
		 *            DefaultHandler into multiple handlers that report different
		 *            error conditions to epicardium (eg. unhandled IRQ, fault, ...)
		 */
		.thumb_func
		.type DefaultHandler, %function
DefaultHandler:
		b .

		.macro    def_irq_handler    handler_name
		.weakref \handler_name, DefaultHandler
		.endm

		/*
		 * Declare all default ISRs.
		 */
		def_irq_handler    NMI_Handler
		def_irq_handler    HardFault_Handler
		def_irq_handler    MemManage_Handler
		def_irq_handler    BusFault_Handler
		def_irq_handler    UsageFault_Handler
		def_irq_handler    SVC_Handler
		def_irq_handler    DebugMon_Handler
		def_irq_handler    PendSV_Handler

		def_irq_handler    PF_IRQHandler
		def_irq_handler    WDT0_IRQHandler
		def_irq_handler    RTC_IRQHandler
		def_irq_handler    TRNG_IRQHandler
		def_irq_handler    TMR0_IRQHandler
		def_irq_handler    TMR1_IRQHandler
		def_irq_handler    TMR2_IRQHandler
		def_irq_handler    TMR3_IRQHandler
		def_irq_handler    TMR4_IRQHandler
		def_irq_handler    RSV11_IRQHandler
		def_irq_handler    RSV12_IRQHandler
		def_irq_handler    I2C0_IRQHandler
		def_irq_handler    UART1_IRQHandler
		def_irq_handler    SPI1_IRQHandler
		def_irq_handler    SPI2_IRQHandler
		def_irq_handler    RSV18_IRQHandler
		def_irq_handler    RSV19_IRQHandler
		def_irq_handler    ADC_IRQHandler
		def_irq_handler    RSV21_IRQHandler
		def_irq_handler    RSV22_IRQHandler
		def_irq_handler    FLC0_IRQHandler
		def_irq_handler    RSV26_IRQHandler
		def_irq_handler    TPU_IRQHandler
		def_irq_handler    DMA0_IRQHandler
		def_irq_handler    DMA1_IRQHandler
		def_irq_handler    DMA2_IRQHandler
		def_irq_handler    DMA3_IRQHandler
		def_irq_handler    RSV32_IRQHandler
		def_irq_handler    RSV33_IRQHandler
		def_irq_handler    UART2_IRQHandler
		def_irq_handler    RSV35_IRQHandler
		def_irq_handler    I2C1_IRQHandler
		def_irq_handler    RSV37_IRQHandler
		def_irq_handler    SPIXFC_IRQHandler
		def_irq_handler    BTLE_TX_DONE_IRQHandler
		def_irq_handler    BTLE_RX_RCVD_IRQHandler
		def_irq_handler    BTLE_RX_ENG_DET_IRQHandler
		def_irq_handler    BTLE_SFD_DET_IRQHandler
		def_irq_handler    BTLE_SFD_TO_IRQHandler
		def_irq_handler    BTLE_GP_EVENT_IRQHandler
		def_irq_handler    BTLE_CFO_IRQHandler
		def_irq_handler    BTLE_SIG_DET_IRQHandler
		def_irq_handler    BTLE_AGC_EVENT_IRQHandler
		def_irq_handler    BTLE_RFFE_SPIM_IRQHandler
		def_irq_handler    BTLE_TX_AES_IRQHandler
		def_irq_handler    BTLE_RX_AES_IRQHandler
		def_irq_handler    BTLE_INV_APB_ADDR_IRQHandler
		def_irq_handler    BTLE_IQ_DATA_VALID_IRQHandler
		def_irq_handler    WUT_IRQHandler
		def_irq_handler    GPIOWAKE_IRQHandler
		def_irq_handler    RSV55_IRQHandler
		def_irq_handler    SPI0_IRQHandler
		def_irq_handler    WDT1_IRQHandler
		def_irq_handler    RSV58_IRQHandler
		def_irq_handler    PT_IRQHandler
		def_irq_handler    SDMA0_IRQHandler
		def_irq_handler    RSV61_IRQHandler
		def_irq_handler    I2C2_IRQHandler
		def_irq_handler    RSV63_IRQHandler
		def_irq_handler    RSV64_IRQHandler
		def_irq_handler    RSV65_IRQHandler
		def_irq_handler    SDHC_IRQHandler
		def_irq_handler    OWM_IRQHandler
		def_irq_handler    DMA4_IRQHandler
		def_irq_handler    DMA5_IRQHandler
		def_irq_handler    DMA6_IRQHandler
		def_irq_handler    DMA7_IRQHandler
		def_irq_handler    DMA8_IRQHandler
		def_irq_handler    DMA9_IRQHandler
		def_irq_handler    DMA10_IRQHandler
		def_irq_handler    DMA11_IRQHandler
		def_irq_handler    DMA12_IRQHandler
		def_irq_handler    DMA13_IRQHandler
		def_irq_handler    DMA14_IRQHandler
		def_irq_handler    DMA15_IRQHandler
		def_irq_handler    USBDMA_IRQHandler
		def_irq_handler    WDT2_IRQHandler
		def_irq_handler    ECC_IRQHandler
		def_irq_handler    DVS_IRQHandler
		def_irq_handler    SIMO_IRQHandler
		def_irq_handler    RPU_IRQHandler
		def_irq_handler    AUDIO_IRQHandler
		def_irq_handler    FLC1_IRQHandler
		def_irq_handler    RSV88_IRQHandler
		def_irq_handler    RSV89_IRQHandler
		def_irq_handler    RSV90_IRQHandler
		def_irq_handler    RSV91_IRQHandler
		def_irq_handler    RSV92_IRQHandler
		def_irq_handler    HTMR0_IRQHandler
		def_irq_handler    HTMR1_IRQHandler

		.section .cinterp
		.asciz "card10-l0dable"
		.byte
