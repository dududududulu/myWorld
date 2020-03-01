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
	////如果是单通道，转为三通道
	//if (1 == img.channels())
	//	cvtColor(img, img, COLOR_GRAY2BGR);

	///**
	//核心：
	//*	*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * c)=new_val
	//*	这行代码是解析出来image的第i行第j列(即坐标为[j,i])第c通道，然后就可以对它进行赋值了。
	//*/
	//for (int k = 0; k < 255; ++k)
	//{
	//	for (int i = 0; i < img.rows; ++i)s
	//		for (int j = 0; j < img.cols; ++j)
	//		{
	//			//对第0个通道进行赋值操作，也就是blue通道
	//			*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * 0) = (200 + (i + j) / 8 + k) % 256;

	//			//对第2个通道进行赋值操作，也就是green通道
	//			*(img.data + img.step[0] * i + img.step[1] * j + img.elemSize1() * 1) = (180 + (i + j) / 8 + k) % 256;

	//			//对第3个通道进行赋值操作，也就是red通道
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
