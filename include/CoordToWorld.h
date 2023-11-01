/**
 * @file CoordToWorld.h
 * @author Sai Surya Sriramoju
 * @brief Projecting the bounding box pixel values to real world assuming a camera matrix of a camera
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <Eigen/Dense>
#include <vector>
#include <opencv2/opencv.hpp>

using Eigen::MatrixXf;

using cv::Mat;

/**
 * @brief This class converts pixel coordinates from camera to robot's frame of reference
 * 
 */

 class CoordToWorld{
    public:
     CoordToWorld() {}
     std::vector<double> coordValues;

    /**
     * @brief computes the projection matrix
     * @return returns the projection matrix
     */

     MatrixXf transMat();

     /**
      * @brief compute the world co-ordinates
      * 
      * @return XYZ co-ordinates
      */
     std::vector<double> worldPoints(MatrixXf T, std::vector<double> coorValues);

    private:
     static double focalLen;


 };



