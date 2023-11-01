// Copyright 2023 Tarun Trilokesh

/**
 * @file YOLO.h
 * @brief Declaration of the YOLO class for detection and classification.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#pragma once

#include <string>
#include <opencv2/opencv.hpp>

/**
 * @class YOLO
 * @brief Handles object detection and classification using the YOLO model.
 * 
 * This class provides an interface to interact with the YOLO (You Only Look Once) model 
 * using OpenCV's DNN module. It allows for object detection and classification on 
 * frames (images) captured from a camera or any other source.
 */
class YOLO {
 public:
    static const std::string modelsDir;

    /**
     * @brief Default constructor for the YOLO class.
     * 
     * Initializes the YOLO model by loading the weights and configuration files.
     * Sets the preferable backend and target for the DNN module in OpenCV.
     */
    YOLO();

    /**
     * @brief Detects objects in the given frame using the YOLO model.
     * 
     * This method processes the frame using the YOLO model, detects objects,
     * and annotates the frame with bounding boxes around detected objects.
     * 
     * @param frame The input frame (image) in which objects are to be detected.
     */
    std::vector<double> detect(const cv::Mat& frame);

    /**
     * @brief Classifies objects in the given frame.
     * 
     * This function can be expanded to classify objects detected in the frame.
     * Currently, it's a placeholder and does not contain any logic.
     * 
     * @param frame The input frame (image) in which objects are to be classified.
     */
    void classify(const cv::Mat& frame);

 private:
    cv::dnn::Net net;  // Adjusted spaces between code and comment
};

