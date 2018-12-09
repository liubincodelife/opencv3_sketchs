#pragma once

//lib
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

class highgui_functionality
{
    private:
        Mat image;
    public:
        highgui_functionality(Mat &input_image);
        ~highgui_functionality();
    public:
        void process();

};