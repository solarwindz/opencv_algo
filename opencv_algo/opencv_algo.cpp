// opencv_algo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	IplImage *test;
	//test = cvLoadImage("e:\\Src\\project\\opencv_cpp\\opencv_algo\\opencv_algo\\pic.png");
	test = cvLoadImage("pic.png");
	cvNamedWindow("Test_demo", 1);
	cvShowImage("Test_demo", test);
	cvWaitKey(0);
	cvReleaseImage(&test);
	return 0;
}
