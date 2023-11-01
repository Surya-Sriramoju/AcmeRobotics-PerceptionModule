// Copyright 2023 Sai Surya Sriramoju

/**
 * @file CoordToWorld.h
 * @author Sai Surya Sriramoju
 * @date 10/31/2023
 * @version 1.0
 *
 * @brief A utility for projecting bounding box pixel values to real world coordinates using a camera matrix.
 *
 * This class provides functionality to convert pixel coordinates from a camera's frame of reference to a robot's frame of reference.
 * It computes a projection matrix using a given camera matrix and provides a method to compute world coordinates from pixel coordinates.
 */

#pragma once

#include <Eigen/Dense>
#include <vector>
#include <opencv2/opencv.hpp>

using Eigen::MatrixXf;
using cv::Mat;

/**
 * @brief Class for converting pixel coordinates to world coordinates.
 *
 * This class contains methods to compute a projection matrix and use it to convert pixel coordinates to world coordinates.
 */
class CoordToWorld {
public:
    /**
     * @brief Default constructor.
     */
    CoordToWorld() {}

    /**
     * @brief A vector to hold coordinate values.
     */
    std::vector<double> coordValues;

    /**
     * @brief Computes the projection matrix.
     *
     * This method computes a projection matrix to be used for converting pixel coordinates to world coordinates.
     *
     * @return MatrixXf - The computed projection matrix.
     */
    MatrixXf transMat();

    /**
     * @brief Computes world coordinates from pixel coordinates.
     *
     * This method takes a projection matrix and a vector of pixel coordinates, and computes the corresponding world coordinates.
     *
     * @param T - The projection matrix.
     * @param coorValues - A vector of pixel coordinates.
     * @return std::vector<double> - A vector of computed world coordinates in XYZ format.
     */
    std::vector<double> worldPoints(MatrixXf T, std::vector<double> coorValues);

private:
    /**
     * @brief The focal length of the camera.
     */
    static double focalLen;
};
