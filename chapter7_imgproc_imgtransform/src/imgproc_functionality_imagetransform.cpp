#include "imgproc_functionality_imagetransform.h"


imgproc_functionality_imagetransform::imgproc_functionality_imagetransform(Mat &input_image)
{
    image = input_image.clone();
}

imgproc_functionality_imagetransform::~imgproc_functionality_imagetransform()
{

}

bool canny_edge()
{
	Mat cannySrcImage = imread("../images/canny.jpg");
	if(cannySrcImage.empty())
	{
		cout<<"cannySrcImage is empty!!!"<<endl;
		return false;
	}
	
	Mat cannyDstImage, cannySimpleEdgeImage, cannyGrayImage, cannyMidEdgeImage;
	imshow("cannySrcImage Window", cannySrcImage);
	Canny(cannySrcImage, cannySimpleEdgeImage, 3, 9);

	imshow("cannySimpleEdgeImage Window", cannySimpleEdgeImage);
	cvtColor(cannySrcImage, cannyGrayImage, COLOR_BGR2GRAY);
	imshow("cannyGrayImage Window", cannyGrayImage);
	blur(cannyGrayImage, cannyMidEdgeImage, Size(3, 3));
	imshow("cannyGrayImage after blur Window", cannyMidEdgeImage);
	Canny(cannyMidEdgeImage, cannyMidEdgeImage, 3, 9);
	imshow("cannyMidEdgeImage Window", cannyMidEdgeImage);
	cannySrcImage.copyTo(cannyDstImage, cannyMidEdgeImage);
	imshow("cannyDstImage Window", cannyDstImage);
	return true;
}

bool sobel_edge()
{
	Mat sobelSrcImage = imread("../images/sobel.jpg");
	if(sobelSrcImage.empty())
	{
		cout<<"sobelSrcImage is empty!!!"<<endl;
		return false;
	}
	Mat sobelGrad_x, sobelGradAbs_x;
	Mat sobelGrad_y, sobelGradAbs_y;
	Mat sobelDstEdgeImage;
	Sobel(sobelSrcImage, sobelGrad_x, CV_16S, 1, 0, 3);
	convertScaleAbs(sobelGrad_x, sobelGradAbs_x);
	imshow("sobelGradAbs_x window", sobelGradAbs_x);

	Sobel(sobelSrcImage, sobelGrad_y, CV_16S, 0, 1, 3);
	convertScaleAbs(sobelGrad_y, sobelGradAbs_y);
	imshow("sobelGradAbs_y window", sobelGradAbs_y);

	addWeighted(sobelGradAbs_x, 0.5, sobelGradAbs_y, 0.5, 0, sobelDstEdgeImage);
	imshow("sobelDstEdgeImage Window", sobelDstEdgeImage);

	return true;
}

bool laplacian_edge()
{
	Mat laplacianSrcImage = imread("../images/laplacian.jpg");
	if(laplacianSrcImage.empty())
	{
		cout<<"laplacianSrcImage is empty!!!"<<endl;
		return false;
	}
	Mat laplacianGrayImage, laplacianSrcBlurImage;
	Mat laplacianRGBEdgeImage, laplacianRGBEdgeImageAbs;
	Mat laplacianRGBEdgeBlurImage, laplacianRGBEdgeBlurImageAbs;
	Mat laplacianGrayEdgeImage, laplacianGrayEdgeImageAbs;

	imshow("laplacianSrcImage Window", laplacianSrcImage);
	cvtColor(laplacianSrcImage, laplacianGrayImage, COLOR_BGR2GRAY);
	GaussianBlur(laplacianGrayImage, laplacianGrayImage, Size(3, 3), 0, 0);
	imshow("laplacianGrayImage after blur Window",laplacianGrayImage);
	Laplacian(laplacianGrayImage, laplacianGrayEdgeImage, CV_16S, 3, 1, 0);
	convertScaleAbs(laplacianGrayEdgeImage, laplacianGrayEdgeImageAbs);
	imshow("laplacianGrayEdgeImageAbs Window",laplacianGrayEdgeImageAbs);

	Laplacian(laplacianSrcImage, laplacianRGBEdgeImage, CV_16S, 3, 1, 0);
	convertScaleAbs(laplacianRGBEdgeImage, laplacianRGBEdgeImageAbs);
	imshow("laplacianRGBEdgeImageAbs Window",laplacianRGBEdgeImageAbs);

	GaussianBlur(laplacianSrcImage, laplacianSrcBlurImage, Size(3, 3), 0, 0);
	imshow("laplacianSrcBlurImage Window",laplacianSrcBlurImage);
	Laplacian(laplacianSrcBlurImage, laplacianRGBEdgeBlurImage, CV_16S, 3, 1, 0);
	convertScaleAbs(laplacianRGBEdgeBlurImage, laplacianRGBEdgeBlurImageAbs);
	imshow("laplacianRGBEdgeBlurImageAbs Window",laplacianRGBEdgeBlurImageAbs);

	return true;
}

bool scharr_edge()
{
	Mat scharrSrcImage = imread("../images/scharr.jpg");
	if(scharrSrcImage.empty())
	{
		cout<<"scharrSrcImage is empty!!!"<<endl;
		return false;
	}
	Mat scharrGrad_x, scharrGradAbs_x;
	Mat scharrGrad_y, scharrGradAbs_y;
	Mat scharrDstEdgeImage;
	Scharr(scharrSrcImage, scharrGrad_x, CV_16S, 1, 0);
	convertScaleAbs(scharrGrad_x, scharrGradAbs_x);
	imshow("scharrGradAbs_x window", scharrGradAbs_x);

	Scharr(scharrSrcImage, scharrGrad_y, CV_16S, 0, 1);
	convertScaleAbs(scharrGrad_y, scharrGradAbs_y);
	imshow("scharrGradAbs_y window", scharrGradAbs_y);

	addWeighted(scharrGradAbs_x, 0.5, scharrGradAbs_y, 0.5, 0, scharrDstEdgeImage);
	imshow("scharrDstEdgeImage Window", scharrDstEdgeImage);

	return true;
}

Mat g_EdgeDetectSrcImage, g_EdgeDetectSrcGrayImage;
Mat g_CannyEdgeDetectDstImage, g_SobelEdgeDetectDstImage, g_LaplacianEdgeDetectDstImage;
int g_cannyLowThreshold = 1;
int g_sobelKernelSize = 1;
int g_laplacianKernelSize = 1;

void cannyEdge_cb(int, void *)
{
	Mat cannyBlurImage, cannyMidEdgeImage;
	blur(g_EdgeDetectSrcGrayImage, cannyBlurImage, Size(3, 3));
	Canny(cannyBlurImage, cannyMidEdgeImage, g_cannyLowThreshold, g_cannyLowThreshold * 3);
	g_CannyEdgeDetectDstImage = Scalar::all(0);
	g_EdgeDetectSrcImage.copyTo(g_CannyEdgeDetectDstImage, cannyMidEdgeImage);
	imshow("Canny Edge Detect Window", g_CannyEdgeDetectDstImage);
}

void sobelEdge_cb(int, void *)
{
	Mat sobelGrad_x, sobelGradAbs_x;
	Mat sobelGrad_y, sobelGradAbs_y;
	int kSize = g_sobelKernelSize * 2 + 1;
	cout<<"sobel kSize = "<<kSize<<endl;
	Sobel(g_EdgeDetectSrcImage, sobelGrad_x, CV_16S, 1, 0, kSize);
	convertScaleAbs(sobelGrad_x, sobelGradAbs_x);

	Sobel(g_EdgeDetectSrcImage, sobelGrad_y, CV_16S, 0, 1, kSize);
	convertScaleAbs(sobelGrad_y, sobelGradAbs_y);
	g_SobelEdgeDetectDstImage = Scalar::all(0);
	addWeighted(sobelGradAbs_x, 0.5, sobelGradAbs_y, 0.5, 0, g_SobelEdgeDetectDstImage);
	imshow("Sobel Edge Detect Window", g_SobelEdgeDetectDstImage);
}

void laplacianEdge_cb(int, void *)
{
	Mat laplacianBlurImage, laplacianMidEdgeImage;
	int kSize = g_laplacianKernelSize * 2 + 1;
	cout<<"laplacian kSize = "<<kSize<<endl;
	GaussianBlur(g_EdgeDetectSrcImage, laplacianBlurImage, Size(3, 3), 1);
	Laplacian(laplacianBlurImage, laplacianMidEdgeImage, CV_16S, kSize);
	convertScaleAbs(laplacianMidEdgeImage, g_LaplacianEdgeDetectDstImage);
	imshow("Laplacian Edge Detect Window", g_LaplacianEdgeDetectDstImage);
}

void scharrProcess()
{
	Mat scharrGrad_x, scharrGradAbs_x;
	Mat scharrGrad_y, scharrGradAbs_y;

	Sobel(g_EdgeDetectSrcImage, scharrGrad_x, CV_16S, 1, 0);
	convertScaleAbs(scharrGrad_x, scharrGradAbs_x);

	Sobel(g_EdgeDetectSrcImage, scharrGrad_y, CV_16S, 0, 1);
	convertScaleAbs(scharrGrad_y, scharrGradAbs_y);
	Mat scharrEdgeDetectDstImage;
	addWeighted(scharrGradAbs_x, 0.5, scharrGradAbs_y, 0.5, 0, scharrEdgeDetectDstImage);
	imshow("scharrEdgeDetectDstImage Window", scharrEdgeDetectDstImage);
}

bool edge_detect_final()
{
	g_EdgeDetectSrcImage = imread("../images/edge_detect.jpg");
	if(g_EdgeDetectSrcImage.empty())
	{
		cout<<"g_EdgeDetectSrcImage is empty!!!"<<endl;
		return false;
	}
	g_CannyEdgeDetectDstImage = g_EdgeDetectSrcImage.clone();
	g_SobelEdgeDetectDstImage = g_EdgeDetectSrcImage.clone();
	imshow("g_EdgeDetectSrcImage Window", g_EdgeDetectSrcImage);
	cvtColor(g_EdgeDetectSrcImage, g_EdgeDetectSrcGrayImage, COLOR_BGR2GRAY);

	namedWindow("Canny Edge Detect Window", WINDOW_AUTOSIZE);
	namedWindow("Sobel Edge Detect Window", WINDOW_AUTOSIZE);
	namedWindow("Laplacian Edge Detect Window", WINDOW_AUTOSIZE);

	createTrackbar("lowThreshold:", "Canny Edge Detect Window", &g_cannyLowThreshold, 120, cannyEdge_cb);
	createTrackbar("kSize:", "Sobel Edge Detect Window", &g_sobelKernelSize, 3, sobelEdge_cb);
	createTrackbar("kSize:", "Laplacian Edge Detect Window", &g_laplacianKernelSize, 3, laplacianEdge_cb);

	cannyEdge_cb(0, 0);
	sobelEdge_cb(0, 0);
	laplacianEdge_cb(0, 0);
	scharrProcess();
	
	return true;
}

bool hough_lines_transform()
{
	Mat houghSrcImage = imread("../images/hough_lines.jpg");
	if(houghSrcImage.empty())
	{
		cout<<"houghSrcImage is empty!!!"<<endl;
		return false;
	}
	imshow("houghSrcImage Window", houghSrcImage);
	Mat houghGrayImage;
	Mat houghDstImage, houghPDstImage;
	Canny(houghSrcImage, houghGrayImage, 50, 200, 3);
	imshow("houghGrayImage Window", houghGrayImage);
	cvtColor(houghGrayImage, houghDstImage, COLOR_GRAY2BGR);
	imshow("houghDstImage Window", houghDstImage);
	vector<Vec2f> lines;
	HoughLines(houghGrayImage, lines, 1, CV_PI/180, 150, 0, 0);
	// Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( houghDstImage, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
    }

	imshow("houghDstImage after draw lines Window", houghDstImage);

	cvtColor(houghGrayImage, houghPDstImage, COLOR_GRAY2BGR);
	// imshow("houghDstImage Window", houghDstImage);
	vector<Vec4f> linesP;
	HoughLinesP(houghGrayImage, linesP, 1, CV_PI/180, 80, 50, 10);
	// Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( houghPDstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, LINE_AA);
    }

	imshow("houghPDstImage after draw lines Window", houghPDstImage);

	return true;
}

bool hough_circle_transform()
{

	return true;
}


void imgproc_functionality_imagetransform::process()
{
	// canny_edge();
	// sobel_edge();
	// laplacian_edge();
	// scharr_edge();
	// edge_detect_final();
	hough_lines_transform();
}