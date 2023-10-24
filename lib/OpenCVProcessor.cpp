// Copyright 2023 Tarun Trilokesh

/**
 * @file OpenCVProcessor.cpp
 * @brief Implementation of the OpenCVProcessor class.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#include "OpenCVProcessor.h"

/**
 * @brief Processes the given frame using OpenCV functions.
 * 
 * This function applies a Gaussian blur to the input frame as a sample image processing step.
 * More OpenCV functions or operations can be added to this method to process the frame further.
 * 
 * @param frame The input frame (image) to be processed.
 */
void OpenCVProcessor::processImages(const cv::Mat& frame) {
    // Apply Gaussian blur as a sample image processing step
    cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0);
}

