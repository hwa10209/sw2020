#include<iostream>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>	//cvtColor 사용하기 위해 필요
using namespace cv;

unsigned char overflow(int number)
{
	if (number > 255)
		return 255;
	else if (number < 0)
		return 0;
	else
		return number;
}
int main() {
	Mat img = imread("lena.jpg", IMREAD_COLOR);
	imshow("image", img);

	Mat grayimg(img.rows, img.cols, CV_8UC1);
	cvtColor(img, grayimg, COLOR_BGR2GRAY);
	imshow("grayimage", grayimg);

	int error;
	for (int i = 0; i < grayimg.rows; i++)
		for (int j = 0; j < grayimg.cols; j++) {
			if (grayimg.at<unsigned char>(i, j) > 127)
				error = grayimg.at<unsigned char>(i, j) - 255;
			else
				error = grayimg.at<unsigned char>(i, j);
			if (j != 0) {
				grayimg.at<unsigned char>(i, j - 1) += 0;											//left
				if (i != grayimg.rows - 1) 
					grayimg.at<unsigned char>(i + 1, j - 1)= overflow(grayimg.at<unsigned char>(i + 1, j - 1) + (error * 3 / 16)); //leftdown 
			}	
			if (i != grayimg.rows - 1) {
				grayimg.at<unsigned char>(i + 1, j) = overflow(grayimg.at<unsigned char>(i + 1, j)+(error * 5 / 16)); //down
				if (j != grayimg.cols - 1) 
					grayimg.at<unsigned char>(i + 1, j + 1) = overflow(grayimg.at<unsigned char>(i + 1, j + 1)+(error * 1 / 16)); //rightdown
			}	
			if (j != grayimg.cols - 1)	
				grayimg.at<unsigned char>(i, j + 1) = overflow(grayimg.at<unsigned char>(i, j + 1)+(error * 7 / 16));//right		
		}			
	for (int i = 0; i < grayimg.rows; i++)
		for (int j = 0; j < grayimg.cols; j++) {
			if (grayimg.at<unsigned char>(i, j) > 127)
				grayimg.at<unsigned char>(i, j) = 255;
			else
				grayimg.at<unsigned char>(i, j) = 0;
		}

	imshow("ditheredimage", grayimg);
	imwrite("ditheredimage.jpg", img);
	waitKey(0);
	return 0;
}