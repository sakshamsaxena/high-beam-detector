#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <wiringPi.h>

using namespace cv;

int main(int, char**)
{
    VideoCapture cap("./video.mp4"); // open the default camera

/*    wiringPiSetup () ;
    pinMode (0, OUTPUT) ; //High-beam
    pinMode (1, OUTPUT) ; //Low-beam

    digitalWrite(0, HIGH) ; //Set high beam
    digitalWrite(1, LOW) ; //Unset low beam
*/
    // Constants
    int fWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //True frame width
    int fHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //True frame height
    int cHeight = floor(fHeight * 0.7); // Cropped height
    int cWidth = fWidth; // Width remains same
    int X = 0; // X of Top left corner of Rectangle
    int Y = fHeight - cHeight; // Y of Top left corner of Rectangle
    int x = 0;

    // Frame matrix and cropping rectangle initialization
    Mat frame;
    Rect cropper(X, Y, cWidth, cHeight);
    int _delta = 5;
    int _min_area = 800;
    int _max_area = 3000;
    std::vector<std::vector<Point> > contours;
    std::vector<Rect> bboxes;
    Ptr< MSER > mser = MSER::create(_delta, _min_area, _max_area);

    std::ofstream datadump;

    // Iterating over each frame
    for(;;)
    {
        cap >> frame; // Webcam image to an empty frame
        frame = frame(cropper); // Cropping same frame
        cvtColor(frame, frame, CV_BGR2GRAY); // Grayscale conversion of same frame
        threshold(frame, frame, 200, 255, THRESH_TOZERO); // Threshold at 200 value
        mser->detectRegions(frame, contours, bboxes);

	if(bboxes.size() && !x){
		//High Beam detected
		std::cout<<"Detected at "<<cap.get(CV_CAP_PROP_POS_FRAMES)<<"\n";
		datadump.open("Data.txt", std::ofstream::out | std::ofstream::app);
		datadump<<"High Beam detected at "<<cap.get(CV_CAP_PROP_POS_FRAMES)<<".Lowering beam...\n";
		datadump.close();
		x = 1;
		//digitalWrite (0, LOW) ; // unset high beam
		//digitalWrite (1, HIGH); // set low beam
		delay(5000);		// wait for 5 seconds
	}
	else if(bboxes.size() && x) continue;
	else{
		//No beam detected yet
		std::cout<<"No high beam detected yet at "<<cap.get(CV_CAP_PROP_POS_FRAMES)<<"\n";
		x = 0;
		//digitalWrite (0, HIGH); // High beam is set as usual
		//digitalWrite (1, LOW);  // Low beam is unset as usual
	}
	//imshow("Yeah", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
