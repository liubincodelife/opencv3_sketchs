#include "core_functionality_pro.h"

#define WINDOW_WIDTH 600

int g_nContrastValue = 80;
int g_nBrightValue = 80;

Mat g_srcImage, g_dstImage;

core_functionality_pro::core_functionality_pro(Mat &input_image)
{
    image = input_image.clone();
}

core_functionality_pro::~core_functionality_pro()
{

}

void trackbar_cb(int value, void* param)
{
	/*Mat& tempImage = *(Mat*)param;
	Mat dstImage = tempImage.clone();
	if(dstImage.empty())
	{
		cout<<"dstImage is empty!!!"<<endl;
		return;
	}*/
	int nRows = g_dstImage.rows;
	int nChannels = g_dstImage.channels();
	int nCols = g_dstImage.cols;
	for(int i = 0; i < nRows; i++)
	{
		for(int j = 0; j < nCols; j++)
		{
			for(int c = 0; c < nChannels; c++)
			{
				g_dstImage.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(g_nContrastValue * 0.01 * g_srcImage.at<Vec3b>(i, j)[c] + g_nBrightValue);
			}
		}
	}

	imshow("change contrast and bright", g_dstImage);
}

void change_contrast_bright()
{
	g_srcImage = imread("../images/girl2.jpg");
	if(g_srcImage.empty())
	{
		cout<<"g_srcImage is empty!!!"<<endl;
		return;
	}
	namedWindow("src image");
	namedWindow("change contrast and bright");

	imshow("src image", g_srcImage);
	g_dstImage = g_srcImage.clone();
	createTrackbar("contrast:", "change contrast and bright", &g_nContrastValue, 300, trackbar_cb);
	createTrackbar("bright:", "change contrast and bright", &g_nBrightValue, 200, trackbar_cb);

	trackbar_cb(g_nContrastValue, 0);
	//trackbar_cb(g_nBrightValue, 0);

}

bool ROI_AddImage()
{
	Mat srcImage = imread("../images/dota_pa.jpg");
	Mat logoImage = imread("../images/dota_logo.jpg");
	if(srcImage.empty())
	{
		cout<<"srcImage is empty!!!"<<endl;
		return false;
	}

	if(logoImage.empty())
	{
		cout<<"logoImage is empty!!!"<<endl;
		return false;
	}

	Mat imageROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));
	//mask must be gray image
	Mat mask = imread("../images/dota_logo.jpg", 0);
	logoImage.copyTo(imageROI, mask);

	imshow("srcImage after mask", srcImage);

	return true;
}

bool Linear_Blending()
{
	double alphaValue = 0.5;
	Mat srcImage = imread("../images/mogu.jpg");
	Mat maskImage = imread("../images/rain.jpg");
	if(srcImage.empty())
	{
		cout<<"srcImage is empty!!!"<<endl;
		return false;
	}

	if(maskImage.empty())
	{
		cout<<"maskImage is empty!!!"<<endl;
		return false;
	}
	Mat dstImage;
	addWeighted(srcImage, alphaValue, maskImage, 1 - alphaValue, 0.0, dstImage);

	imshow("srcImage mogu", srcImage);
	imshow("maskImage rain", maskImage);
	imshow("dstImage mogu+rain", dstImage);

	return true;
}

bool ROI_Linear_Blending()
{
	Mat srcImage = imread("../images/dota_pa.jpg");
	Mat logoImage = imread("../images/dota_logo.jpg");
	if(srcImage.empty())
	{
		cout<<"srcImage is empty!!!"<<endl;
		return false;
	}

	if(logoImage.empty())
	{
		cout<<"logoImage is empty!!!"<<endl;
		return false;
	}
	Mat roiImage = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));
	addWeighted(roiImage, 0.5, logoImage, 0.3, 0.0, roiImage);
	imshow("dstImage ROI_Linear_Blending", srcImage);
	return true;
}

bool image_multichannel_blending()
{
	Mat srcImage = imread("../images/dota_jugg.jpg");
	Mat logoImage = imread("../images/dota_logo.jpg", 0); //gray image
	vector<Mat> imageChannels;
	if(srcImage.empty())
	{
		cout<<"srcImage is empty!!!"<<endl;
		return false;
	}

	if(logoImage.empty())
	{
		cout<<"logoImage is empty!!!"<<endl;
		return false;
	}

	split(srcImage, imageChannels);

	Mat imageBlueChannel = imageChannels.at(0);
	Mat imageGreenChannel = imageChannels.at(1);
	Mat imageRedChannel = imageChannels.at(2);

	Mat dstImage;
	merge(imageChannels, dstImage);

	imshow("imageBlueChannel", imageBlueChannel);
	imshow("imageGreenChannel", imageGreenChannel);
	imshow("imageRedChannel", imageRedChannel);
	imshow("dstImage merge channels", dstImage);

	//blue channel
	Mat bcImageROI = imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows));
	addWeighted(bcImageROI, 1.0, logoImage, 0.5, 0.0, bcImageROI);
	imshow("blue channel add logo", imageBlueChannel);

	Mat mergeImageBlue;
	merge(imageChannels, mergeImageBlue);
	imshow("merge blue channel logo", mergeImageBlue);

	//green channel
	Mat gcImageROI = imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows));
	addWeighted(gcImageROI, 1.0, logoImage, 0.5, 0.0, gcImageROI);
	imshow("green channel add logo", imageGreenChannel);

	Mat mergeImageGreen;
	merge(imageChannels, mergeImageGreen);
	imshow("merge green channel logo", mergeImageGreen);

	//red channel
	Mat rcImageROI = imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows));
	addWeighted(rcImageROI, 1.0, logoImage, 0.5, 0.0, rcImageROI);
	imshow("red channel add logo", imageRedChannel);

	Mat mergeImageRed;
	merge(imageChannels, mergeImageRed);
	imshow("merge red channel logo", mergeImageRed);
	return true;
}

void image_blending()
{
	ROI_AddImage();
	Linear_Blending();
	ROI_Linear_Blending();
}

bool image_dft()
{
	Mat srcImage = imread("../images/food.jpg", 0);
	if(srcImage.empty())
	{
		cout<<"srcImage is empty!!!"<<endl;
		return false;
	}
	imshow("srcImage", srcImage);
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	cout<<"nRows = "<<nRows<<endl<<"nCols = "<<nCols<<endl<<endl;
	int nRowsEx = getOptimalDFTSize(srcImage.rows);
	int nColsEx = getOptimalDFTSize(srcImage.cols);
	cout<<"nRowsEx = "<<nRowsEx<<endl<<"nColsEx = "<<nColsEx<<endl<<endl;
	Mat expandImage;
	copyMakeBorder(srcImage, expandImage, 0, nRowsEx - nRows, 0, nColsEx - nCols, BORDER_CONSTANT, Scalar::all(0));
	imshow("expandImage", expandImage);

	Mat planes[] = {Mat_<float>(expandImage), Mat::zeros(expandImage.rows, expandImage.cols, CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);
	dft(complexI, complexI);
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);

	Mat magnitudeImage = planes[0];

	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);
   
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	Mat tempMagnitudeImage = magnitudeImage.clone();
	normalize(tempMagnitudeImage, tempMagnitudeImage, 0, 1, NORM_MINMAX);
	//cout<<"magnitudeImage src"<<magnitudeImage<<endl;
 	imshow("magnitudeImage src", tempMagnitudeImage);
	int cx = magnitudeImage.cols/2;
	int cy = magnitudeImage.rows/2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); 

	Mat tmp;                           
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                 
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX); 
	imshow("magnitudeImage center calibration", magnitudeImage);

	return true;
}

bool xml_yaml_read()
{
	FileStorage fs2("../files/test.yaml", FileStorage::READ);  

	int frameCount = (int)fs2["frameCount"];  

	std::string date;  
	fs2["calibrationDate"] >> date;  

	Mat cameraMatrix2, distCoeffs2;  
	fs2["cameraMatrix"] >> cameraMatrix2;  
	fs2["distCoeffs"] >> distCoeffs2;  

	cout << "frameCount: " << frameCount << endl  
		<< "calibration date: " << date << endl  
		<< "camera matrix: " << cameraMatrix2 << endl  
		<< "distortion coeffs: " << distCoeffs2 << endl;  

	FileNode features = fs2["features"];  
	FileNodeIterator it = features.begin(), it_end = features.end();  
	int idx = 0;  
	std::vector<uchar> lbpval;  

	for( ; it != it_end; ++it, idx++ )  
	{  
		cout << "feature #" << idx << ": ";  
		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";  
		(*it)["lbp"] >> lbpval;  
		for( int i = 0; i < (int)lbpval.size(); i++ )  
			cout << " " << (int)lbpval[i];  
		cout << ")" << endl;  
	}  
	fs2.release();
	return true;
}

bool xml_yaml_write()
{
	// FileStorage fs("../files/test.yaml", FileStorage::WRITE);  
	// FileStorage fs("../files/test.xml", FileStorage::WRITE); 
	// FileStorage fs("../files/test.txt", FileStorage::WRITE); 
	FileStorage fs("../files/test.doc", FileStorage::WRITE);

	fs << "frameCount" << 5;  
	time_t rawtime; time(&rawtime);  
	fs << "calibrationDate" << asctime(localtime(&rawtime));  
	Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);  
	Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);  
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;  
	fs << "features" << "[";  
	for( int i = 0; i < 3; i++ )  
	{  
		int x = rand() % 640;  
		int y = rand() % 480;  
		uchar lbp = rand() % 256;  

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";  
		for( int j = 0; j < 8; j++ )  
			fs << ((lbp >> j) & 1);  
		fs << "]" << "}";  
	}  
	fs << "]";  
	fs.release();  
	return true;
}

void core_functionality_pro::process()
{
	//change contrast and bright demo
    // change_contrast_bright();
	//image blending demos
	// image_blending();
	//multichannel image blending demo
	// image_multichannel_blending();
	//DFT transfer demo
	// image_dft();
	xml_yaml_write();
	// xml_yaml_read();
}