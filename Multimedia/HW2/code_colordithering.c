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

	Mat BGR[3];
	split(img, BGR);																//split
	imshow("Blue", BGR[0]); 	imshow("Green", BGR[1]);	imshow("Red", BGR[2]);

	int error;
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < BGR[k].rows; i++)
			for (int j = 0; j < BGR[k].cols; j++) {
				error = (BGR[k].at<unsigned char>(i, j) > 127) ? BGR[k].at<unsigned char>(i, j) - 255 : BGR[k].at<unsigned char>(i, j);
				if (j != 0) {
					BGR[k].at<unsigned char>(i, j - 1) += 0;											//left
					if (i != BGR[k].rows - 1)
						BGR[k].at<unsigned char>(i + 1, j - 1) = overflow(BGR[k].at<unsigned char>(i + 1, j - 1) + (error * 3 / 16)); //leftdown 
				}
				if (i != BGR[k].rows - 1) {
					BGR[k].at<unsigned char>(i + 1, j) = overflow(BGR[k].at<unsigned char>(i + 1, j) + (error * 5 / 16)); //down
					if (j != BGR[k].cols - 1)
						BGR[k].at<unsigned char>(i + 1, j + 1) = overflow(BGR[k].at<unsigned char>(i + 1, j + 1) + (error * 1 / 16)); //rightdown
				}
				if (j != BGR[k].cols - 1)
					BGR[k].at<unsigned char>(i, j + 1) = overflow(BGR[k].at<unsigned char>(i, j + 1) + (error * 7 / 16));//right		
			}
		for (int i = 0; i < BGR[k].rows; i++)										//step2
			for (int j = 0; j < BGR[k].cols; j++)
				BGR[k].at<unsigned char>(i, j) = (BGR[k].at<unsigned char>(i, j) > 127) ? 255 : 0;
	}
	
	imshow("ditheredBlue", BGR[0]); 	imshow("ditheredGreen", BGR[1]);	imshow("ditheredRed", BGR[2]);
	Mat ditheredBGR;
	merge(BGR, 3, ditheredBGR);														//merge
	imshow("ditheredBGR", ditheredBGR);
	waitKey(0);
	return 0;
}

