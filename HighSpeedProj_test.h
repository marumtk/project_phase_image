
//-----------------------------------------------------------------------------
// Class for High-speed Projector
// -- Gaku Narita, 2015/11/06
//-----------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <tchar.h>
#include<opencv2\opencv.hpp>;
#include <libappinterface.h>
#include <RegDef.h>

#ifndef _DEBUG
#pragma comment(lib, "StdLibrary.lib")
#else
#pragma comment(lib, "StdLibraryd.lib")
#endif

//#define PROJ_TRIG_DELAY 0
//#define PROJ_LED_DELAY 0 // �ʏ��600���炢���œK�l
constexpr unsigned int PROJ_FRAME_PER_SEC = 750u;
constexpr unsigned int PROJ_TRIG_DELAY = 0u;
constexpr unsigned int PROJ_LED_DELAY = 0u; //���̃R�[�h�ł͊֌W�Ȃ��͂�
constexpr unsigned int PROJ_VALID_BITS = 8u; //�g�p����bit��(�}�[�J�܂�)
constexpr unsigned int PROJ_MIRROR_MODE = 1u; //disable 1: enable (�ʏ��1)
constexpr unsigned int PROJ_COMP_DATA = 0u; // 0: disable 1: enable (�ʏ��0)
constexpr unsigned int PROJ_FLIP_MODE = 0u;// 0: disable 1: enable (�ʏ��0)
constexpr unsigned int PROJ_SKIP_TRIG = 0u;// 0: disable 1: enable (�ʏ��0)
constexpr unsigned int PROJ_WIDTH = 1024u;
constexpr unsigned int PROJ_HEIGHT = 768u;
constexpr unsigned int BIT_SEQUENCE[] = { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u };
constexpr unsigned int MARKER_OFFSET = 0u; // 0: disable otherwise: enable (1��s)
constexpr int PROJ_LED_ADJUST[] = { 500u, 200u, 0u, 0u, 0u, 0u, 0u, 0u }; // 10ns

//---- HighSpeedProjector�̃N���X
class HighSpeedProj {
private:
	std::size_t input_img_count;
	UINT iRet_loop;

	//---- �ċA�̂��߂̊֐�
	void sendImageloop(cv::Mat& img);
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

	//---- ��Ԃ𓾂�
	void getstatus(SYSTEM_STATUS &_stSystemStatus);

	//---- sendImg�ɐ�������������Ԃ��֐�
	void GetInputImgNum(std::size_t &_input_frame_num);
};


