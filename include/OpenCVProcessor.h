// Copyright 2023 Tarun Trilokesh

/**
 * @file OpenCVProcessor.h
 * @brief Declaration of the OpenCVProcessor class for image processing.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#pragma once

#include <opencv2/opencv.hpp>

/**
 * @class OpenCVProcessor
 * @brief Handles image processing operations using OpenCV.
 * 
 * This class provides an interface to apply various image processing techniques 
 * on frames (images) using OpenCV. It currently supports a sample processing method 
 * that applies a Gaussian blur, but more methods can be added as needed.
 */
class OpenCVProcessor {
public:
    /**
     * @brief Processes the given frame using OpenCV functions.
     * 
     * This method applies various image processing techniques on the input frame.
     * As of now, it applies a Gaussian blur as a sample processing step. More 
     * processing steps can be added to this method as needed.
     * 
     * @param frame The input frame (image) to be processed.
     */
    void processImages(cv::Mat& frame);
};

