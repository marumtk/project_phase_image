#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
#include "HighSpeedProj_test.h"
#include <vector>
#include "basler.h"
#include "Webcam.h"
#include <thread>

using namespace std;
using namespace cv;

//�e�X�g�摜�𓊉e����v���O����
void create_image_test(vector<Mat1b> &result){
	int num_image = 256;
	for(int i=0;i<num_image;i++){
		cv::Mat img(cv::Size(1024, 768), CV_8UC3, cv::Scalar::all(i));
		result.push_back(img);
	}
}

// 2���p�^�[���𓊉e����v���O����
void create_image_new(vector<Mat1b> &result){
	const string base = "sinimage_";
	vector<string> files;

	files.push_back(base+"1.bmp");
	files.push_back(base+"2.bmp");
	files.push_back(base+"3.bmp");
	files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};

// �����g��2���p�^�[���𓊉e����v���O����
void create_image_newhigh(vector<Mat1b> &result){
	const string base = "sinimage_high_";
	vector<string> files;

	files.push_back(base+"1.bmp");
	files.push_back(base+"2.bmp");
	files.push_back(base+"3.bmp");
	files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};

//Micro Phase Shifting �̃p�^�[���𓊉e����R�[�h 
void create_image_old(vector<Mat1b> &result){
	const string base = "Frame";
	vector<string> files;

	files.push_back(base+"0.tiff");
	files.push_back(base+"1.tiff");
	files.push_back(base+"2.tiff");
	files.push_back(base+"3.tiff");
	files.push_back(base+"4.tiff");
	files.push_back(base+"5.tiff");
	files.push_back(base+"6.tiff");
	files.push_back(base+"7.tiff");
	files.push_back(base+"8.tiff");
	files.push_back(base+"9.tiff");
	files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};

// csf�g�̉摜�𓊉e����v���O����
void create_image_twoplusone(vector<Mat1b> &result){
	const string base = "sinimage_csf_";
	vector<string> files;

	files.push_back(base+"1.bmp");
	files.push_back(base+"2.bmp");
	files.push_back(base+"3.bmp");
	files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};

// �ʏ�̐����g�p�^�[���𓊉e����v���O����
void create_image_normalsin(vector<Mat1b> &result){
	const string base = "sin30_";
	vector<string> files;

	files.push_back(base+"1.bmp");
	files.push_back(base+"2.bmp");
	files.push_back(base+"3.bmp");
	files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};



int main(){
	cout << "csf�@�Ōv������Ƃ���0��" << endl;
	cout << "��Ď�@�Ōv���i����g�j����Ƃ���1��" << endl;
	cout << "��Ď�@�Ōv���i�����g�j����Ƃ���2��" << endl;
	cout << "�e�X�g�摜�𓊉e����Ƃ���3��" << endl;
	cout << "�ʏ�̐����g�p�^�[���𓊉e����Ƃ���4��" << endl;
	cout << "������@�Ōv������Ƃ��͂���ȊO�̐�����" << endl;
	cout << "���͂��ĉ�����" << endl;
	int num;
	cin >> num;
	//���͂�0�̂Ƃ���csf�摜�𓊉e
	if(num==0){
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_twoplusone(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}
	
	//���͂�1�̂Ƃ��͒�Ď�@�̃p�^�[���𓊉e(����g)
	else if(num==1){
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_new(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;
	
		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//���͂�2�̂Ƃ��͒�Ď�@�̃p�^�[���𓊉e(�����g)
	else if(num==2){
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_newhigh(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//���͂�3�̂Ƃ��̓e�X�g�摜�𓊉e
	else if(num==3){
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_test(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	else if(num==4){
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_normalsin(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//����ȊO�̏ꍇ�͊�����@�̃p�^�[���𓊉e
	else{
		//�摜����
		vector<Mat1b> input;
		int i,j=0;
		create_image_old(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//���e
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	
	

	return 0;
}