#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace cv;
const int max_value_H = 360 / 2;
const int max_value = 255;
const String window_capture_name = "frame";
const String window_detection_name = "hsvframe";
//-----------------CHANGE THESE VALUES-------------------
int low_H = 100, low_S = max_value*0.02, low_V = max_value*0.25;
int high_H = 150, high_S = max_value*0.26, high_V = max_value*0.41;
//---------------------------------------------------------

int main()
{
    namedWindow(window_capture_name);
    namedWindow(window_detection_name);
    Mat frame, frame_HSV, frame_threshold;

    std::string image_path = "pic2.JPG";
    frame = imread(image_path, IMREAD_COLOR);
    if (frame.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    // Convert from BGR to HSV colorspace
    cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
    // Detect the object based on HSV Range Values
    inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
    // Show the frames
    imshow(window_capture_name, frame);
    imshow(window_detection_name, frame_threshold);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        std::cout << "closing";
    }

    return 0;
}
