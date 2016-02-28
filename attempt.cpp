#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    int wd = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int ht = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int oht = floor(ht * 0.7);
    Mat edges;
    Mat cl;
    Rect r(0, ht - oht, wd, oht);
    // namedWindow("edges",1);
    for(;;)
    {
        cap >> edges;
        cl = edges(r);
        imshow("cropped", cl);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}