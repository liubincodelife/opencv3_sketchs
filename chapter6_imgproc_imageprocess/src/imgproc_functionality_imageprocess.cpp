#include "imgproc_functionality_imageprocess.h"

Mat g_filterSrcImage, g_morphologySrcImage;
int g_nBoxFilterKernelSize = 6;
int g_nMeanBlurFilterKernelSize = 6;
int g_nGaussianBlurFilterKernelSize = 6;
int g_nMedianBlurFilterKernelSize = 6;
int g_nBilateralFilterKernelSize = 6;

int g_nDilateKernelSize = 1;
int g_nErodeKernelSize = 1;
int g_nOpenKernelSize = 1;
int g_nCloseKernelSize = 1;
int g_nTopHatKernelSize = 1;
int g_nBlackHatKernelSize = 1;
int g_nMorphologyGradientKernelSize = 1;

imgproc_functionality_imageprocess::imgproc_functionality_imageprocess(Mat &input_image)
{
    image = input_image.clone();
}

imgproc_functionality_imageprocess::~imgproc_functionality_imageprocess()
{

}

void boxFilterTrackbar_cb(int , void *)
{
	Mat boxFilterDstImage;
	int kSize = g_nBoxFilterKernelSize * 2 + 1;
	boxFilter(g_filterSrcImage, boxFilterDstImage, -1, Size(kSize, kSize));
	imshow("BoxFilter Window", boxFilterDstImage);
}

void meanBlurFilterTrackbar_cb(int , void *)
{
	Mat meanBlurFilterDstImage;
	int kSize = g_nMeanBlurFilterKernelSize * 2 + 1;
	blur(g_filterSrcImage, meanBlurFilterDstImage, Size(kSize, kSize));
	imshow("MeanBlurFilter Window", meanBlurFilterDstImage);
}

void gaussianBlurFilterTrackbar_cb(int , void *)
{
	Mat gaussianBlurFilterDstImage;
	int kSize = g_nGaussianBlurFilterKernelSize * 2 + 1;
	GaussianBlur(g_filterSrcImage, gaussianBlurFilterDstImage, Size(kSize, kSize), 0, 0);
	imshow("GaussianBlurFilter Window", gaussianBlurFilterDstImage);
}

bool linearFilterProcess()
{
	namedWindow("BoxFilter Window");
	namedWindow("MeanBlurFilter Window");
	namedWindow("GaussianBlurFilter Window");
	createTrackbar("ksize:", "BoxFilter Window", &g_nBoxFilterKernelSize, 50, boxFilterTrackbar_cb);
	createTrackbar("ksize:", "MeanBlurFilter Window", &g_nMeanBlurFilterKernelSize, 50, meanBlurFilterTrackbar_cb);
	createTrackbar("ksize:", "GaussianBlurFilter Window", &g_nGaussianBlurFilterKernelSize, 50, gaussianBlurFilterTrackbar_cb);
	boxFilterTrackbar_cb(g_nBoxFilterKernelSize, 0);
	meanBlurFilterTrackbar_cb(g_nMeanBlurFilterKernelSize, 0);
	gaussianBlurFilterTrackbar_cb(g_nGaussianBlurFilterKernelSize, 0);
	return true;
}

void medianBlurFilterTrackbar_cb(int, void*)
{
	Mat medianBlurFilterDstImage;
	int kSize = g_nMedianBlurFilterKernelSize * 2 + 1;
	medianBlur(g_filterSrcImage, medianBlurFilterDstImage, kSize);
	imshow("MedianBlurFilter Window", medianBlurFilterDstImage);
}

void bilateralFilterTrackbar_cb(int, void*)
{
	Mat bilateralFilterDstImage;
	int kSize = g_nGaussianBlurFilterKernelSize * 2 + 1;
	bilateralFilter(g_filterSrcImage, bilateralFilterDstImage, kSize, kSize * 2, kSize / 2);
	imshow("BilateralFilter Window", bilateralFilterDstImage);
}

bool nonlinearFilterProcess()
{
	namedWindow("MedianBlurFilter Window");
	namedWindow("BilateralFilter Window");
	createTrackbar("ksize:", "MedianBlurFilter Window", &g_nMedianBlurFilterKernelSize, 50, medianBlurFilterTrackbar_cb);
	createTrackbar("ksize:", "BilateralFilter Window", &g_nBilateralFilterKernelSize, 50, bilateralFilterTrackbar_cb);
	
	medianBlurFilterTrackbar_cb(g_nMedianBlurFilterKernelSize, 0);
	bilateralFilterTrackbar_cb(g_nBilateralFilterKernelSize, 0);
	return true;
}

bool imageFilterProcess()
{
	// g_filterSrcImage = imread("../images/car.jpg");
	// g_filterSrcImage = imread("../images/girl.jpg");
	g_filterSrcImage = imread("../images/girlcartoon.jpg");
	if(g_filterSrcImage.empty())
	{
		cout<<"g_filterSrcImage is empty!!!"<<endl;
		return false;
	}
	imshow("filterSrcImage window", g_filterSrcImage);
	linearFilterProcess();
	nonlinearFilterProcess();
	return true;
}

void dilateTrackbar_cb(int , void* )
{
	Mat dilateDstImage, element;
	int kSize = g_nDilateKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, dilateDstImage, MORPH_DILATE, element);
	imshow("Morphology Dialate Window", dilateDstImage);
}

bool imageDilateProcess()
{
	namedWindow("Morphology Dialate Window");
	createTrackbar("ksize:", "Morphology Dialate Window", &g_nDilateKernelSize, 50, dilateTrackbar_cb);
	dilateTrackbar_cb(g_nDilateKernelSize, 0);
	return true;
}

void erodeTrackbar_cb(int , void* )
{
	Mat erodeDstImage, element;
	int kSize = g_nErodeKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, erodeDstImage, MORPH_ERODE, element);
	imshow("Morphology Erode Window", erodeDstImage);
}

bool imageErodeProcess()
{
	namedWindow("Morphology Erode Window");
	createTrackbar("ksize:", "Morphology Erode Window", &g_nErodeKernelSize, 50, erodeTrackbar_cb);
	erodeTrackbar_cb(g_nErodeKernelSize, 0);
	return true;
}

void openTrackbar_cb(int , void* )
{
	Mat openDstImage, element;
	int kSize = g_nOpenKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, openDstImage, MORPH_OPEN, element);
	imshow("Morphology Open Window", openDstImage);
}

bool imageOpenProcess()
{
	namedWindow("Morphology Open Window");
	createTrackbar("ksize:", "Morphology Open Window", &g_nOpenKernelSize, 50, openTrackbar_cb);
	openTrackbar_cb(g_nOpenKernelSize, 0);
	return true;
}

void closeTrackbar_cb(int , void* )
{
	Mat closeDstImage, element;
	int kSize = g_nCloseKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, closeDstImage, MORPH_CLOSE, element);
	imshow("Morphology Close Window", closeDstImage);
}

bool imageCloseProcess()
{
	namedWindow("Morphology Close Window");
	createTrackbar("ksize:", "Morphology Close Window", &g_nCloseKernelSize, 50, closeTrackbar_cb);
	closeTrackbar_cb(g_nCloseKernelSize, 0);
	return true;
}

void topHatTrackbar_cb(int , void* )
{
	Mat topHatDstImage, element;
	int kSize = g_nTopHatKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, topHatDstImage, MORPH_TOPHAT, element);
	imshow("Morphology TopHat Window", topHatDstImage);
}

bool imageTopHatProcess()
{
	namedWindow("Morphology TopHat Window");
	createTrackbar("ksize:", "Morphology TopHat Window", &g_nTopHatKernelSize, 50, topHatTrackbar_cb);
	topHatTrackbar_cb(g_nTopHatKernelSize, 0);
	return true;
}

void blackHatTrackbar_cb(int , void* )
{
	Mat blackHatDstImage, element;
	int kSize = g_nBlackHatKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, blackHatDstImage, MORPH_BLACKHAT, element);
	imshow("Morphology BlackHat Window", blackHatDstImage);
}

bool imageBlackHatProcess()
{
	namedWindow("Morphology BlackHat Window");
	createTrackbar("ksize:", "Morphology BlackHat Window", &g_nBlackHatKernelSize, 50, blackHatTrackbar_cb);
	blackHatTrackbar_cb(g_nBlackHatKernelSize, 0);
	return true;
}

void morphologyGradientTrackbar_cb(int , void* )
{
	Mat morphologyGradientDstImage, element;
	int kSize = g_nMorphologyGradientKernelSize * 2 + 1;
	element = getStructuringElement(MORPH_RECT, Size(kSize, kSize));
	morphologyEx(g_morphologySrcImage, morphologyGradientDstImage, MORPH_GRADIENT, element);
	imshow("Morphology Gradient Window", morphologyGradientDstImage);
}

bool imageMorphologyGradientProcess()
{
	namedWindow("Morphology Gradient Window");
	createTrackbar("ksize:", "Morphology Gradient Window", &g_nMorphologyGradientKernelSize, 50, morphologyGradientTrackbar_cb);
	morphologyGradientTrackbar_cb(g_nMorphologyGradientKernelSize, 0);
	return true;
}

bool imageMorphologyProcess()
{
	g_morphologySrcImage = imread("../images/captain.jpg");
	if(g_morphologySrcImage.empty())
	{
		cout<<"g_morphologySrcImage is empty!!!"<<endl;
		return false;
	}
	imshow("morphologySrcImage window", g_morphologySrcImage);
	imageDilateProcess();
	imageErodeProcess();
	imageOpenProcess();
	imageCloseProcess();
	imageTopHatProcess();
	imageBlackHatProcess();
	imageMorphologyGradientProcess();
	return true;
}

bool imageFloodFillNoMask()
{
	Mat floodFillSrcImage = imread("../images/building.jpg");
	if(floodFillSrcImage.empty())
	{
		cout<<"floodFillSrcImage is empty!!!"<<endl;
		return false;
	}
	imshow("floodFillSrcImage", floodFillSrcImage);
	Rect rect;
	floodFill(floodFillSrcImage, Point(50, 300), Scalar(155, 255, 55), &rect, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("floodFillSrcImage dstImage", floodFillSrcImage);

	return true;
}

Mat g_floodFillSrcImage, g_floodFillDstImage,g_floodFillGrayImage, g_floodFillMaskImage;
int g_nFillMode = 1;
int g_nLowDifference = 20, g_nUpDifference = 20;
int g_nConnectivity = 4;
bool g_bIsColor = true;
bool g_bIsShowMask = false;
int g_nNewMaskVal = 255;

static void mouseClick_cb(int event, int x, int y, int, void*)
{
	if(event != EVENT_LBUTTONDOWN)
		return;
	cout<<"mouce left button click..."<<endl;
	Point seed = Point(x, y);
	int nLowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	int nUpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	int b = (unsigned)theRNG() & 0xFF;
	int g = (unsigned)theRNG() & 0xFF;
	int r = (unsigned)theRNG() & 0xFF;

	Rect rect;
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.229 + g*0.587 + b*0.114);
	Mat floodFillDstImage = g_bIsColor ? g_floodFillDstImage : g_floodFillGrayImage;
	int area = 0;
	if(g_bIsShowMask)
	{
		threshold(g_floodFillMaskImage, g_floodFillMaskImage, 1, 128, THRESH_BINARY);
		area = floodFill(floodFillDstImage, g_floodFillMaskImage, seed, newVal, &rect, 
				Scalar(nLowDifference, nLowDifference, nLowDifference), 
				Scalar(nUpDifference, nUpDifference, nUpDifference), flags);
		imshow("mask image", g_floodFillMaskImage);
	}
	else
	{
		area = floodFill(floodFillDstImage, seed, newVal, &rect, Scalar(nLowDifference, nLowDifference, nLowDifference),
				Scalar(nUpDifference, nUpDifference, nUpDifference), flags);
	}
	imshow("FloodFill Prcess Window", floodFillDstImage);
	cout<<"num:"<<area<<"  pixels is been redraw..."<<endl;
}

bool imageFloodFillWithMask()
{
	// g_floodFillSrcImage = imread("../images/building.jpg");
	g_floodFillSrcImage = imread("../images/house.jpg");
	if(g_floodFillSrcImage.empty())
	{
		cout<<"g_floodFillSrcImage is empty!!!"<<endl;
		return false;
	}
	
	g_floodFillDstImage = g_floodFillSrcImage.clone();
	cvtColor(g_floodFillSrcImage, g_floodFillGrayImage, COLOR_BGR2GRAY);
	g_floodFillMaskImage.create(g_floodFillSrcImage.rows + 2, g_floodFillSrcImage.cols + 2, CV_8UC1);

	namedWindow("FloodFill Prcess Window", WINDOW_AUTOSIZE);

	createTrackbar("LowDiff", "FloodFill Prcess Window", &g_nLowDifference, 255, 0);
	createTrackbar("UpDiff", "FloodFill Prcess Window", &g_nUpDifference, 255, 0);
	setMouseCallback("FloodFill Prcess Window", mouseClick_cb);

	while(1)
	{
		imshow("FloodFill Prcess Window", g_bIsColor ?  g_floodFillDstImage : g_floodFillGrayImage);
		int c = waitKey(0);
		if((c & 0xFF) == 27)
		{
			cout<<"process exit......"<<endl;
			return false;
		}
		switch(char(c))
		{
			case '1':
				if(g_bIsColor)
				{
					cout<<"key \"1\" pressed, switch rgb/gray mode. Now switch to gray mode."<<endl;
					cvtColor(g_floodFillSrcImage, g_floodFillGrayImage, COLOR_BGR2GRAY);
					g_floodFillMaskImage = Scalar::all(0);
					g_bIsColor = false;
				}
				else
				{
					cout<<"key \"1\" pressed, switch rgb/gray mode. Now switch to rgb mode."<<endl;
					g_floodFillDstImage = g_floodFillSrcImage.clone();
					g_floodFillMaskImage = Scalar::all(0);
					g_bIsColor = true;
				}
				break;
			case '2':
				cout<<"key \"2\" pressed, switch to use mask or not."<<endl;
				if(g_bIsShowMask)
				{
					destroyWindow("mask image");
					g_bIsShowMask = false;
				}
				else
				{
					namedWindow("mask image", WINDOW_NORMAL);
					g_floodFillMaskImage = Scalar::all(0);
					imshow("mask image", g_floodFillMaskImage);
					g_bIsShowMask = true;
				}
				break;
			case '3':
				cout<<"key \"3\" pressed, refresh to src image."<<endl;
				g_floodFillDstImage = g_floodFillSrcImage.clone();
				cvtColor(g_floodFillDstImage, g_floodFillGrayImage, COLOR_BGR2GRAY);
				g_floodFillMaskImage = Scalar::all(0);
				break;
			case '4':
				cout<<"key \"4\" pressed, use empty range flood fill mode."<<endl;
				g_nFillMode = 0;
				break;
			case '5':
				cout<<"key \"5\" pressed, use const range flood fill mode."<<endl;
				g_nFillMode = 1;
				break;
			case '6':
				cout<<"key \"6\" pressed, use float range flood fill mode."<<endl;
				g_nFillMode = 2;
				break;
			case '7':
				cout<<"key \"7\" pressed, use 4bits connectivity mode."<<endl;
				g_nConnectivity = 4;
				break;
			case '8':
				cout<<"key \"8\" pressed, use 8bits connectivity mode."<<endl;
				g_nConnectivity = 8;
				break;
			default:
				break;
		}
	}

	return true;
}

bool gaussianPyrAndResize()
{
	Mat gaussianPyrSrcImage = imread("../images/car2.jpg");
	if(gaussianPyrSrcImage.empty())
	{
		cout<<"gaussianPyrSrcImage is empty!!!"<<endl;
		return false;
	}
	Mat gaussianPyrDstImage, gaussianPyrTmpImage;
	namedWindow("GaussianPyr and Resize Window", WINDOW_AUTOSIZE);
	imshow("GaussianPyr and Resize Src Window", gaussianPyrSrcImage);
	gaussianPyrTmpImage = gaussianPyrSrcImage.clone();
	while(1)
	{
		int c = waitKey(0);
		if((c & 0xFF) == 27)
		{
			cout<<"process exit......"<<endl;
			return false;
		}
		switch(char(c))
		{
			case 'q':
				cout<<"key \"q\" pressed, switch to use mask or not."<<endl;
				
				break;
			case 'u':
				cout<<"key \"u\" pressed, pyr up to double size."<<endl;
				pyrUp(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols * 2, gaussianPyrTmpImage.rows * 2));
				break;
			case 'd':
				cout<<"key \"d\" pressed, pyr down to double size."<<endl;
				pyrDown(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols / 2, gaussianPyrTmpImage.rows / 2));
				break;
			case 'r':
				cout<<"key \"r\" pressed, resize up to double size with default mode."<<endl;
				resize(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols * 2, gaussianPyrTmpImage.rows * 2));
				break;
			case 's':
				cout<<"key \"s\" pressed, resize down to double size with default mode."<<endl;
				resize(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols / 2, gaussianPyrTmpImage.rows / 2));
				break;
			case 'e':
				cout<<"key \"e\" pressed, resize up to double size with INTER_CUBIC mode."<<endl;
				resize(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols * 2, gaussianPyrTmpImage.rows * 2), 
					0.0, 0.0, INTER_CUBIC);
				break;
			case 'a':
				cout<<"key \"a\" pressed, resize down to double size with INTER_CUBIC mode."<<endl;
				resize(gaussianPyrTmpImage, gaussianPyrDstImage, Size(gaussianPyrTmpImage.cols / 2, gaussianPyrTmpImage.rows / 2),
				0.0, 0.0, INTER_CUBIC);
				break;
			default:
				break;
		}
		imshow("GaussianPyr and Resize Drc Window", gaussianPyrDstImage);
		gaussianPyrTmpImage = gaussianPyrDstImage;
	}
	return true;
}

Mat g_thresholdSrcImage, g_thresholdDstImage, g_thresholdGrayImage;
int g_nThresholdType = THRESH_TOZERO;
int g_nThresholdValue = 100;


void threshold_cb(int, void *)
{
	if(g_nThresholdType != 5)
	{
		threshold(g_thresholdGrayImage, g_thresholdDstImage, g_nThresholdValue, 255, g_nThresholdType);
	}
	else
	{
		adaptiveThreshold(g_thresholdGrayImage, g_thresholdDstImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);
	}
	
	imshow("Threshold Process Dst Window", g_thresholdDstImage);
}

bool thresholdOperation()
{
	g_thresholdSrcImage = imread("../images/sea.jpg");
	if(g_thresholdSrcImage.empty())
	{
		cout<<"g_thresholdSrcImage is empty!!!"<<endl;
		return false;
	}
	cvtColor(g_thresholdSrcImage, g_thresholdGrayImage, COLOR_BGR2GRAY);
	namedWindow("Threshold Process Dst Window", WINDOW_AUTOSIZE);
	imshow("Threshold Process Sst Window", g_thresholdSrcImage);
	createTrackbar("mode", "Threshold Process Dst Window", &g_nThresholdType, 5, threshold_cb);
	createTrackbar("value", "Threshold Process Dst Window", &g_nThresholdValue, 255, threshold_cb);
	threshold_cb(0, 0);
	while(1)
	{
		int c = waitKey(0);
		if(c == 27)
			break;
	}
	return true;
}


void imgproc_functionality_imageprocess::process()
{
	// imageFilterProcess();
	// imageMorphologyProcess();
	// imageFloodFillNoMask();
	// imageFloodFillWithMask();
	// gaussianPyrAndResize();
	thresholdOperation();
}