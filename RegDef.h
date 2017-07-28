/*=========================================================================
	TOKYO ELECTRON DEVICE LTD.
	Copyright (c) 2014 TOKYO ELECTRON DEVICE LTD.
	DLP System Library
=========================================================================*/

/*=========================================================================
	LibDrvInterface.h
	Interface for StdLibrary and Drive
=========================================================================*/

#ifndef	_TEDSH_REGDEF_H_H_H_
#define	_TEDSH_REGDEF_H_H_H_	(1)

// New PCIe IP Core
#define IPCORE_REG_INTR_MASK				0x004
#define IPCORE_REG_INTR_STATUS				0x008
#define IPCORE_REG_INTR_FACTOR				0x00C
#define IPCORE_REG_PCIE_CORE_RESET			0x010
#define IPCORE_REG_PCIE_LINK_STAT			0x020
#define IPCORE_REG_PCIE_REQUEST_NUM			0x024

// DMA Board Register
#define IPCORE_REG_DMA_CONTROL				0x100
#define IPCORE_REG_DMA_NEXT_DCSRADDR_LOW	0x110
#define IPCORE_REG_DMA_NEXT_DCSRADDR_HIGH	0x114

#define IPCORE_REG_DMA_CTRL					0x160
#define IPCORE_REG_DMA_4KCNT				0x164

// Pcie Board Register
#define PCIE_FPGA_VERSION					0x0000
#define PCIE_SYS_CTRL						0x0004
#define PCIE_MIRROR_CTRL					0x0008
#define PCIE_FRAME_TIME						0x000C
#define PCIE_DMD_FBIT_NUM					0x0010
#define PCIE_DMD_FBIT_SEQ					0x0014
#define PCIE_DMD_GRST1_OFFSET				0x0018
#define PCIE_DMD_GRST2_OFFSET				0x001C
#define PCIE_DMD_GRST3_OFFSET				0x0020
#define PCIE_DMD_GRST4_OFFSET				0x0024
#define PCIE_DMD_GRST5_OFFSET				0x0028
#define PCIE_DMD_GRST6_OFFSET				0x002C
#define PCIE_DMD_GRST7_OFFSET				0x0030
#define PCIE_DMD_GRST8_OFFSET				0x0034
#define PCIE_LED_ENABLE_GRST				0x0038
#define PCIE_LED_CHAN1_OFFSET				0x003C
#define PCIE_LED_CHAN2_OFFSET				0x0040
#define PCIE_LED_CHAN3_OFFSET				0x0044
#define PCIE_LED_CHAN4_OFFSET				0x0048
#define PCIE_LED_CHAN5_OFFSET				0x004C
#define PCIE_LED_CHAN6_OFFSET				0x0050
#define PCIE_LED_CHAN7_OFFSET				0x0054
#define PCIE_LED_CHAN8_OFFSET				0x0058
#define PCIE_LED_ENABLE_DELAY				0x005C

#define PCIE_INPUT_FRAME_CNT				0x0060
#define PCIE_DMDOUT_FRAME_CNT				0x0064
#define PCIE_BIT_MODE						0X0108
#define PCIE_SINGLE_MODE					0x10C
#define PCIE_TRIG_SKIP						0X0114
#define PCIE_TRIG_MODE						0X0118
#define PCIE_TRIG_CNT						0x0130
#define PCIE_FRAME_TRIG_DELAY				0x0068

#define PCIE_LED_NEW_CTRL_BASEADDR			0x0070
#define PCIE_LED_NEW_CTRL_NUM				20
#define PCIE_LED_CTRL_MODE					0x00C0

// Register value defines
// interrupt enable
#define USER_INT_ENABLE						(0x01<<16)
#define DMA_END_INT_ENABLE					0x01

// interrupt status(write 1 to clear)
#define USER_INT_STATUS						(0x01<<16)
#define DMA_END_INT_STATUS					0x01

//DMA Control
#define DMA_MODE_SG							(0x1<<23)
#define DMA_MODE_ONESHOT					(0x0<<23)
#define DMA_FPGA_TO_PC						(0x1<<21)
#define DMA_PC_TO_FPGA						(0x0<<21)
#define DMA_START							(0x1<<20)

// Descriptor format
// Control
#define DESCRIPTOR_VALID					(0x1<<31)
#define LAST_DESCRIPTOR						(0x1<<30)
#define END_DESCRIPTOR						(0x1<<22)
// FPGA address
#define FPGAAddress(addr)					((addr)>>3)		// Unused


// SYS CTRL
#define SOFT_RSET_VAL						(0x01 << 31)
#define OUTPUT_START_VAL					(0x01 << 24)
#define TEST_MODE_VAL						(0x01 << 20)
#define SYSTEM_STOP_VAL						(0x01 << 17)
#define SYSTEM_START_VAL					(0x01 << 16)
#define SODIMM2_INIT_DONE_VAL				(0x01 << 1)
#define SODIMM1_INIT_DONE_VAL				(0x01 << 0)

// MIRROR CTRL
#define POWER_FLOAT_VAL						(0x01 << 1)
#define FLOAT_VAL							(0x01 << 0)


#define VALUE_INT_INIT_DONE					(0x01 << 0)

#define VALUE_PCIE_CORE_RESET				(0x01 << 0)


#define VAL_BIT_MODE_1						( 0x01 )
#define VAL_BIT_MODE_8						( 0x00 )

#define VAL_TRIG_MODE_INTERNAL					( 0x00 )
#define VAL_TRIG_MODE_EXTERNAL					( 0x01 )



#endif
