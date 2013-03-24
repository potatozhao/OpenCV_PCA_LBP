#include "stdafx.h"
#include "test.h"
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
int test1234()
{
	Mat ImgTotal(210,6400,CV_32FC1);
	for(int i = 0;i<70;i++)
	{
		for(int j = 0;j<3;j++)
		{
			int n = 3*i+j;
			std::stringstream ss;
			string num;
			ss<<n;
			ss>>num;
			string ImgName = (".\\trainBase\\"+num+".bmp");
			Mat img = imread(ImgName,0);
			if(img.empty())
			{
				return 0;
			}
			else
			{
				Mat row_tmp = ImgTotal.row(n);
				img.reshape(1,1).row(0).convertTo(ImgTotal.row(n),CV_32FC1);
			}
		}
		imwrite("111.bmp",ImgTotal);
	}
	return 0;
}