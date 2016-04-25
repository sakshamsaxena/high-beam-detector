#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <wiringPi.h>

using namespace cv;

int main(int, char**)
{
    VideoCapture cap("./Trip_LowRes.mp4"); // open the default camera

    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;

    // Set FPS to 10
    cap.set(CV_CAP_PROP_FPS, 10);

    // Constants
    int fWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //True frame width
    int fHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //True frame height
    int cHeight = floor(fHeight * 0.7); // Cropped height
    int cWidth = fWidth; // Width remains same
    int X = 0; // X of Top left corner of Rectangle
    int Y = fHeight - cHeight; // Y of Top left corner of Rectangle
    
    // Frame matrix and cropping rectangle initialization
    Mat frame;
    Rect cropper(X, Y, cWidth, cHeight);
    
    
    std::vector<std::vector<Point> > contours;
    std::vector<Rect> bboxes;
    Ptr< MSER > mser = MSER::create();

    
    // Iterating over each frame
    for(;;)
    {
        cap >> frame; // Webcam image to an empty frame
        frame = frame(cropper); // Cropping same frame
        cvtColor(frame, frame, CV_BGR2GRAY); // Grayscale conversion of same frame
        threshold(frame, frame, 200, 255, THRESH_TOZERO); // Threshold at 200 value
        mser->detectRegions(frame, contours, bboxes);

	if(bboxes.size())
		digitalWrite (0,  LOW) ;
	else
		digitalWrite (0,  HIGH) 

        imshow("cropped", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
