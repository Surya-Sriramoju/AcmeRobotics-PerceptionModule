/**
 * @file main.cpp
 * @author  Tarun Trilokesh
 * @date    10/15/2023
 * @version 1.0
 * 
 * @brief Main entry point for the AcmeRobotics-PerceptionModule project.
 *
 * This program initializes video capture from a camera using OpenCV,
 * sets up a window to display the video feed, and implements
 * human detection using YOLO.
 */

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

/**
 * @brief Main function.
 * 
 * Initializes video capture, enters a loop to capture frames, process them using YOLO for human detection,
 * and display the processed frames.
 * 
 * @return int Returns -1 if there's an error opening the camera, 0 otherwise.
 */
int main() {
    // Capture video from camera
    cv::VideoCapture cap(0);  ///< Video capture object
    
    // Check if the camera opened successfully
    if(!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    // Load YOLO model
    cv::dnn::Net net = cv::dnn::readNet("models/yolov3.weights", "models/yolov3.cfg");
    if (net.empty()) {
        std::cerr << "Error loading YOLO model" << std::endl;
        return -1;
    }
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    while(true) {
        cv::Mat frame;  ///< Frame buffer
        cap >> frame;  // Capture a frame
        
        // Check if the frame is empty (e.g., end of video or error)
        if(frame.empty()) break;

        // Process frame using YOLO for human detection
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
        net.setInput(blob);

        // Get detections from the model
        std::vector<cv::Mat> detections;
        net.forward(detections, net.getUnconnectedOutLayersNames());

        // TODO: Parse detections, assign class IDs to human predictions, and annotate the frame

        // Display the frame
        cv::imshow("Frame", frame);
        
        // Break the loop if the 'q' key is pressed
        if(cv::waitKey(1) == 'q') break;
    }

    // Release the camera and destroy all OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
