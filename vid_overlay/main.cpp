#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    double alpha = 0.6; double beta; double input;
    Mat src1, src2, output;

    /// Ask the user enter alpha
//    std::cout<<" Simple Linear Blender "<<std::endl;
//    std::cout<<"-----------------------"<<std::endl;
//    std::cout<<"* Enter alpha [0-1]: ";
//    std::cin>>input;

    /// We use the alpha provided by the user if it is between 0 and 1
//    if( input >= 0.0 && input <= 1.0 )
//    { alpha = input; }

    /// Read image ( same size, same type )
    VideoCapture capture(0);
    VideoCapture vid("../nature.mp4");

    if(!capture.isOpened()){return -1;}
    if(!vid.isOpened()){return -1;}

    vid.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    vid.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    Mat img1;
    Mat img_resize;
    vid.read(img1);
    resize(img1, img1, Size(640,480), 0,0, INTER_CUBIC);

    src1 = imread("../winter.jpg");
    src2 = imread("../WindowsLogo.jpg");

    if( !src1.data ) { printf("Error loading src1 \n"); return -1; }
    if( !src2.data ) { printf("Error loading src2 \n"); return -1; }

    /// Create Windows
    namedWindow("Overlay", 1);

    beta = ( 1.0 - alpha );
    //addWeighted( src1, alpha, src2, beta, 0.0, dst);


    while(true){
        Mat frame;

        capture >> frame;
        if (frame.empty())
            break;

        addWeighted (src1, alpha, frame, beta, 0.0, output);

        imshow( "Overlay", output );
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }

    return 0;
}