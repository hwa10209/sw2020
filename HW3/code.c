#include<iostream>
#include<stdlib.h>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>	//cvtColor 사용하기 위해 필요
using namespace cv;

void FindZeroCrossings(Mat& laplacian, Mat& zero_crossings);

/*
1) 입력영상을 read 한다.
2) 영상을 흑백으로 변환한다.
3) Gaussian smoothing 으로 영상을 blur 한다. (잡음도 제거)
4) Blur된 영상에 Laplacian filtering 적용한다.
5) Edge를 찾기위해 Zero crossing 실행
*/

int main() {
	Mat img,				//for read
		laplacian,			//for GaussianBlur
		abs_laplacian,		//for Laplacian
		cvt_laplacian,		//to use float in ZeroCrossing
		zero[5];				//for ZeroCrossing
	

	for (int i = 0; i < 5; i++)
	{
		img = imread("lena.jpg", IMREAD_COLOR);
		cvtColor(img, img, COLOR_BGR2GRAY);
		//imshow("grayimage", img);

		GaussianBlur(img, img, Size(5, 5), 1.0+i, 0, BORDER_DEFAULT);
		imshow("Bluredimg", img);


		Laplacian(img, laplacian, CV_16S, 3, 1, 0, BORDER_DEFAULT);

		
		convertScaleAbs(laplacian, abs_laplacian);
		imshow("Laplacian", abs_laplacian);

		laplacian.convertTo(cvt_laplacian, CV_32FC1);
		FindZeroCrossings(cvt_laplacian, zero[i]);		
	}
	imwrite("sigam = 1,0.jpg", zero[0]);
	imwrite("sigam = 2,0.jpg", zero[1]);
	imwrite("sigam = 3,0.jpg", zero[2]);
	imwrite("sigam = 4,0.jpg", zero[3]);
	imwrite("sigam = 5,0.jpg", zero[4]);
	waitKey(0);
	return 0;
}
void FindZeroCrossings(Mat& laplacian, Mat& zero_crossings)
{
	Mat* result = new Mat(laplacian.size(), CV_8U, Scalar(0));
	zero_crossings = *result;
	int image_rows = laplacian.rows;
	int image_channels = laplacian.channels();
	int values_on_each_row = laplacian.cols * image_channels;
	float laplacian_threshold = 20.0;
	// Find Zero Crossings
	for (int row = 1; row < image_rows; row++) {
		float* prev_row_pixel = laplacian.ptr<float>(row - 1) + 1;
		float* curr_row_pixel = laplacian.ptr<float>(row);
		uchar* output_pixel = zero_crossings.ptr<uchar>(row) + 1;
		for (int column = 1; column < values_on_each_row; column++)
		{
			float prev_value_on_row = *curr_row_pixel;
			curr_row_pixel++;
			float curr_value = *curr_row_pixel;
			float prev_value_on_column = *prev_row_pixel;
			float difference = 0.0;
			if (((curr_value > 0) && (prev_value_on_row < 0)) ||
				((curr_value < 0) && (prev_value_on_row > 0)))
				difference = abs(curr_value - prev_value_on_row);
			if ((((curr_value > 0) && (prev_value_on_column < 0)) ||
				((curr_value < 0) && (prev_value_on_column > 0))) &&
				(abs(curr_value - prev_value_on_column) > difference))
				difference = abs(curr_value - prev_value_on_column);
			*output_pixel = (difference > laplacian_threshold) ? 255 : 0;// (int) ((100 * difference) / laplacian_threshold);
			prev_row_pixel++;
			output_pixel++;
		}
	}
}
