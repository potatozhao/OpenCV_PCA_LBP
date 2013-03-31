#include "Stdafx.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
#include <highgui.h>
using namespace std;
using  namespace  cv;
#ifdef _EiC
#define WIN32
#endif
static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
void detect_and_draw( IplImage* image,Mat &src_mat );
const char* cascade_name =
	"haarcascade_frontalface_alt.xml";
/*    "haarcascade_profileface.xml";*/
//CvMat header;
//CvMat *mat;					//MAT的全局变量，人脸检测后返回的矩阵

IplImage *dst1 = 0;
int PhotoCup(Mat &src_mat,const char* filename )
{
	//IplImage *frame, *frame_copy = 0;
	int optlen = strlen("--cascade=");
	const char* input_name = "Lena.jpg";

	cascade_name = "D:\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";
	//opencv装好后haarcascade_frontalface_alt2.xml的路径,
	//也可以把这个文件拷到你的工程文件夹下然后不用写路径名cascade_name= "haarcascade_frontalface_alt2.xml";  
	//或者cascade_name ="C:\\Program Files\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt2.xml"

	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
	if(cascade)
		cout<<"载入分类器成功"<<endl;
	if( !cascade )
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
		fprintf( stderr,
			"Usage: facedetect --cascade=\"<cascade_path>\" [filename|camera_index]\n" );
		return -1;
	}
	storage = cvCreateMemStorage(0);
	IplImage* image;
	image = cvLoadImage(filename,1);

	if( image )
	{
		detect_and_draw( image ,src_mat);
	
	}
	else
	{
		return 0;
	}
	return 0;
}

void detect_and_draw( IplImage* img,Mat &src_mat)
{
	static CvScalar colors[] = 
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};

	double scale = 1.3;
	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
	IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
		cvRound (img->height/scale)),
		8, 1 );
	int i;

	cvCvtColor( img, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	cvClearMemStorage( storage );

	if( cascade )
	{
		double t = (double)cvGetTickCount();
		CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
			1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
			cvSize(30, 30) );
		t = (double)cvGetTickCount() - t;
		printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
		for( i = 0; i < (faces ? faces->total : 0); i++ )
		{
			CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
			CvSize dst_cvsize;
			//IplImage *src = 0;			//源图像指针
			IplImage *dst = 0;			//目标图像指针
			//IplImage *dst1 = 0;			//目标图像指针
			cvSetImageROI(gray,cvRect(float (r->x)*scale,float(r->y)*scale,float(r->width)*scale,float(r->height)*scale));			//这段开始    将需要剪切的图像图像不部分设置为ROI
			dst = cvCreateImage(cvSize(float(r->width)*scale,float(r->height)*scale),IPL_DEPTH_8U, gray->nChannels);		//目标图片与剪切的区域大小相同
			cvCopy(gray,dst,0);														//复制到目标区域
			cvResetImageROI(gray);													//释放ROI区域

			dst_cvsize.width =80;					//目标图像的宽为源图象宽的scale倍
			dst_cvsize.height =80;					//目标图像的高为源图象高的scale倍

			dst1 = cvCreateImage( dst_cvsize, gray->depth,gray->nChannels);	//构造目标图象
			cvResize(dst, dst1, CV_INTER_LINEAR);	//缩放源图像到目标图像
			Mat src_mat1(dst1,0);				//用MAT 类中带有的Ipimage与MAT矩阵转换函数
			src_mat = src_mat1;
			
		}
	}
}