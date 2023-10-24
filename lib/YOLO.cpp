// Copyright 2023 Tarun Trilokesh

/**
 * @file YOLO.cpp
 * @brief Implementation of the YOLO class.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#include "YOLO.h"
#include <stdexcept>

// If MODELS_DIR is defined, use it. Otherwise, use "./models"
#ifdef MODELS_DIR
    const std::string YOLO::modelsDir = MODELS_DIR;
#else
    const std::string YOLO::modelsDir = "./models";
#endif

/**
 * @brief Constructor for YOLO class that initializes the YOLO model.
 *
 * Loads the YOLO model weights and configurations. It also sets the backend
 * and target for the DNN module in OpenCV for efficient processing.
 */
YOLO::YOLO() {
    // Load the YOLO network
    std::string weightsPath = modelsDir + "/yolov3.weights";
    std::string cfgPath = modelsDir + "/yolov3.cfg";
    net = cv::dnn::readNet(weightsPath, cfgPath);

    // Error handling for network loading
    if (net.empty()) {
        throw std::runtime_error("Error loading YOLO model");
    }

    // Set the backend and target for efficient processing
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

/**
 * @brief Detects objects in the given frame using the YOLO model.
 *
 * Processes the frame, detects objects, and annotates the frame with bounding
 * boxes around detected objects.
 * 
 * @param frame The input frame (image) in which objects are to be detected.
 */
void YOLO::detect(const cv::Mat& frame) {
    // Convert the image to blob for neural network preprocessing
    cv::Mat blob = cv::dnn::blobFromImage(
        frame, 1/255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);

    std::vector<cv::Mat> d;
    net.forward(d, net.getUnconnectedOutLayersNames());

    for (size_t i = 0; i < d.size(); ++i) {
        float* data = reinterpret_cast<float*>(d[i].data);
        for (int j = 0; j < d[i].rows; ++j, data += d[i].cols) {
            cv::Mat scores = d[i].row(j).colRange(5, d[i].cols);
            cv::Point classIdPoint;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > 0.5) {
                int centerX = static_cast<int>(data[0] * frame.cols);
                int centerY = static_cast<int>(data[1] * frame.rows);
                int width = static_cast<int>(data[2] * frame.cols);
                int height = static_cast<int>(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                // Annotate the frame with a bounding box
                cv::Point topL(left, top);
                cv::Point bottomR(left + width, top + height);
                cv::rectangle(frame, topL, bottomR, cv::Scalar(0, 255, 0), 2);
            }
        }
    }
}

/**
 * @brief Placeholder method for classifying objects in a frame.
 *
 * This function can be expanded to classify objects detected in the frame in
 * future implementations.
 * 
 * @param frame The input frame (image) in which objects can be classified.
 */
void YOLO::classify(const cv::Mat& frame) {
    // Classification logic can be added here in the future
}

