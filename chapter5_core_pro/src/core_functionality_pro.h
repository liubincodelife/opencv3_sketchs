#pragma once

//lib
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include<iostream>

using namespace cv;
using namespace std;

class core_functionality_pro
{
    private:
        Mat image;
    public:
        core_functionality_pro(Mat &input_image);
        ~core_functionality_pro();
    public:
        void process();

};