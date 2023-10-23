// Copyright 2023 Tarun Trilokesh

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


int main() {
    // Capture video from camera
    cv::VideoCapture cap(0);  // Video capture object

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    // Load YOLO model
    cv::dnn::Net net = cv::dnn::readNet("models/yolov3.weights",
                                        "models/yolov3.cfg");
    if (net.empty()) {
        std::cerr << "Error loading YOLO model" << std::endl;
        return -1;
    }
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    while (true) {
        cv::Mat frame;  // Frame buffer
        cap >> frame;  // Capture a frame

        // Check if the frame is empty
        if (frame.empty()) {
            break;
        }

        // Process frame using YOLO for human detection
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1/255.0,
                                              cv::Size(416, 416),
                                              cv::Scalar(0, 0, 0), true, false);
        net.setInput(blob);

        // Get detections from the model
        std::vector<cv::Mat> d;
        net.forward(d, net.getUnconnectedOutLayersNames());

        // Parse detections and annotate the frame
        for (size_t i = 0; i < d.size(); ++i) {
            float* data = reinterpret_cast<float*>(d[i].data);
            for (int j = 0; j < d[i].rows; ++j, data += d[i].cols) {
                cv::Mat scores = d[i].row(j).colRange(5, d[i].cols);
                cv::Point classIdPoint;
                double confidence;
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > 0.5 && classIdPoint.x == 0) {
                    int centerX = static_cast<int>(data[0] * frame.cols);
                    int centerY = static_cast<int>(data[1] * frame.rows);
                    int width = static_cast<int>(data[2] * frame.cols);
                    int height = static_cast<int>(data[3] * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;
                    cv::rectangle(frame, cv::Point(left, top),
                                cv::Point(left + width, top + height),
                                cv::Scalar(0, 255, 0), 2);
                }
            }
        }

        // Display the frame
        cv::imshow("Frame", frame);

        // Break the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera and destroy all OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
