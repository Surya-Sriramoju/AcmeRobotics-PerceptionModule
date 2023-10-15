/**
 * @file main.cpp
 * @author  Tarun Trilokesh
 * @date    10/15/2023
 * @version 1.0
 * 
 * @brief Main entry point for the AcmeRobotics-PerceptionModule project.
 *
 * This program initializes video capture from a camera using OpenCV,
 * sets up a window to display the video feed, and lays the groundwork
 * for human detection and tracking to be added.
 */

#include <opencv2/opencv.hpp>

/**
 * @brief Main function.
 * 
 * Initializes video capture, enters a loop to capture frames and display them,
 * and sets up a placeholder for human detection and tracking functionality.
 * 
 * @return int Returns -1 if there's an error opening the camera, 0 otherwise.
 */
int main() {
    // Capture video from camera using the Video4Linux backend
    cv::VideoCapture cap(0, cv::CAP_V4L2);  ///< Video capture object
    
    // Check if the camera opened successfully
    if(!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    while(true) {
        cv::Mat frame;  ///< Frame buffer
        cap >> frame;  // Capture a frame
        
        // Check if the frame is empty (e.g., end of video or error)
        if(frame.empty()) break;

        // TODO: Human detection and tracking

        // Display the frame
        cv::imshow("Frame", frame);
        
        // Break the loop if a key is pressed
        if(cv::waitKey(1) >= 0) break;
    }

    // Release the camera and destroy all OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
