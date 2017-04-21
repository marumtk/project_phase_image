//-----------------------------------------------------------------------------
// Class for High-speed Projector
// -- Gaku Narita, 2015/11/06
//-----------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <tchar.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
#include <libappinterface.h>
#include <RegDef.h>

#pragma comment(lib, "StdLibrary.lib")

#define PROJ_FRAME_PER_SEC 700
#define PROJ_VALID_BITS 8
#define PROJ_TRIG_DELAY 0
#define PROJ_LED_DELAY 600
#define PROJ_MIRROR_MODE 1 // 0: disable 1: enable (�ʏ��1)
#define PROJ_COMP_DATA 0 // 0: disable 1: enable (�ʏ��0)
#define PROJ_FLIP_MODE 0 // 0: disable 1: enable (�ʏ��0)
#define PROJ_WIDTH 1024
#define PROJ_HEIGHT 768

//---- HighSpeedProjector�̃N���X
class HighSpeedProj{
public:
	CStdLibrary *pPcieLibrary;
	SYSTEM_PARAM stSystemParam;
	INT	iStop;

	INT iBoardID;
	UINT iRet;
	UINT iChannel;
	ULONG ulSize;

	void *pBuf;
	ULONG		ulLEDCtrlDelay;
	ULONG		ulFrameTrigDelay;
	ULONG		ulDataSizeInBuffer;

	//---- �R���X�g���N�^
	HighSpeedProj();

	//---- �v���W�F�N�^��ڑ�����
	//---- [out] ����:true ���s:false
	bool connectProj();

	//---- �G���[���Ƀv���W�F�N�^�̐ڑ�����������
	void errorCloseProj();

	//---- �f�X�g���N�^
	~HighSpeedProj();

	//---- �f���𑗂�
	void sendImage(cv::Mat& img);
};
