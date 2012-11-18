#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>
#include <cstdio>
using namespace cv;
using namespace std;

// Stitches frames together to make a video in mpeg-4 format.
// Assumes the frames are jpegs named 001.jpg ... 00n.jpg and are in the folder
// where stitch is running.

int main (int argc, char * const argv[]) {
	
	// Read the first frame
	Mat frame = imread("001.jpg", CV_LOAD_IMAGE_COLOR);
	
	stringstream stream;
	
	// Create a VideoWriter that will create a file named test.avi.
	VideoWriter writer = VideoWriter("test.avi", CV_FOURCC('D', 'I', 'V', 'X'), 10, frame.size(), true);
	 
	if (!writer.isOpened()) {
		 printf("VideoWriter failed to open.");
		 return -1;
	}
	
	// Write the first frame to test.avi
	writer << frame;

	// Iterate through the rest of the frames and stitch them into a video.
	// I've hard coded 28 frames here - when I get a chance I'll change this to 
	// read the current directory and determine the number of files automatically.
	for (int i = 2; i < 28; i++) {
		stream.str("");
		stream.clear();
		
		stream << i;

    		string paddedFileName = "";
    		if (i < 100) {
        		if (i < 10) {
            			paddedFileName = "00" + stream.str();
       			 }
        		else {
            			paddedFileName = "0" + stream.str();
        		}
    		}
    		else {
        		paddedFileName = stream.str();
    		}
		
		frame = imread(paddedFileName + ".jpg", CV_LOAD_IMAGE_COLOR);
		writer << frame;
		
		printf("Wrote frame %d\n", i);
	}
	
    return 0;
}
