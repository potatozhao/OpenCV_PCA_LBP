#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <math.h>
#include<stdio.h>
#include<string>
#include<sstream>
using namespace cv;
static int last[16][255];
Mat LBPTrain(Mat img)
{
	int LBPReturn[16][255];
	int LBPMain[80][80];
	for(int i =1;i<79;i++)
	{
		for (int j = 1;j<79;j++)
		{
			int value = 0;
			if(img.at<float>(i-1,j-1)>=img.at<float>(i,j))
			{
				value = value+1;
			}
			if(img.at<float>(i-1,j)>=img.at<float>(i,j))
			{
				value = value+2;
			}
			if(img.at<float>(i-1,j+1)>=img.at<float>(i,j))
			{
				value = value+4;
			}
			if(img.at<float>(i,j-1)>=img.at<float>(i,j))
			{
				value = value+8;
			}
			if(img.at<float>(i,j+1)>=img.at<float>(i,j))
			{
				value = value+16;
			}
			if(img.at<float>(i+1,j-1)>=img.at<float>(i,j))
			{
				value = value+32;
			}
			if(img.at<float>(i+1,j)>=img.at<float>(i,j))
			{
				value = value+64;
			}
			if(img.at<float>(i+1,j+1)>=img.at<float>(i,j))
			{
				value = value+128;
			}
			LBPMain[i][j] = value;
		}
	}
	for(int i=0;i<16;i++)
	{
		for(int j = 0;j<255;j++)
		{
			LBPReturn[i][j] = 0;
		}
	}
	for(int i = 0;i<4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			for(int m = 1;m<19;m++)
			{
				for(int n = 1;n<19;n++)
				{
					int num;
					num = LBPMain[i*20+m][j*20+n];
					LBPReturn[i*j+j][num] = LBPReturn[i*j+j][num]+1;
				}
			}
		}
	}
	Mat img(16,255,CV_32FC1);
	for(int i=0;i<16;i++)
	{
		for(int j = 0;j<255;j++)
		{
			img.at<float>(i,j) = LBPReturn[i][j];
		}
	}
	return img;
}
float LastValue(Mat img1,Mat img2)
{
	float a[16];
	float b[16];
	float c[16];
	float d = 0;
	int xxx = 0;
	for(int i = 0;i<16;i++)
	{
		a[i] = 0;
		b[i] = 0;
		c[i] = 0;
		for(int j = 0;j<255;j++)
		{
			a[i] = img2.at<float>(i,j) * img1.at<float>(i,j) + a[i];
			b[i] = img1.at<float>(i,j) * img1.at<float>(i,j) + b[i];
			c[i] = img2.at<float>(i,j) * img2.at<float>(i,j) + c[i];
		}
		if(b[i]==0||c[i]==0)
		{
			d = d+1;
			xxx = 1;
		}
		else
		{
			d = a[i]/(sqrt(b[i])*sqrt(c[i]))+d;
			xxx = a[i]/(sqrt(b[i])*sqrt(c[i]));
		}
	}
	float n = d/16;
	n = n*n*n;
	return n;
}
std::string test(Mat img1,Mat img2)/*(char *imagename1,char *imagename2)*/
{
	//Mat img;
	//Mat img1(80,80,CV_32FC1);
	//Mat img2(80,80,CV_32FC1);
	//img = imread(imagename1,0);
	//for(int i=0;i<80;i++)
	//{
	//	for(int j = 0;j<80;j++)
	//	{
	//		img1.at<float>(i,j) = img.at<uchar>(i,j);
	//	}
	//}
	//img = imread(imagename2,0);
	//for(int i=0;i<80;i++)
	//{
	//	for(int j = 0;j<80;j++)
	//	{
	//		img2.at<float>(i,j) = img.at<uchar>(i,j);
	//	}
	//}
	std::stringstream lastnum;
	std::string last1;

	Mat num1 = LBPTrain(img1);
	Mat num2 = LBPTrain(img2);
	int num = 100*LastValue(num1,num2);
	lastnum << num;
	lastnum>>last1;
	last1 = last1+"%";
	return last1;
}