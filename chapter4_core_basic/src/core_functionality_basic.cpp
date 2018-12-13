#include "core_functionality_basic.h"

#define WINDOW_WIDTH 600

core_functionality_basic::core_functionality_basic(Mat &input_image)
{
    image = input_image.clone();
}

core_functionality_basic::~core_functionality_basic()
{

}

void DrawEllipse( Mat img, double angle )
{
	int thickness = 2;
	int lineType = 8;

	ellipse( img,
		Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2 ),
		Size( WINDOW_WIDTH/4, WINDOW_WIDTH/16 ),
		angle,
		0,
		360,
		Scalar( 255, 129, 0 ),
		thickness,
		lineType );
}

void DrawFilledCircle( Mat img, Point center )
{
	int thickness = -1;
	int lineType = 8;

	circle( img,
		center,
		WINDOW_WIDTH/32,
		Scalar( 0, 0, 255 ),
		thickness,
		lineType );
}

void DrawPolygon( Mat img )
{
	int lineType = 8;

	//create points
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(    WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][1]  = Point(  3*WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][2]  = Point(  3*WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );
	rookPoints[0][3]  = Point( 11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][4]  = Point( 19*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][5]  = Point(  3*WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][6]  = Point(  3*WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][7]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][8]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][9]  = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][10] = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][11] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][12] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][13] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][14] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][15] = Point(    WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][16] = Point(    WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][17] = Point( 13*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][18] = Point(  5*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][19] = Point(    WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly( img,
		ppt,
		npt,
		1,
		Scalar( 255, 255, 255 ),
		lineType );
}

void DrawLine( Mat img, Point start, Point end )
{
	int thickness = 2;
	int lineType = 8;
	line( img,
		start,
		end,
		Scalar( 0, 0, 0 ),
		thickness,
		lineType );
}

void core_functionality_basic::process()
{
    cout<<"-----------Mat demos-------------"<<endl;
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout<<"M = "<<endl<<M<<endl;

    Mat L;
    L.create(4, 4, CV_8UC2);
    cout<<"L = "<<endl<<L<<endl;

    Mat E = Mat::eye(4, 4, CV_64F);
    Mat O = Mat::ones(2, 2, CV_32F);
    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    cout<<"E = "<<endl<<E<<endl;
    cout<<"O = "<<endl<<O<<endl;
    cout<<"Z = "<<endl<<Z<<endl;

    Mat C = (Mat_<double>(3, 3)<< 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout<<"C = "<<endl<<C<<endl;
    Mat rowclone = C.row(1).clone();
    cout<<"rowclone = "<<endl<<rowclone<<endl;

    Mat r = Mat(3, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));

    cout<<"opencv default:"<<r<<endl;
    cout<<"python style:"<<endl<<format(r, Formatter::FMT_PYTHON)<<endl;
    cout<<"csv style:"<<endl<<format(r, Formatter::FMT_CSV)<<endl;
    cout<<"numpy style:"<<endl<<format(r, Formatter::FMT_NUMPY)<<endl;
    cout<<"c style:"<<endl<<format(r, Formatter::FMT_C)<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"-----------Point demos-------------"<<endl;
    Point2f p2f = Point2f(6, 2);
    cout<<"2d point2f:"<<p2f<<endl;

    Point3f p3f = Point3f(8, 2, 0);
    cout<<"3d point3f:"<<p3f<<endl;
    cout<<"-----------------------------------"<<endl;

    Mat atomImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );
	Mat rookImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );

	DrawEllipse( atomImage, 90 );
	DrawEllipse( atomImage, 0 );
	DrawEllipse( atomImage, 45 );
	DrawEllipse( atomImage, -45 );

	DrawFilledCircle( atomImage, Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2) );

	DrawPolygon( rookImage );

	rectangle( rookImage,
		Point( 0, 7*WINDOW_WIDTH/8 ),
		Point( WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar( 0, 255, 255 ),
		-1,
		8 );

	DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

	imshow( "picture 1", atomImage );
	moveWindow( "picture 1", 0, 200 );
	imshow( "picture 2", rookImage );
	moveWindow( "picture 2", WINDOW_WIDTH, 200 );
}