#include <iostream>  
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "imgproc_functionality_imagetransform.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image;
    image = imread("/home/liubin/workspace/opencv_demos/images/lena_color_256.tif");
    if(!image.data)
    {
        cout<<"image is empty!!!"<<endl;
        return -1;
    }
    namedWindow("display_image", CV_WINDOW_AUTOSIZE);
    imshow("display_image", image);

    imgproc_functionality_imagetransform imgproc_module(image);
    imgproc_module.process();
    waitKey(0);
    return 0;
}
