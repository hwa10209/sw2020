#include<iostream>
#include<stdlib.h>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>	//cvtColor 사용하기 위해 필요

#include<math.h>
#define PI 3.1415926535897

using namespace cv;

void DCT_basis(Mat& DCT_basisout,int u, int v);
void DCT(Mat& beforeDCT, Mat& afterDCT, float basis[][8][8][8]);
void IDCT(Mat& beforeIDCT, Mat& afterIDCT, float basis[][8][8][8],int useSize);

/*
1) 2D DCT에 사용될 8x8 DCT basis를 구한다. (전체 64개) 
2) 입력영상을 read 하여 graylevel로 변환한다. 
3) 영상의 8x8 영역(block)에 대하여 f(i,j)를 8x8 DCT basis 를 이용하여 8x8 주파수 공간 F(u,v)로 변환한다. 
4) F(u,v)를 다시 IDCT로 8x8 영상을 다시 복원한다. - 이때, F(u,v)의 8x8, 4x4, 2x2 값들만 사용하여 비교 
5) 영상 전체에 대하여 3)-4) 과정을 반복한다. 
6) 입력 1장 영상에 대하여 복원된 영상 3장을 각각 저장한다.
*/

int main() {
	Mat temp(8, 8, CV_32FC1);
	float saveBasis[8][8][8][8] = { 0, };	//[v][u][j][i]	외부행,외부열, 내부행, 내부열
	
	for (int V=0; V < 8; V++) {				//for all 'v's
		for (int U=0; U < 8; U++) {			//for all 'u's
			DCT_basis(temp, U, V);			//1) 2D DCT에 사용될 8x8 DCT basis를 구한다. (전체 64개)
			memcpy(&saveBasis[V][U], temp.data, 8 * 8 * sizeof(float));
		}
	}
	
	/*
	for(int y=0;y<8;y++){
		for (int t=0; t < 8; t++){				//DCT basis 결과 확인용
			for(int t2=0;t2<8;t2++){
				printf("%6.3f ", saveBasis[0][y][t][t2]);
			}
			printf("\n");
		}
		printf("\n");
	}
	*/
	
	Mat img = imread("lena.jpg", IMREAD_COLOR);	//2) 입력영상을 read 하여 graylevel로 변환한다.
	cvtColor(img, img, COLOR_BGR2GRAY);
	Mat comp(img.rows, img.cols, CV_8UC1);
	imshow("lena", img);
	for (int r = 0; r < img.rows/8; r++) {
		for (int c = 0; c < img.cols/8; c++) {	//이미지를 8*8사이즈로 잘라서 이용(이미지 전체에 대하여)
			
			
			Mat cut = img(Range(r * 8,r * 8 + 8), Range(c * 8,c * 8 + 8));
			Mat DCTblock(8, 8, CV_32FC1);		
			DCT(cut, DCTblock, saveBasis);		//3) f(i, j)를 8x8 DCT basis이용, F(u, v)로 변환한다.

			Mat restored(8, 8, CV_8UC1);
			IDCT(DCTblock, restored, saveBasis,8);//4) F(u, v)를 다시 IDCT로 8x8 영상을 다시 복원한다.	(8*8, 4*4, 2*2에 대해 확인)
			restored.copyTo(comp(Range(r * 8, r * 8 + 8), Range(c * 8, c * 8 + 8)));

		}										//5) 영상 전체에 대하여 과정을 반복한다.
	}											//6) 복원된 영상 3장을 각각 저장한다.

	imshow("restored_8*8", comp);
	imwrite("restored_8*8.jpg",comp );
	
	/*											//DCT결과 확인용
	uchar data[64] = {
		182,196,199,201,203,201,199,173,
		175,180,176,142,148,152,148,120,
		148,118,123,115,114,107,108,107,
		115,110,110,112,105,109,101,100,
		104,106,106,102,104,95 ,98 ,105,
		99 ,115,131,104,118,86 ,87 ,133,
		112,154,154,107,140,97 ,88 ,151,
		145,158,178,123,132,140,138,133
	}; 
	Mat cut(Size(8, 8), CV_8UC1, data);
	Mat DCTblock(8, 8, CV_32FC1);
	DCT(cut, DCTblock, saveBasis);
	float test[8][8];
	memcpy(&test, DCTblock.data, 8 * 8 * sizeof(float));
	for (int t = 0; t < 8; t++) {
		for (int t2 = 0; t2 < 8; t2++) {
			printf("%7.3f ", test[t][t2]);

		}
		printf("\n");
	}
	*/
	
	waitKey(0);
	return 0;
}


//u, i : 열, v,j :행
void DCT_basis(Mat& DCT_basisout,  int u, int v) {
	float c1, c2;
	c1 = (u == 0) ? sqrt(2) / 2 : 1;
	c2 = (v == 0) ? sqrt(2) / 2 : 1;
	
	for (int j = 0; j < 8; j++) {
		float* target = DCT_basisout.ptr<float>(j);
		for (int i = 0; i < 8; i++) {
			*target = c1 * c2 / 4 * cos((2 * i + 1) * u * PI / 16) * cos((2 * j + 1) * v * PI / 16);
			target++;
		}
	}
}

void DCT(Mat& beforeDCT, Mat& afterDCT, float basis[][8][8][8]){
	float summation;
	for (int V = 0; V < 8; V++) {				//for all 'v's
		float* vafterDCT = afterDCT.ptr<float>(V);
		for (int U = 0; U < 8; U++) {			//for all 'u's
			summation = 0;
			for (int j = 0; j < 8; j++) {
				uchar* vbeforeDCT = beforeDCT.ptr<uchar>(j);
				for (int i = 0; i < 8; i++) {
					summation += (*vbeforeDCT) * (basis[V][U][j][i]);
					vbeforeDCT++;
				}
			}
			*vafterDCT = summation;
			vafterDCT++;
		}
	}
}

void IDCT(Mat& beforeIDCT, Mat& afterIDCT, float basis[][8][8][8], int useSize)
{
	float summation;
	for (int j = 0; j < 8; j++) {				//for all 'j's
		uchar* vafterIDCT = afterIDCT.ptr<uchar>(j);
		for (int i = 0; i < 8; i++) {			//for all 'i's
			summation = 0;
			for (int V = 0; V < 8; V++) {
				float* vbeforeIDCT = beforeIDCT.ptr<float>(V);
				for (int U = 0; U < 8; U++) {
					summation += ((U >= useSize) | (V >= useSize))?  0 : (*vbeforeIDCT) * (basis[V][U][j][i]);
					if (summation >= 255)
						summation = 255;
					else if (summation <= 0)
						summation = 0;
					vbeforeIDCT++;
				}
			}
			*vafterIDCT = summation;
			vafterIDCT++;
		}
	}

}
