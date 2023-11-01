// Copyright 2023 Sai Surya Sriramoju

/**
 * @file CoordToWorld.cpp
 * @author Sai Surya Sriramoju (saisurya@umd.edu)
 * @date 10/31/2023
 * @version 1.0
 *
 * @brief Implements functionality for converting pixel coordinates to real world coordinates.
 *
 * Defines methods for computing a projection matrix and converting pixel coordinates to world coordinates
 * based on the intrinsic and extrinsic parameters of the camera.
 */

#include "CoordToWorld.h"

using Eigen::Matrix3f;
using Eigen::MatrixXf;
using Eigen::Vector3f;
using Eigen::Vector4f;

/**
 * @brief Sets the default focal length of the camera.
 */
double CoordToWorld::focalLen = 27.0;

/**
 * @brief Computes the projection matrix based on intrinsic and extrinsic camera parameters.
 *
 * The intrinsic matrix is defined based on the focal length of the camera, and the extrinsic matrix is assumed.
 * The method then computes the projection matrix by multiplying the intrinsic and extrinsic matrices.
 *
 * @return MatrixXf - The computed projection matrix.
 */
MatrixXf CoordToWorld::transMat() {
  Matrix3f intrinsic;
  intrinsic << focalLen, 0, 0, 0, focalLen, 0, 0, 0, 1;
  MatrixXf extrinsic(3, 4);
  extrinsic << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1;
  MatrixXf T(3, 4);
  T = intrinsic * extrinsic;
  return T;
}

/**
 * @brief Converts pixel coordinates to real world coordinates.
 *
 * Utilizes the computed projection matrix to convert given pixel coordinates to world coordinates.
 * The method iterates through the given vector of pixel coordinates, computes the corresponding world
 * coordinates, and populates a vector with these world coordinates which is then returned.
 *
 * @param T - The projection matrix.
 * @param coordValues - A vector of pixel coordinates.
 * @return std::vector<double> - A vector of computed world coordinates in XYZ format.
 */
std::vector<double> CoordToWorld::worldPoints(MatrixXf T, std::vector<double> coordValues) {

    std::vector<double> actual_world;
    MatrixXf pseudo_T(4,3);

    pseudo_T = T.completeOrthogonalDecomposition().pseudoInverse();

    for (long unsigned int i = 0; i < coordValues.size(); i = i+2) {
        double u = coordValues.at(i);
        double v = coordValues.at(i+1);

        Vector3f pixel_coord;
        pixel_coord << u, v, 1;
        Vector4f world_coord;

        world_coord = pseudo_T * pixel_coord;

        double x = world_coord[0] / world_coord[3];
        double y = world_coord[1] / world_coord[3];
        double z = world_coord[2] / world_coord[3];

        actual_world.push_back(x);
        actual_world.push_back(y);
        actual_world.push_back(z);

    }
    return actual_world;
}
