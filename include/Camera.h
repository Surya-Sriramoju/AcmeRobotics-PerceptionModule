// Copyright 2023 Tarun Trilokesh

/**
 * @file Camera.h
 * @brief Declaration of the Camera class for capturing images.
 * @author Tarun Trilokesh
 * @date 10/23/2023
 */

#pragma once

#include <opencv2/opencv.hpp>

/**
 * @class Camera
 * @brief Handles camera operations such as capturing images and releasing the camera.
 * 
 * This class provides an interface to interact with a camera using OpenCV. 
 * It allows for capturing images from the camera and releasing the camera when done.
 */
class Camera {
 public:
    /**
     * @brief Default constructor for the Camera class.
     * 
     * Initializes the camera. If the camera fails to open, an error message is displayed.
     */
    Camera();

    /**
     * @brief Captures an image from the camera.
     * 
     * This method captures a single frame (image) from the camera and returns it.
     * 
     * @return cv::Mat - The captured frame.
     */
    cv::Mat captureImage();

    /**
    * @brief reads an existing image
    * This method reads an image from the directory
    */
    cv::Mat readImage();


    /**
     * @brief Releases the camera.
     * 
     * This method releases the camera, freeing up any resources associated with it.
     */


    void release();

 private:
    cv::VideoCapture cap;  ///< Video capture object for accessing the camera.
};
