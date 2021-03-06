// opencv_algo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

/*
int main() {
	//IplImage *test;
	//test = cvLoadImage("e:\\Src\\project\\opencv_cpp\\opencv_algo\\opencv_algo\\pic.png");
	//test = cvLoadImage("pic.png");
	Mat img1 = imread("pic.png", CV_LOAD_IMAGE_GRAYSCALE);
	if (img1.empty())
	{
		cout << "Cannot load image!" << endl;
		return -1;
	}

	imshow("Original", img1);  // Original

							   // Create mask image
	Mat mask(img1.rows, img1.cols, CV_8UC1, Scalar(0, 0, 0));
	circle(mask, Point(img1.rows / 2, img1.cols / 2), 150, 255, -1);
	imshow("Mask", mask);

	// perform AND
	Mat r;
	bitwise_and(img1, mask, r);

	// fill outside with white
	const uchar white = 255;
	for (int i = 0; i < r.rows; i++)
		for (int j = 0; j < r.cols; j++)
			if (!mask.at<uchar>(i, j))
				r.at<uchar>(i, j) = white;

	imshow("Result", r);

	waitKey(0);
	return 0;
}
*/

//直方图计算函数
void histogramcaculation(const Mat& Image, Mat& histoImage)
{
	int histSize = 255;

	//对（B,G,R)设置范围
	float range[] = { 0,256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;
	vector<Mat> bgr_planes;
	split(Image, bgr_planes);

	//计算各个直方图
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize,
		&histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize,
		&histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize,
		&histRange, uniform, accumulate);

	//为B,G和R绘制直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	//将结果归一化为[0, histImage.rows]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//为每个通道进行绘制
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}

	histoImage = histImage;
}
/*
void processhistogram()
{
	Mat src, histImage, imageq;

	//将图像划分为三个部分（B、G和R）
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	//显示结果
	imshow("Source Image", src);

	//计算原始图像每个通道的直方图
	histogramcaculation(src, histImage);

	//显示每个颜色通道的直方图
	imshow("Color Image Histogram", histImage);

	//均衡化图像
	//直方图均衡化应用与每个通道
	equalizeHist(bgr_planes[0], bgr_planes[0]);
	equalizeHist(bgr_planes[1], bgr_planes[1]);
	equalizeHist(bgr_planes[2], bgr_planes[2]);

	//将这些均衡化的图像通道合并得到其均衡化图像
	merge(bgr_planes, imageq);

	//显示均衡化图像
	imshow("Equalized Image", imageq);

	//计算每个均衡化图像通道的直方图
	histogramcaculation(imageq, histImage);

	//显示均衡化图像的直方图
	imshow("Equalized Color Image Histogram", histImage);
}
*/

int main()
{
	//Mat src, imageq;
	//Mat histImage;
	Mat src;

	//读取原始图像
	//src = imread("pic.png");
	src = imread("checkerboard.png");
	if (!src.data)
	{
		printf("Error image!\n");
		exit(1);
	}

	/*Smooth Filter
	{
		// Apply the filters
		Mat dst, dst2;
		GaussianBlur(src, dst, Size(9, 9), 0, 0);
		medianBlur(src, dst2, 9);

		// Show the results
		namedWindow(" ORIGINAL ", WINDOW_AUTOSIZE);
		imshow(" ORIGINAL ", src);
		namedWindow(" GAUSSIAN BLUR ", WINDOW_AUTOSIZE);
		imshow(" GAUSSIAN BLUR ", dst);
		namedWindow(" MEDIAN BLUR ", WINDOW_AUTOSIZE);
		imshow(" MEDIAN BLUR ", dst2);
	}
	*/

	/*Sharpen
	{
		// Apply Sobel and Laplacian
		Mat dst, dst2;
		Sobel(src, dst, -1, 1, 1);
		Laplacian(src, dst2, -1);

		// Show the results
		namedWindow(" ORIGINAL ", WINDOW_AUTOSIZE);
		imshow(" ORIGINAL ", src);
		namedWindow(" SOBEL ", WINDOW_AUTOSIZE);
		imshow(" SOBEL ", dst);
		namedWindow(" LAPLACIAN ", WINDOW_AUTOSIZE);
		imshow(" LAPLACIAN ", dst2);
	}
	*/

	/*Pyramids
	{
		// Apply two times pyrDown
		Mat dst, dst2;
		pyrDown(src, dst);
		pyrDown(dst, dst2);

		// Show the results
		namedWindow(" ORIGINAL ", WINDOW_AUTOSIZE);
		imshow(" ORIGINAL ", src);
		namedWindow(" 1st PYRDOWN ", WINDOW_AUTOSIZE);
		imshow(" 1st PYRDOWN ", dst);
		namedWindow(" 2st PYRDOWN ", WINDOW_AUTOSIZE);
		imshow(" 2st PYRDOWN ", dst2);

		// Apply two times pyrUp
		pyrUp(dst2, dst);
		pyrUp(dst, src);

		// Show the results
		namedWindow(" NEW ORIGINAL ", WINDOW_AUTOSIZE);
		imshow(" NEW ORIGINAL ", dst2);
		namedWindow(" 1st PYRUP ", WINDOW_AUTOSIZE);
		imshow(" 1st PYRUP ", dst);
		namedWindow(" 2st PYRUP ", WINDOW_AUTOSIZE);
		imshow(" 2st PYRUP ", src);
	}
	*/

	/*morphological*/
	{
		// Apply the filters
		Mat dst, dst2, dst3;
		inRange(src, Scalar(0, 0, 100), Scalar(40, 30, 255), dst);

		Mat element = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
		dilate(dst, dst2, element);
		erode(dst2, dst3, element);
		//morphologyEx(src, dst3, MORPH_OPEN, element);

		// Show the results
		namedWindow(" ORIGINAL ", WINDOW_AUTOSIZE);
		imshow(" ORIGINAL ", src);
		namedWindow(" SEGMENTED ", WINDOW_AUTOSIZE);
		imshow(" SEGMENTED ", dst);
		namedWindow(" DILATION ", WINDOW_AUTOSIZE);
		imshow(" DILATION ", dst2);
		namedWindow(" EROSION ", WINDOW_AUTOSIZE);
		imshow(" EROSION ", dst3);
	}

	//等待用户退出程序
	waitKey();

	return 0;
}