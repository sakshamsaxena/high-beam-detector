#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <wiringPi.h>

using namespace cv;

int main(int, char**)
{
	VideoCapture cap(0); // open the default camera

	wiringPiSetup () ;
	pinMode (0, OUTPUT) ; //High-beam
	pinMode (1, OUTPUT) ; //Low-beam

	digitalWrite(0, HIGH) ; //Set high beam
	digitalWrite(1, LOW) ; //Unset low beam

	// Constants
	int fWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //True frame width
	int fHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //True frame height
	int cHeight = floor(fHeight * 0.7); // Cropped height
	int cWidth = fWidth; // Width remains same
	int X = 0; // X of Top left corner of Rectangle
	int Y = fHeight - cHeight; // Y of Top left corner of Rectangle
	int flag = 0; // Flag which would set during active circuit

	// Frame matrix and cropping rectangle initialization
	Mat frame;

	Mat frame_original; // for storing complete frame of detected_image
	Mat detected_image; // variable for storing detected frame
	
	Rect cropper(X, Y, cWidth, cHeight);
	int _delta = 5;
	int _min_area = 800;
	int _max_area = 3000;
	std::vector<std::vector<Point> > contours;
	std::vector<Rect> bboxes;
	Ptr< MSER > mser = MSER::create(_delta, _min_area, _max_area);

	int count = 0; //number of detected frames
	char file1[15],file2[15]; //for storing file names 

	// Iterating over each frame
	for (;;)
	{
		cap >> frame_original; // Webcam image to an empty frame

		frame = frame_original(cropper); // Cropping same frame
		cvtColor(frame, frame, CV_BGR2GRAY); // Grayscale conversion of same frame
		threshold(frame, frame, 200, 255, THRESH_TOZERO); // Threshold at 200 value
		mser->detectRegions(frame, contours, bboxes);

		if (bboxes.size() && !flag) {
			//High Beam detected

			detected_image = frame; //save detected frame;
			sprintf(file1,"Image_%d.jpg",count);  //save files with different names using 'count'     
			imwrite(file1,detected_image);
			//imwrite("detected_frame.jpg",detected_image); //write the saved frame on the directory

			detected_frame = frame_original;
			sprintf(file2,"Frame_%d.jpg",count);  //save files with different names using 'count'     
			imwrite(file2,frame_original);

			flag = 1;
			digitalWrite (0, LOW) ; // unset high beam
			digitalWrite (1, HIGH); // set low beam
			delay(5000);		// wait for 5 seconds
			count++;
		}
		if (bboxes.size() && flag) {
			continue;
		}
		if (!bboxes.size()) {
			//No beam detected yet
			flag = 0;
			digitalWrite (0, HIGH); // High beam is set as usual
			digitalWrite (1, LOW);  // Low beam is unset as usual
		}

		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
