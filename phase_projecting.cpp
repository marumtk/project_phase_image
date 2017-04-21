#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/opencv_lib.hpp>
#include "Highspeedproj.h"
#include <vector>
#include "basler.h"
#include "Webcam.h"
#include <thread>

using namespace std;
using namespace cv;

//テスト画像を投影するプログラム
void create_image_test(vector<Mat1b> &result){
	vector<string> files;
	files.push_back("test.bmp");
	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}
}

// sin波の画像を生成するプログラム
void create_image_new(vector<Mat1b> &result){
	const string base = "sinimage_";
	vector<string> files;

	files.push_back(base+"1.bmp");
	//files.push_back(base+"2.bmp");
	//files.push_back(base+"3.bmp");
	//files.push_back("reference.bmp");

	vector<string>::iterator p = files.begin();
	for(;p!=files.end();++p){
		Mat img = imread(*p,0);
		result.push_back(img);
	}


};

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



int main(){
	cout << "提案手法で計測（低周波）するときは1を" << endl;
	cout << "提案手法で計測（高周波）するときは2を" << endl;
	cout << "テスト画像を投影するときは3を" << endl;
	cout << "既存手法で計測するときはそれ以外の整数を" << endl;
	cout << "入力して下さい" << endl;
	int num;
	cin >> num;
	
	//入力が1のときは提案手法のパターンを投影(低周波)
	if(num==1){
		//画像生成
		vector<Mat1b> input;
		int i,j=0;
		create_image_new(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;
	
		while(true){	
			for(i=0;i<input.size();i++){
				//投影
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//入力が2のときは提案手法のパターンを投影(高周波)
	else if(num==2){
		//画像生成
		vector<Mat1b> input;
		int i,j=0;
		create_image_newhigh(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//投影
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//入力が3のときはテスト画像を投影
	if(num==3){
		//画像生成
		vector<Mat1b> input;
		int i,j=0;
		create_image_test(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//投影
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	//それ以外の場合は既存手法のパターンを投影
	else{
		//画像生成
		vector<Mat1b> input;
		int i,j=0;
		create_image_old(input);

		HighSpeedProj hsproj;
		hsproj.connectProj();
		//thread temp1,temp2;

		while(true){	
			for(i=0;i<input.size();i++){
				//投影
				hsproj.sendImage(input[i]);
			}
			if(_kbhit()) break;
		}
	}

	
	

	return 0;
}