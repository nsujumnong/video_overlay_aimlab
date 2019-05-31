#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

//global variables
const int red_low_max = 255;
const int red_hight_max = 255;
int red_low, red_high;
double red_l,red_h;

const int green_low_max = 255;
const int green_hight_max = 255;
int green_low, green_high;
double green_l,green_h;

const int blue_low_max = 255;
const int blue_hight_max = 255;
int blue_low, blue_high;
double blue_l,blue_h;

void on_trackbar(int, void*)
{
    red_l = getTrackbarPos("Red Low","Image Result1");
    red_h = getTrackbarPos("Red High","Image Result1");

    green_l = getTrackbarPos("Green Low","Image Result1");
    green_h = getTrackbarPos("Green High","Image Result1");

    blue_l = getTrackbarPos("Blue Low","Image Result1");
    blue_h = getTrackbarPos("Blue High","Image Result1");
}

//void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color);

void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color)
{
    *dst = Mat(under.rows, under.cols, CV_8UC3);

//    int underColor0 = under.at<Vec3b>(0,0)[0];
//    int underColor1 = under.at<Vec3b>(0,0)[1];
//    int underColor2 = under.at<Vec3b>(0,0)[2];
//
//    cout << underColor0 << endl;
//    cout << underColor1 << endl;
//    cout << underColor2 << endl;

    for(int y=0; y<under.rows;y++)
    {
        for(int x=0; x<under.cols;x++)
        {
            int overColor0 = over.at<Vec3b>(y,x)[0];
            int overColor1 = over.at<Vec3b>(y,x)[1];
            int overColor2 = over.at<Vec3b>(y,x)[2];

            int underColor0 = under.at<Vec3b>(y,x)[0];
            int underColor1 = under.at<Vec3b>(y,x)[1];
            int underColor2 = under.at<Vec3b>(y,x)[2];

//            cout << overColor0 << endl;
//            cout << overColor1 << endl;
//            cout << overColor2 << endl;
//
//            cout << underColor0 << endl;
//            cout << underColor1 << endl;
//            cout << underColor2 << endl;

//            cout << over.at<Vec3b>(y,x) << endl;
//            cout << red_l << endl;
//            cout << red_h << endl;
//            cout << green_l << endl;
//            cout << green_h << endl;
//            cout << blue_l << endl;
//            cout << blue_h << endl;

            if(over.at<Vec3b>(y,x)[0] >= red_l && over.at<Vec3b>(y,x)[0] <= red_h && over.at<Vec3b>(y,x)[1] >= green_l && over.at<Vec3b>(y,x)[1] <= green_h && over.at<Vec3b>(y,x)[2] >= blue_l && over.at<Vec3b>(y,x)[2] <= blue_h)
            //if(overColor0 >= red_l && overColor0 <= red_h && overColor1 >= green_l && overColor1 <= green_h && overColor2 >= blue_l && overColor2 <= blue_h)
            {
                //cout << "true" << endl;
                dst->at<Vec3b>(y,x)[0] = under.at<Vec3b>(y,x)[0];
                dst->at<Vec3b>(y,x)[1] = under.at<Vec3b>(y,x)[1];
                dst->at<Vec3b>(y,x)[2] = under.at<Vec3b>(y,x)[2];

            }
            else
            {
                //cout << "false" << endl;
                dst->at<Vec3b>(y,x)[0] = over.at<Vec3b>(y,x)[0];
                dst->at<Vec3b>(y,x)[1] = over.at<Vec3b>(y,x)[1];
                dst->at<Vec3b>(y,x)[2] = over.at<Vec3b>(y,x)[2];
            }
        }
    }
}

int main() {
    //VideoCapture cap("../plane.mp4"); // Plane video on top layer
    //VideoCapture cap(0); // endoscope on tope layer
    VideoCapture cap("../screencast_02.mp4");
    VideoCapture cap1(0);

    Mat imgRBG, imgRBG1, combined_images;

    int key = 0;
    Mat background = imread("../fjord.jpg");

    namedWindow("Image Result1", 1);

    createTrackbar("Red Low", "Image Result1", 0, 255, on_trackbar);
    createTrackbar("Red High", "Image Result1", 0, 255, on_trackbar);

    createTrackbar("Green Low", "Image Result1", 0, 255, on_trackbar);
    createTrackbar("Green High", "Image Result1", 0, 255, on_trackbar);

    createTrackbar("Blue Low", "Image Result1", 0, 255, on_trackbar);
    createTrackbar("Blue High", "Image Result1", 0, 255, on_trackbar);

    cvSetTrackbarPos("Red Low", "Image Result1", 134);
    cvSetTrackbarPos("Red High", "Image Result1", 220);

    cvSetTrackbarPos("Green Low", "Image Result1", 0);
    cvSetTrackbarPos("Green High", "Image Result1", 255);

    cvSetTrackbarPos("Blue Low", "Image Result1", 0);
    cvSetTrackbarPos("Blue High", "Image Result1", 121);



    while(key!=27){
        cap >> imgRBG;
        cap1 >> imgRBG1;
        chromakey(background,imgRBG, &combined_images, Scalar(100,200,185));

        imshow("Image Result1", combined_images);

        key = waitKey(30);
    }

    cap.release();

    return 0;
}
