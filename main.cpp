#include "basler.h"
#include "Webcam.h"
#include "XimeaXiQ.h"
#include "HighSpeedProj.h"
#include<conio.h>




//*******************************************************************************//
//********�v���W�F�N�^�ƃJ�����̃L�����u���[�V�����p�̉摜�擾�v���O����*********//
//*******************************************************************************//

#define CalibrationMode 1
#define ProjecterCalibrationMode 1



//�֐���`
//�l�p�`��`�悷��(�`�悷��摜�A�����`�̃T�C�Y�A�`��J�n�ʒu�A��������)
void Square_paint(cv::Mat &paint_image, const int square_size, const cv::Point offset_point, bool flag);
//�`�F�b�J�[�p�^�[���𐶐�����(��������摜�A�`�F�b�J�[�p�^�[���̉��̊i�q�_�̐��A�`�F�b�J�[�p�^�[���̏c�̊i�q�_�̐��A���n�܂�̃`�F�b�J�[�p�^�[�������n�܂�̃`�F�b�J�[�p�^�[����)
void Calibration_pattern(cv::Mat &calib_image, const unsigned int cheker_width, const unsigned int cheker_height, bool flag);


int main()
{
	
	XimeaXiQ Ximea;
	basler Basler;
#if ProjecterCalibrationMode

	bool white_black_flag = true;
	cv::Mat image1(PROJ_HEIGHT, PROJ_WIDTH, CV_8UC1, cv::Scalar::all(255)), image2;
	Calibration_pattern(image1,7,5, true);
	Calibration_pattern(image2,7,5, false);
	cv::imshow("image",image1);
	cv::imshow("image",image2);
	cv::waitKey(1);
	std::cout << "�`�F�b�J�[�p�^�[����������" << std::endl;

	//�v���W�F�N�^���g�킸�摜�����B��Ƃ��̓R�����g�A�E�g
	//HighSpeedProj Highspeedproj;
	//Highspeedproj.connectProj();
	//auto projection_image1 = image1.clone();
	//auto projection_image2 = image2.clone();
#endif
	//cv::imwrite("checker_image.bmp", image1);
	
	std::vector<cv::Mat> ImageBufferRight(0);
	std::vector<cv::Mat> ImageBufferLeft(0);
	
	cv::Mat XimeaImage;
	cv::Mat BaslerImage;

	Basler.camera_init();

	std::cout << "������@" << std::endl;
	std::cout << "w : �摜�擾" << std::endl;
	std::cout << "p : ���݂̉摜�����m�F" << std::endl;
	std::cout << "c : �B�������摜���ꖇ������" << std::endl;
	std::cout << "q : �I��" << std::endl;

	

	while(true)
	{
/*
#if ProjecterCalibrationMode
		if(white_black_flag == true)
		{
		//�v���W�F�N�^���g�킸�摜�����B��Ƃ��̓R�����g�A�E�g
		//	Highspeedproj.sendImage(projection_image1);
		}
		else
		{
		//�v���W�F�N�^���g�킸�摜�����B��Ƃ��̓R�����g�A�E�g
		//Highspeedproj.sendImage(projection_image2);
		}
#endif
*/
		Basler.cap_color(BaslerImage);
		Ximea.getFrame(XimeaImage);
		
		if(XimeaImage.data != 0)
		{
			cv::imshow("RightImageWindow",XimeaImage);
		}
		if(BaslerImage.data != 0)
		{
			cv::imshow("LeftImageWindow",BaslerImage);
		}
		int key = cv::waitKey(1);
		//�B���I��
		if(key == 'q')
		{
			std::cout << "�I��" << std::endl;
			break;
		}
		//�ꖇ�擾����
		else if(key == 'w')
		{
			
			ImageBufferLeft.push_back(BaslerImage.clone());
			ImageBufferRight.push_back(XimeaImage.clone());
			auto index = ImageBufferLeft.size();
			cv::imshow("SaveImgae1",ImageBufferLeft[index-1]);
			cv::imshow("SaveImgae2",ImageBufferRight[index-1]);
#if ProjecterCalibrationMode
			if(white_black_flag == true)
			{
				white_black_flag = false;
			}
			else
			{
				white_black_flag = true;
			}
#endif
			std::cout << "�摜�擾����" << std::endl;
		}
		//���݂̎B�������m�F
		else if(key == 'p')
		{
			std::cout << "���� " << ImageBufferLeft.size() << " ���B������Ă��܂�" << std::endl;
		}
		//�B�������s�����������
		else if(key == 'c')
		{
			if(ImageBufferLeft.size() != 0)
			{
				ImageBufferLeft.pop_back();
				ImageBufferRight.pop_back();
				std::cout << "�摜���ꖇ�������܂���" << std::endl;
			}
			else
			{
			std::cout << "�������摜������܂���" << std::endl;
			}
		}

		key = 0;


	}

	char Filename[100];
	char _filename1[] = "data/left/left";
	char _filename2[] = "data/right/right";
	char fileext[] = "bmp";

	std::cout << "�摜�����o���J�n" << std::endl;

	for(int i=0; i < ImageBufferLeft.size(); i++)
	{
		sprintf_s(Filename,"%s%02d.%s",_filename1,i,fileext);
		imwrite(Filename,ImageBufferLeft[i]);
	}
	for(int i=0; i < ImageBufferRight.size(); i++)
	{
		sprintf_s(Filename,"%s%02d.%s",_filename2,i,fileext);
		imwrite(Filename,ImageBufferRight[i]);
	}
	cv::destroyAllWindows();
	

	return 1;
}




// �`�F�b�J�[�p�^�[���̐���
void Calibration_pattern(cv::Mat &calib_image, const unsigned int cheker_width, const unsigned int cheker_height, bool color_flag)
{
	auto _width = cheker_width - 1;
	auto _height = cheker_height - 1;
	const unsigned int cheker_size = 80;//80pixel�̃`�F�b�J�[�p�^�[���𐶐�
	auto _cheker_width = (_width + 2) * cheker_size; // �`�F�b�J�[�p�^�[���S�̂̉���(pixel)�A[+1]�̗��R�͊i�q�_�̐�+1�`�F�X�{�[�h�����邩��
	auto _cheker_height = (_height + 2) * cheker_size; // �`�F�b�J�[�p�^�[���S�̂̏c��(pixel)
	unsigned int _image_offset_width = (PROJ_WIDTH - _cheker_width) / 2; //�I�t�Z�b�g�̌v�Z
	unsigned int _image_offset_height = (PROJ_HEIGHT - _cheker_height) / 2;  //�I�t�Z�b�g�̌v�Z
	calib_image.create(PROJ_HEIGHT,PROJ_WIDTH,CV_8UC1);
	std::cout << "�I�t�Z�b�g��(x, y) = (" << _image_offset_width << ", " << _image_offset_height << ")" <<std::endl; 
	if(color_flag == true)
	{
		for(int y = 0; y < _height + 2; y++)
		{
			for(int x = 0; x < _width + 2; x++)
			{
				if((y % 2) == 0)
				{
					if((x % 2) == 1)
					{
						//�h��Ԃ��̈悪�͈͂𒴂��Ȃ����ǂ����̃`�F�b�N
						if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
						{
							Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), true);
						}
					}
					else
					{
						if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
						{
							Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), false);
						}	
					}
				}
				else
				{
					if((x % 2) == 1)
					{
						if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
						{
							Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), false);
						}
					}
					else
					{
						if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
						{
							Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), true);
						}	
					}
				}
			}
		}
			
	}
	else
	{
		{
			for(int y = 0; y < _height + 2; y++)
			{
				for(int x = 0; x < _width + 2; x++)
				{
					if((y % 2) == 0)
					{
						if((x % 2) == 1)
						{
							//�h��Ԃ��̈悪�͈͂𒴂��Ȃ����ǂ����̃`�F�b�N
							if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
							{
								Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), false);
							}
						}
						else
						{
							if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
							{
								Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), true);
							}	
						}
					}
					else
					{
						if((x % 2) == 1)
						{
							if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
							{
								Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), true);
							}
						}
						else
						{
							if(((x + 1) * cheker_size + _image_offset_width) < PROJ_WIDTH && (y + 1) * cheker_size + _image_offset_height < PROJ_HEIGHT)
							{
								Square_paint(calib_image, cheker_size, cv::Point(x * cheker_size + _image_offset_width, y * cheker_size + _image_offset_height), false);
							}	
						}
					}
				}
			}

		}
	}
}

void Square_paint(cv::Mat &paint_image, const int square_size, const cv::Point offset_point, bool flag)
{
	if(flag == true)
	{
		for(int y = 0;y<square_size;y++)
		{
			for(int x = 0;x<square_size;x++)
			{
				paint_image.at<unsigned char>(offset_point.y + y, offset_point.x + x) = 255;
			}
		}
	}
	else
	{
		for(int y = 0;y<square_size;y++)
		{
			for(int x = 0;x<square_size;x++)
			{
				paint_image.at<unsigned char>(offset_point.y + y, offset_point.x + x) = 0;
			}
		}
	}
}
