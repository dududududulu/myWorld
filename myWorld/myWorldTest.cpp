#include <iostream>
#include "settings.h"
#include "Concept.h"
#include "Effect.h"
#include "Object.h"
#include "Entity.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	//all_test();
	cout << "1" << endl;
	Cube cube(1);
	cout << "cube built" << endl;
	/*Observer eye;
	cout << "eye established" << endl;
	cube.display(&eye);
	cout << "cube mapped to the eye" << endl;
	eye.display();
	cout << "eye displayed" << endl;*/

	//Mat img(256, 256, CV_8UC3);
	////Mat img_backup = img.clone();
	////����ǵ�ͨ����תΪ��ͨ��
	//if (1 == img.channels())
	//	cvtColor(img, img, COLOR_GRAY2BGR);

	///**
	//���ģ�
	//*	*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * c)=new_val
	//*	���д����ǽ�������image�ĵ�i�е�j��(������Ϊ[j,i])��cͨ����Ȼ��Ϳ��Զ������и�ֵ�ˡ�
	//*/
	//for (int k = 0; k < 255; ++k)
	//{
	//	for (int i = 0; i < img.rows; ++i)s
	//		for (int j = 0; j < img.cols; ++j)
	//		{
	//			//�Ե�0��ͨ�����и�ֵ������Ҳ����blueͨ��
	//			*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * 0) = (200 + (i + j) / 8 + k) % 256;

	//			//�Ե�2��ͨ�����и�ֵ������Ҳ����greenͨ��
	//			*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * 1) = (180 + (i + j) / 8 + k) % 256;

	//			//�Ե�3��ͨ�����и�ֵ������Ҳ����redͨ��
	//			*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * 2) = (30 + (i + j) / 10 + k) % 256;
	//		}
	//	imshow("img_rst", img);
	//	cout << k << endl;
	//	if (k == 112) break;
	//}
	////imshow("img_src", img_backup);
	//waitKey();

	cout << "Task Over" << endl;

	//int i, j;
	//for (i = 63; i < 250; ++i)
	//{
	//	for (j = 120; j < 320; ++j)
	//	{
	//		a(i, j) = 100;
	//	}
	//}

	return 0;
}
