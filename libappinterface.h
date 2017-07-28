/*=========================================================================
	TOKYO ELECTRON DEVICE LTD.
	Copyright (c) 2014 TOKYO ELECTRON DEVICE LTD.
	DLP System Library
=========================================================================*/

/*=========================================================================
	LibAppInterface.h
	Interface for StdLibrary and application
=========================================================================*/

#ifndef	_TEDSH_LIB_APP_IF_H_H_H_
#define	_TEDSH_LIB_APP_IF_H_H_H_	(1)

#include "Windows.h"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STDLIBRARY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STDLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STDLIBRARY_EXPORTS
#define STDLIBRARY_API __declspec(dllexport)
#else
#define STDLIBRARY_API __declspec(dllimport)
#endif

#define MAXIMUM_NUMBER_OF_BOARDS		4
#define MAXIMUM_NUMBER_OF_CHANNELS		2
#define MAX_BUF_NUM_ONE_TIME			4

#define DMD_CTRL_20150904				1

/****************************
* PCIE Config
****************************/
#define	PCI_TYPE0_ADDRESSES				6
#define PCI_TYPE1_ADDRESSES				2
#define PCI_TYPE2_ADDRESSES				5



typedef struct _PCI_COMMON_CONFIG 
{
    USHORT  VendorID;                   
    USHORT  DeviceID;                   
    USHORT  Command;                    
    USHORT  Status;            
    USHORT  RevisionID;                                     
    USHORT  ClassCode;                 
    UCHAR   CacheLineSize;              
    UCHAR   LatencyTimer;              
    UCHAR   HeaderType;                 
    UCHAR   BIST;                       
    union 
    {
        struct _PCI_HEADER_TYPE_0 
        {
            ULONG   BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   CIS;
            USHORT  SubVendorID;
            USHORT  SubSystemID;
            ULONG   ROMBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   Reserved2;
            UCHAR   InterruptLine;      
            UCHAR   InterruptPin;       
            UCHAR   MinimumGrant;       
            UCHAR   MaximumLatency;     
        } type0;
    } u;
    ULONG	Reserved3[6];
    union 
    {
		struct _PCI_HEADER_TYPE_1 
		{
			UCHAR	PCIeCapID;
			UCHAR	NextCapPointer;
			USHORT	PCIeCap;
			ULONG	DeviceCap;
			USHORT	DeviceControl;
			USHORT	DeviceStatus;
			ULONG	LinkCap;
			USHORT	LinkControl;
			USHORT	LinkStatus;
		} type1;
	} n;
    union 
    {
		struct _PCI_HEADER_TYPE_2 
		{
			UCHAR	PMCapID;
			UCHAR	NextCapPointer;
			USHORT	PMCap;
			USHORT	PMCSR;
			UCHAR	BSE;
			UCHAR	Data;
		} type2;
	} m;
    union 
    {
		struct _PCI_HEADER_TYPE_3 
		{
			UCHAR	MSICapID;
			UCHAR	NextCapPointer;
			USHORT	MSIControl;
			ULONG	MessAddrLow;
			ULONG	MessAddrUpp;
			USHORT	MessData;
		} type3;
	} k;
    UCHAR   DeviceSpecific[140];
} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;

typedef struct _tagUserVerInfo
{
	char strDate[20];
	char strVer[20];
}USER_VER_INFO, *PUSER_VER_INFO;

#define LED_CTRL_STEP	20
#define SIDE_NUM	2
#define ON_SIDE		0
#define OFF_SIDE	1

typedef struct _tagSystemParam
{
	ULONG	FrameRate;		// fps
//	ULONG	Stage;			// 8: output 0:7, 7: output 1:7, 6: output 2:7, 5: output 3:7
	ULONG	ValidBits;			// 8: output 0:7, 7: output 1:7, 6: output 2:7, 5: output 3:7
#if DMD_CTRL_20150904	// 20150904-ZHANG.H_ADD-S
	ULONG	MirrorMode;		// 0: enable 1: disable
	ULONG	CompData;		// 0: enable 1: disable
	ULONG	FlipMode;		// 0: enable 1: disable

	ULONG	bitMode;	 // 0: disable 1: enable
	ULONG	trigMode;    // 0: Internal trigger	1: External trigger
	ULONG	skipMode;	 // 0: disableÅ@1: enable
	ULONG	SkipStage;	 // 1: *.*.*.*. , 2: **..**..**..**.. , 3:***...***...***...***...
	double MarkerOffset;
	unsigned int BIT_SEQUENCE[8];
#endif	// 20150904-ZHANG.H_ADD-E
	int		LEDAdjust[LED_CTRL_STEP];
}SYSTEM_PARAM, *PSYSTEM_PARAM;

typedef struct _tagSystemStatus
{
	ULONG	InputFrames;
	ULONG	OutputFrames;
	double	dfFrameTime;	// us
	double  dfMinDarkTime;	// us
}SYSTEM_STATUS, *PSYSTEM_STATUS;

/******************************************
* Return status defines
******************************************/
#define STATUS_SUCCESSFUL		 		0x00
#define	STATUS_INCOMPLETE				0x01
#define	STATUS_INVALID_PARAM			0x02
#define STATUS_INVALID_BOARDINDEX		0x04
#define STATUS_ALLOC_FAILED				0x08
#define STATUS_INVALID_DEVICEHANDLE		0x10
#define STATUS_INVALID_BARNUM			0x20
#define STATUS_LOCK_FAILED				0x40
#define STATUS_UNLOCK_FAILED			0x80
#define STATUS_FREE_FAILED				0x100
#define STATUS_INVALID_CHINDEX			0x200
#define STATUS_DMA_TIMEOUT				0x400

/*************************************************
* Event for application and driver communication
*************************************************/
#define TSTDPCI_USER_EVENT_NUM			(32)
#define	TSTDPCI_USER_EVENT_OPEN_NAME	_T("Global\\TSTDPCI%02XUserEvent_%02X")					// For application
#define EVENT_FPGA_INIT_DONE			0

#define SIZE_4K		(4096)
#define FRAME_SIZE	(1024 * 768)
#define FRAME_BUF_MIN_NUM	100
#define FRAME_BUF_MAX_NUM	1000

// ----------------------
// Externally Visible API
#ifdef __cplusplus
extern "C" {
#endif

// ç°âÒnBoardIndexÇÕÇOÇ…å≈íËÇ∑ÇÈ
// nChannelIndexÇ‡ÇOÇ…å≈íËÇ∑ÇÈ

class CStdLibrary
{
public:
	CStdLibrary();
//	CStdLibrary(UINT nBoardIndex);
	~CStdLibrary();

public:
	UINT ConnectToBoard(UINT nBoardIndex);
	UINT DisconnectFromBoard(UINT nBoardIndex);
	UINT WriteBoardRegister(UINT nBoardIndex, ULONG ulBar, ULONG ulOffset, ULONG ulData);
	UINT ReadBoardRegister(UINT nBoardIndex, ULONG ulBar, ULONG ulOffset, ULONG *pulData);

	UINT SetReset(
			UINT nBoardIndex 	// in, nBoardIndex = 0;
	);
	
	UINT SetSystemParam(
			UINT nBoardIndex,  	// in, nBoardIndex = 0;
			SYSTEM_PARAM stSystemParam
	);

	UINT RegisterSGDMA(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex, // in, nChannelIndex = 0;
			ULONG ulDDROffset, 	// in, ulDDROffset = 0;
			ULONG ulDMABufferSize	// in, alignment by frame size(1024 x 768)
	);

	UINT UnregisterSGDMA(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex // in, nChannelIndex = 0;
	);

	UINT StartSGDMA(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex, // in, nChannelIndex = 0;
			BOOL bToPC);		// in, bToPC = FALSE (Write to board)

	UINT StopSGDMA(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex); // in, nChannelIndex = 0;

	UINT GetBuffer(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex, // in, nChannelIndex = 0;
			void **ppBuffer, 	// out, next empty buffer address for sgdma;
			ULONG* pulDataSize	// out, next empty buffer size that is can be used for sgdma (Fix Value = FRAME_SIZE or 0)
	);

	UINT PostDataSize(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT nChannelIndex, // in, nChannelIndex = 0;
			ULONG ulDataSize	// in, ulDataSize = FRAME_SIZE;
	);

	UINT GetStatus(
			UINT nBoardIndex, 				// in, nBoardIndex = 0;
			PSYSTEM_STATUS stSystemStatus	// out
	);

	UINT SetFloat(
			UINT nBoardIndex, 	// in, nBoardIndex = 0;
			UINT isPowerFloat	// in, 1: PowerFloat
	);

//	UINT CreateUserEvent(UINT nBoardIndex, HANDLE *hEvent);		// TBD. unused
	UINT GetDriverInfo(UINT nBoardIndex, PUSER_VER_INFO pVerInfo);
	UINT GetLibInfo(UINT nBoardIndex, PUSER_VER_INFO pVerInfo);
//	UINT GetDMATransTimeMS(UINT nBoardIndex, UINT nChannelIndex, double *pTime);
	UINT GetMaxMinFrameRate(UINT nBoardIndex, UINT ValidBits, UINT *MaxFps, UINT *MinFps);
};

#ifdef __cplusplus
}
#endif


#endif