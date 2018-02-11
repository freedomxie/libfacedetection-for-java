// FaceDete.cpp: 定义 DLL 应用程序的导出函数。
//

#include"stdafx.h"
#include <facedetect-dll.h>
#include <string>
#include <cstring>
#include<opencv2\opencv.hpp>  
#include<iostream>  

using namespace cv;
using namespace std;
#define MYLIBAPI extern "C" __declspec( dllexport)
#define DETECT_BUFFER_SIZE 0x20000

MYLIBAPI char* MutFaceDetectRF(unsigned char* img, int cols, int rows, int step);

MYLIBAPI char* MutFaceDetect(unsigned char* img, int cols, int rows, int step);


char* MutFaceDetectRF(unsigned char* img, int cols, int rows, int step)
{
	
	int * pResults = NULL;
	//pBuffer is used in the detection functions.
	//If you call functions in multiple threads, please create one buffer for each thread!
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return "";
	}

	int doLandmark = 0;
	//facedetect_multiview_reinforce
	pResults = facedetect_multiview_reinforce(pBuffer, img, cols,rows, step, 1.1f, 2, 30, 0, doLandmark);

	printf("%d faces detected.\n", (pResults ? *pResults : 0));
	

	string pox = "";
	//print the detection results
	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		pox += (to_string(x) + "," + to_string(y) + "," + to_string(w) + "," + to_string(h) + "|");

	}
	int count = *pResults;
	if (count > 0) {
		char *c = new char[20 * count];
		strcpy_s(c, 20 * count,pox.c_str());
		return c;
	}
	return "";
}

char* MutFaceDetect(unsigned char* img, int cols, int rows, int step)
{
	
	int * pResults = NULL;
	//pBuffer is used in the detection functions.
	//If you call functions in multiple threads, please create one buffer for each thread!
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return "";
	}

	int doLandmark = 0;
	//facedetect_multiview_reinforce
	pResults = facedetect_multiview(pBuffer, img, cols, rows,step, 1.1f, 2, 30, 0, doLandmark);

	printf("%d faces detected.\n", (pResults ? *pResults : 0));
	
	string pox = "";
	//print the detection results
	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		pox += (to_string(x) + "," + to_string(y) + "," + to_string(w) + "," + to_string(h) + "|");

	}
	int count = *pResults;
	if (count > 0) {
		char *c = new char[20 * count];
		strcpy_s(c, 20 * count, pox.c_str());
		return c;
	}
	return "";
}


