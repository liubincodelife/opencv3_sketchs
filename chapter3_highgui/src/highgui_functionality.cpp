#include "highgui_functionality.h"

int g_nAlphaValue = 0;
const int  g_nAlphaValueMax = 100;

highgui_functionality::highgui_functionality(Mat &input_image)
{
    image = input_image.clone();
}

highgui_functionality::~highgui_functionality()
{

}

void trackbar_cb(int, void*)
{
    cout<<"track bar value = "<<g_nAlphaValue<<endl;
}

void mouse_cb(int event, int x, int y, int flags, void* param)
{
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            cout<<"EVENT_MOUSEMOVE..."<<endl;
            break;
        case EVENT_MOUSEWHEEL:
            cout<<"EVENT_MOUSEWHEEL..."<<endl;
            break;
        case EVENT_LBUTTONDOWN:
            cout<<"EVENT_LBUTTONDOWN..."<<endl;
            break;
        case EVENT_LBUTTONUP:
            cout<<"EVENT_LBUTTONUP..."<<endl;
            break;

        default:
            break;
    }
}

void highgui_functionality::process()
{
    namedWindow("highgui_functionality", CV_WINDOW_AUTOSIZE);
    imshow("highgui_functionality", image);

    Mat grayimage;
    cvtColor(image, grayimage, COLOR_BGR2GRAY);
    namedWindow("gray image", CV_WINDOW_AUTOSIZE);
    imshow("gray image", grayimage);
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);
    imwrite("../images/lena_gray.jpg", grayimage, compression_params);
    createTrackbar("alpha", "gray image", &g_nAlphaValue, g_nAlphaValueMax, trackbar_cb);
    setMouseCallback("gray image", mouse_cb);
}