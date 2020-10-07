#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

#define vid1 "roadmarked.mp4"
#define vid2 "plainroadwithnocar.mp4"
using namespace cv;
int main() {

    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap(vid2);

    // Check if camera opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    //temp variable for getting video fram dimesions
    Mat tempsrc;
    cap >> tempsrc;
    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
    //last arg is true if output video is in RGB
    VideoWriter video("outcpp.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25,tempsrc.size(), true);
    
    while (1) {
        Mat dst, cdst, cdstP;
        Mat src;
        // Capture frame-by-frame
        cap >> src;

        // If the frame is empty, break immediately
        if (src.empty())
            break;

        blur(src, src, Size(8, 8));
        // Edge detection
        Canny(src, dst, 20, 20*3, 3);

        // Copy edges to the images that will display the results in BGR
        cvtColor(dst, cdst, COLOR_GRAY2BGR);
        //cdstP = cdst.clone();
        // Standard Hough Line Transform
        std::vector<Vec2f> lines; // will hold the results of the detection
        HoughLines(dst, lines, 1, CV_PI / 180, 175, 0, 0); // runs the actual detection
        // Draw the lines
        for (size_t i = 0; i < lines.size(); i++)
        {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
        }

        //record frame
        video.write(cdst);

        // Display the resulting frame
        //imshow("Source", src);
        //imshow("Edited", cdst);
        // Press  ESC on keyboard to exit
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();
    // Closes all the frames
    destroyAllWindows();

    return 0;
}
