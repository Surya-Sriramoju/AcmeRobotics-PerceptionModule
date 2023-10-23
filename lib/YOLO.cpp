// Copyright 2023 Tarun Trilokesh

/**
 * @file YOLO.cpp
 * @brief Implementation of the YOLO class.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#include "YOLO.h"

/**
 * @brief Constructor for the YOLO class.
 * 
 * Initializes the YOLO model by loading the weights and configuration files.
 * Sets the preferable backend and target for the DNN module in OpenCV.
 */
YOLO::YOLO() {
    net = cv::dnn::readNet("models/yolov3.weights", "models/yolov3.cfg");
    if (net.empty()) {
        std::cerr << "Error loading YOLO model" << std::endl;
        exit(-1);
    }
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

/**
 * @brief Detects objects in the given frame using the YOLO model.
 * 
 * The function processes the frame using the YOLO model, detects objects,
 * and annotates the frame with bounding boxes around detected objects.
 * 
 * @param frame The input frame (image) in which objects are to be detected.
 */
void YOLO::detect(cv::Mat& frame) {
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1/255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);

    std::vector<cv::Mat> d;
    net.forward(d, net.getUnconnectedOutLayersNames());

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
                cv::rectangle(frame, cv::Point(left, top), cv::Point(left + width, top + height), cv::Scalar(0, 255, 0), 2);
            }
        }
    }
}

/**
 * @brief Classifies objects in the given frame.
 * 
 * This function can be expanded to classify objects detected in the frame.
 * Currently, it's a placeholder and does not contain any logic.
 * 
 * @param frame The input frame (image) in which objects are to be classified.
 */
void YOLO::classify(cv::Mat& frame) {
    // Classification logic can be added here if needed
}
