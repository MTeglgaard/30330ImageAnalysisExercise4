#include <stdint.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include  <conio.h>

int main(int argc, char* argv[])
{
	const char* wName = "Original"; // window name 
	const char* wName2 = "Filter";
	const char* wName3 = "Contour";
	//const char* wName4 = "webCam";
	//cvNamedWindow(wName4, 0); // create simple window    
	cvNamedWindow(wName, 0); // create simple window    
	//cvNamedWindow(wName2, 0); // create simple window   
	//cvNamedWindow(wName3, 0); // create simple window 

	CvCapture* capture = 0;

	double capProp = 0;

	IplImage *frame, *img, *frame_copy = 0; // pointers to images 
	
	frame = 0;
	//capture = cvCaptureFromCAM(0); // initialize capture device 

	img = cvLoadImage("PEN.png",0); // = cvLoadImage("ariane5_1b.jpg", 1); //

	//IplImage *img_filter = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 1);

	//cvResize(img, img_filter, CV_INTER_LINEAR);

	//IplImage *img_result = cvCreateImage(cvGetSize(img_filter), IPL_DEPTH_8U, 1);
	IplImage *imgT = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	//IplImage *imgFilter = 0;
	//cvCvtColor(img, imgT, CV_RGB2GRAY);
	//cvResizeWindow(wName, img->width, img->height);
	//cvMoveWindow(wName, 0, 150);

	//cvResizeWindow(wName3, imgT->width, imgT->height);
	//cvMoveWindow(wName3, 650, 150);
	//IplImage *img_cvfind = cvCreateImage(cvGetSize(img_filter), IPL_DEPTH_8U, 1);
	//double k_weight = 1.0 / 9.0;
	//double K[9] = { k_weight,k_weight,k_weight,k_weight,k_weight,k_weight,k_weight,k_weight,k_weight };//{ 1 / 9,1 / 9 ,1 / 9 ,1 / 9,1 / 9,1 / 9,1 / 9,1 / 9,1 / 9 };
	//double k_weight = -1.0 ;
	//double K[9] = { k_weight,k_weight,k_weight,k_weight, 8.0 ,k_weight,k_weight,k_weight,k_weight };//{ 1 / 9,1 / 9 ,1 / 9 ,1 / 9,1 / 9,1 / 9,1 / 9,1 / 9,1 / 9 };
	//const CvMat Kernel = cvMat(3, 3, CV_64FC1, K); 


	////** Laplace-Gaussian filter
	//double K2[81] = { 0,0,1,2,2,2,1,0,0,     0,1,5,10,12,10,5,1,0,   1,5,15,19,16,19,15,5,1,   2,10,19,-19,-64,-19,19, 10,2,    2,12,16,-64,-148,-64,16,12,2,  2,10,19,-19,-64,-19,19, 10,2,   1,5,15,19,16,19,15,5,1,    0,1,5,10,12,10,5,1,0,        0,0,1,2,2,2,1,0,0, };
	//const CvMat Kernel2 = cvMat(9, 9, CV_64FC1, K2);
	//long double init_tick = (long double)cvGetTickCount();
	//cvFilter2D(img_filter, img_result, &Kernel2);
	//long double last_tick = (long double)cvGetTickCount();
	//long double ticks_cvfind = (last_tick - init_tick); // (long double)cvGetTickFrequency();
	//double freq = (long double)cvGetTickFrequency();
	//printf("\nTicks for cvfind: %f \ninit_tick: %f \n last_tick: %f \n freq = %f\n", ticks_cvfind, init_tick, last_tick, freq);

	//** Highpass filter
	//cvFilter2D(img_filter, img_cvfind,&Kernel);
	//int step_filter = img_filter->widthStep / sizeof(uchar);
	//uchar *data = (uchar *)img_filter->imageData;

	/*
	init_tick = (long double)cvGetTickCount();
	double maxVale = 0;
	double minVale = 255;
	for (size_t i = 1; i < (img_filter->width); i++)
	{
		for (size_t j = 1; j < (img_filter->height); j++)
		{
	
			// Lowpass filter
			//int temp_data= data[(i-1) + step_filter * (j-1)]+ data[i + step_filter * (j-1)]+ data[(i+1) + step_filter * (j-1)]+ data[(i-1) + step_filter * j]+ data[i + step_filter * j]+ data[(i+1) + step_filter * j]+ data[(i-1) + step_filter * (j+1)]+ data[i + step_filter * (j+1)]+ data[(i+1) + step_filter * (j+1)];
			//img_result->imageData[i + step_filter * j] = temp_data/9;
			
			// highpass filter
			int temp_data = -data[(i - 1) + step_filter * (j - 1)] - data[i + step_filter * (j - 1)] - data[(i + 1) + step_filter * (j - 1)] 
							- data[(i - 1) + step_filter * j]      +8*data[i + step_filter * j]       - data[(i + 1) + step_filter * j] 
							- data[(i - 1) + step_filter * (j + 1)] - data[i + step_filter * (j + 1)] - data[(i + 1) + step_filter * (j + 1)];

			//int temp_data = -(0									+ data[i + step_filter * (j - 1)]	+ 0
			//				 + data[(i - 1) + step_filter * j]	- 4 * data[i + step_filter * j]		+ data[(i + 1) + step_filter * j]
			//				 + 0								+ data[i + step_filter * (j + 1)]	+ 0);
			
			
			// normalization  
			temp_data = temp_data + 8 * 255; //  0 to 2*8*255
			temp_data = temp_data * 255; // normalized to btew 0 nd 255
			temp_data = temp_data * 1 / (2 * 8 * 255); // normalized to btew 0 nd 1

						
			img_result->imageData[i + step_filter * j] = temp_data; // + data[i + step_filter * j];
			
			if (temp_data < minVale)
			{
				minVale = temp_data;
			}
			else if(temp_data > maxVale)
			{
				maxVale = temp_data;
			}
		}

	}
	printf("\n max Val %f, min val %f", maxVale, minVale);
	
	last_tick = (long double)cvGetTickCount();
	long double ticks_cvfind2 = (last_tick - init_tick);//(long double)cvGetTickFrequency();
	long double difrence = ((ticks_cvfind2 - ticks_cvfind)/ ticks_cvfind)*100;
	printf("\nTicks for custom filter: %Lf \ninit_tick: %Lf \n last_tick: %Lf \n freq = %Lf\n diference: %Lf\n ", ticks_cvfind2, init_tick, last_tick, freq, difrence);
	*/
	
	

	int character = 0;
	
		//uchar * data = (uchar *)img->imageData;
		int h = img->height;
		int w = img->width;
		int step = img->widthStep / sizeof(uchar);
		int color = 1; // red = 0, Green = 1,  Blue = 2 
		int c = 0 + color;
		int r = 0;
	
	/*
		for (size_t i = 0; i < img->imageSize; i=i+3)
		{
			data[i + color]=255 - data[i + color];
			data[i + color+1] = 255- data[i + color + 1];
			data[i + color + 2] = 255 - data[i + color + 2];
		}
		img->imageData = (char *)data;
		//data[c + step * r]
	*/
	
		unsigned char *channel, *channel2; // pre-allocated array holding image data for the color channel or the grayscale image. 
		unsigned char value=0; // index value for the histogram (not really needed) 
		int histogram[256]; // histogram array - remember to set to zero initially 
		int width; // say, 320 
		int height; // say, 240 
		channel = (uchar *)img->imageData;
		//channel2 = (uchar *)imgT->imageData;
	
		//Histogram

		width = w;
		height = h;
		//int k = 256; 
		int t = 100;//107
		//while (k-- > 0)
		//{
		//	histogram[k] = 0; // reset histogram entry 
		//}
		//int maxVal = 0;
		//for (int i = 0; i < width*height; i++)
		//{
		//	value = channel[i];
		//	histogram[value] += 1;
		//	if (channel2[i] >= t)
		//	{
		//		imgT -> imageData[i] = 255;
		//	}
		//	else { imgT->imageData[i] = 0;}
		//	
		//	if (histogram[value] > maxVal)
		//	{
		//		maxVal = histogram[value];
		//	}
		//	//printf("%d ", histogram[value]);
		//}
		//printf("%d ", maxVal);
		//CvSize histImSiz = cvSize(256, maxVal*1.01); //cvSize(width, height); 
	
		//IplImage *histPlot = cvCreateImage(histImSiz, IPL_DEPTH_8U, img->nChannels);
		//
		//for (int i = 1; i < 256; i++) //i = 0;
		//{
		//	int mag = histogram[i];
		//	//cvLine(histPlot, cvPoint(i, 0), cvPoint(i, mag), cvScalar(255, 0, 0), 1);
		//	cvLine(histPlot, cvPoint((i-1), histogram[i-1]), cvPoint(i, histogram[i]), cvScalar(255, 0, 0), 1);
		//}
	
		/*cvLine(histPlot, cvPoint(t, 0), cvPoint(t, maxVal), cvScalar(0, 255, 0), 1);
		cvLine(histPlot, cvPoint(100, 0), cvPoint(100, 100), cvScalar(255, 0, 0), 1, 8, CV_AA);
		cvLine(		histPlot, cvPoint(400, 0), cvPoint(400, 200), cvScalar(255, 0, 0), 1);
		cvRectangle(histPlot, cvPoint(10, 10), cvPoint(20, 20), cvScalar(255, 0, 0), 1);
		cvResizeWindow(wName2, img->width, h);
		cvMoveWindow(wName2, 250, 150);*/
	
		//FILTER
		/*
		Get Data of the pixel > Enter the if loop > if the pixels around it exists, do..., else check next pixels around
		
		*/

		
		 for (int i = 0; i < width*height; i++)
		{
			value = channel[i];
			
			if (img->imageData[i] < t)
			{
				imgT->imageData[i] = 255;
			}
			else { imgT->imageData[i] = 0; }

		//	if (histogram[value] > maxVal)
		//	{
		//		maxVal = histogram[value];
		//	}
		//	//printf("%d ", histogram[value]);
		}

		

	//	int kernel;

		char quit = 0;
	//	//cvFilter2D(img, imgFilter,(0, 0, 5), cvPoint(-1, 1));
	//if(capture)
	//{ 
	//	while (1)
	//	{
	//		if (!cvGrabFrame(capture))
	//		{
	//			break;
	//		}
	//		frame = cvRetrieveFrame(capture);

	//		if (!img)
	//		{
	//			printf("no img");
	//			break;
	//		}
	//		if (!frame_copy)
	//		{
	//			frame_copy = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	//		}
			
			//cvFilter2D(frame, frame_copy, &Kernel2);



		//Contour

		//Define MAX_RAND , pos , end , count , rimx . rimy , B (width of the image)

		unsigned char *pic= (uchar *)img->imageData; // placeholder for image data
		int MAX_RAND = img->width * img->height;
		int end = w * h;
		int rimx[100000], rimy[100000];
		int newpos, local_tresh, pos,i;
		int count = 0;
		local_tresh = 107;
		int draw_type=0;
		int B = img->width;


		for (i = 0; i < h*w; i++) {
			if (pic[i] >= local_tresh) {
				
				pos = i;
				printf("position %d", pos);
				break;
			}
		}

		newpos=pos; // pos equals the starting position in the image ( = y*Width+x)
		while(newpos>=0L && newpos<end){

			rimx[count]=newpos%B; // save current position in list
			rimy[count]=newpos/B;
			printf("\n rimx = %d rimy = %d", rimx[count], rimy[count]);
			count++;

			draw_type=(draw_type+6)%8; // Select next search direction
			switch(draw_type)
			{
			case 0: 
				if(pic[newpos+1 ]>local_tresh)
				{
				newpos+=1;
				draw_type=0;
				break;
				}

			case 1: 
				if(pic[newpos+B+1]>local_tresh) 
				{
				newpos+=B+1;
				draw_type=1;
				break;
				}
			case 2: 
				if(pic[newpos+B ]>local_tresh) 
				{
				newpos+=B ;
				draw_type=2;
				break;
				}
			case 3: 
				if(pic[newpos+B-1]>local_tresh) 
				{
				newpos+=B-1;
				draw_type=3;
				break;
				}
			case 4:
				if(pic[newpos-1 ]>local_tresh) 
				{
				newpos-=1 ;
				draw_type=4;
				break;
				}
			case 5:
				if (pic[newpos - B - 1] > local_tresh)
				{
				newpos -= B + 1;
				draw_type = 5; 
				break;
				}
			case 6:
				if (pic[newpos - B] > local_tresh) 
				{
				newpos -= B; 
				draw_type = 6;
				break;
				}
			case 7: 
				if (pic[newpos - B + 1] > local_tresh) 
				{
				newpos -= B - 1; 
				draw_type = 7; 
				break; 
				}
			case 8: if (pic[newpos + 1] > local_tresh) 
				{
				newpos += 1; 
				draw_type = 0;
				break; 
				}
			case 9: 
				if (pic[newpos + B + 1] > local_tresh) 
				{
				newpos += B + 1; 
				draw_type = 1; 
				break;
				}
			case 10: 
				if (pic[newpos + B] > local_tresh) 
				{
				newpos += B;
				draw_type = 2;
				break; 
				}
			case 11: if (pic[newpos + B - 1] > local_tresh) 
				{
				newpos += B - 1;
				draw_type = 3; 
				break; 
				}
			case 12: if (pic[newpos - 1] > local_tresh)
				{
				newpos -= 1; 
				draw_type = 4; 
				break; 
				}
			case 13: if (pic[newpos - B - 1] > local_tresh) 
				{
				newpos -= B + 1;
				draw_type = 5;
				break; 
				}
			case 14: 
				if (pic[newpos - B] > local_tresh) 
				{
				newpos -= B; 
				draw_type = 6;
				break;
				}
			}
			
			// If weare back at the beginning, we declare success
			if(newpos==pos)
				break;
			// Abortif the contour is too complex
			if(count>=MAX_RAND)
				break;
		}
			while (1)
	{

	//		//cvShowImage(wName4, frame_copy);
	//		//cvShowImage(wName, img_cvfind);
	//		//cvShowImage(wName2, img_filter);
	//		//cvShowImage(wName3, img_result);
	//		//cvFlip(histPlot, NULL, 0); // cvFlip(const CvArr* src, CvArr* dst=NULL, int flip_mode=0 ) // flip_mode – a flag to specify how to flip the array; 0 flipping around the x-axis and fx 1 means flipping around y-axis. -1 means flipping around both axes
			cvShowImage(wName, imgT);
			quit = cvWaitKey(0);
			if (quit=='q')
				break;
		}
	
	
	
	cvReleaseImage(&img);
	//cvReleaseImage(&imgT);
	cvDestroyWindow("Hello World");
	//cvReleaseImage(&histPlot);
	cvDestroyWindow(wName);
	cvDestroyWindow(wName2);
	cvDestroyWindow(wName3);

	return 0;
}
