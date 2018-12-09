#include "highgui_functionality.h"

int g_nAlphaValue = 0;
const int  g_nAlphaValueMax = 100;
Mat g_image1, g_image2; 
Rect g_rectangle;
bool g_bDrawBox;
RNG rng(12345);

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
    double dAlphaValue = (double)g_nAlphaValue / g_nAlphaValueMax;
    double dBetaValue = (double)1 - dAlphaValue;
    Mat dstimage;
    addWeighted(g_image1, dAlphaValue, g_image2, dBetaValue, 0.0, dstimage);
    imshow("addweight image", dstimage);
}

void mouse_cb(int event, int x, int y, int flags, void* param)
{
    Mat& draw_image = *(Mat*)param;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            // cout<<"EVENT_MOUSEMOVE..."<<endl;
            if(g_bDrawBox)
            {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
            break;
        case EVENT_MOUSEWHEEL:
            // cout<<"EVENT_MOUSEWHEEL..."<<endl;
            break;
        case EVENT_LBUTTONDOWN:
            // cout<<"EVENT_LBUTTONDOWN..."<<endl;
            g_bDrawBox = true;
            g_rectangle = Rect(x, y, 0, 0);
            break;
        case EVENT_LBUTTONUP:
            // cout<<"EVENT_LBUTTONUP..."<<endl;
            g_bDrawBox = false;
            if(g_rectangle.width < 0)
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if(g_rectangle.height < 0)
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            rectangle(draw_image, g_rectangle, Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)));
            break;

        default:
            break;
    }
}

void picture_display()
{
    Mat image_girl = imread("../images/girl.jpg");
    if(image_girl.empty())
    {
        cout<<"image girl is empty!!!"<<endl;
        return;
    }
    namedWindow("highgui image girl");
    imshow("highgui-image girl", image_girl);

    Mat image_dota = imread("../images/dota.jpg");
    Mat image_logo = imread("../images/dota_logo.jpg");
    if(image_dota.empty())
    {
        cout<<"image dota is empty!!!"<<endl;
        return;
    }
    if(image_logo.empty())
    {
        cout<<"image logo is empty!!!"<<endl;
        return;
    }
    namedWindow("highgui-image dota");
    namedWindow("highgui-image logo");
    imshow("highgui-image dota", image_dota);
    imshow("highgui-image logo", image_logo);

    Mat image_ROI = image_dota(Rect(800, 350, image_logo.cols, image_logo.rows));
    namedWindow("highgui-image ROI");
    imshow("highgui-image ROI",image_ROI);
    addWeighted(image_ROI, 0.5, image_logo, 0.3, 0, image_ROI);
    namedWindow("highgui-addweight");
    imshow("highgui-addweight", image_dota);

    imwrite("../images/image_dota_weight.jpg", image_dota);
}

void picture_linearmix()
{
    g_image1 = imread("../images/1.jpg");
    g_image2 = imread("../images/2.jpg");
    namedWindow("addweight image");
    if(g_image1.empty())
    {
        cout<<"image g_image1 is empty!!!"<<endl;
        return;
    }

    if(g_image2.empty())
    {
        cout<<"image g_image1 is empty!!!"<<endl;
        return;
    }

    g_nAlphaValue = 50;
    createTrackbar("alpha", "addweight image", &g_nAlphaValue, g_nAlphaValueMax, trackbar_cb);
    trackbar_cb(g_nAlphaValue, 0);
}

void drag_mouse2draw()
{
    Mat image_background(600, 800, CV_8UC3), temp_image;
    image_background = Scalar::all(0);
    g_rectangle = Rect(-1, -1, 0, 0);
    g_bDrawBox = false;
    namedWindow("draw background");
    setMouseCallback("draw background", mouse_cb, (void *)&image_background);
    while(1)
    {
        // image_background.copyTo(temp_image);
        temp_image = image_background.clone(); //解决拖动矩形重影问题
        if(g_bDrawBox)
        {
            rectangle(temp_image, g_rectangle, Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)));
        }
        imshow("draw background", temp_image);
        if(waitKey(10) == 27) //click esc to stop drawing...
            break;
    }
}

void highgui_functionality::process()
{
    //demo1:picture display
    // picture_display();
    //demo2:picture linearmix
    // picture_linearmix();
    //demo3:drawing rect to image
    drag_mouse2draw();
    // Mat grayimage;
    // cvtColor(image, grayimage, COLOR_BGR2GRAY);
    // namedWindow("gray image", CV_WINDOW_AUTOSIZE);
    // imshow("gray image", grayimage);
    // vector<int> compression_params;
    // compression_params.push_back(IMWRITE_JPEG_QUALITY);
    // compression_params.push_back(95);
    // imwrite("../images/lena_gray.jpg", grayimage, compression_params);
    // createTrackbar("alpha", "gray image", &g_nAlphaValue, g_nAlphaValueMax, trackbar_cb);
    // setMouseCallback("gray image", mouse_cb);
}