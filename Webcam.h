#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>;

class Webcam {
public:
	cv::VideoCapture cap;

	const unsigned int CAMERA_WIDTH = 368;
	const unsigned int CAMERA_HEIGHT = 320;
	const unsigned int FRAME_PER_SEC = 800;



	Webcam();                             //コンストラクタ
	~Webcam() {}                           //デストラクタ
	bool cap_color(cv::Mat &img_col);     //カラー画像取得
	bool cap_gray(cv::Mat &img_gray);     //グレースケール画像取得
};
