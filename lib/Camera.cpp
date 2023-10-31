// Copyright 2023 Tarun Trilokesh

/**
 * @file Camera.cpp
 * @brief Implementation of the Camera class.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#include "Camera.h"

/**
 * @brief Constructor for the Camera class. Initializes the camera.
 */
Camera::Camera() {
    // cap.open(0);  // Open the default camera (index 0)
    // if (!cap.isOpened()) {
    //     std::cerr << "Error opening camera" << std::endl;
    //     exit(-1);
    // }
}

/**
 * @brief Captures an image using the camera.
 * @return cv::Mat - The captured frame.
 */
cv::Mat Camera::captureImage() {
    cv::Mat frame;
    cap >> frame;  // Capture a frame from the camera
    return frame;
}

cv::Mat Camera::readImage()
{
    cv::Mat image = cv::imread("./data/people.jpg");
    return image;
}

/**
 * @brief Releases the camera.
 */
void Camera::release() {
    cap.release();
}
