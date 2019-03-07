#pragma once

//lib
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

class imgproc_functionality_imagetransform
{
    private:
        Mat image;
    public:
        imgproc_functionality_imagetransform(Mat &input_image);
        ~imgproc_functionality_imagetransform();
    public:
        void process();

};