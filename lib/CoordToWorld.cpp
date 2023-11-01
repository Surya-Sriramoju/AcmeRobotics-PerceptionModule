/**
 * @file CoordToWorld.cpp
 * @author Sai Surya Sriramoju (saisurya@umd.edu)
 * @brief Converts the pixel coordinates of the detections to real worl coordinates
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "CoordToWorld.h"

using Eigen::Matrix3f;
using Eigen::MatrixXf;
using Eigen::Vector3f;
using Eigen::Vector4f;

double CoordToWorld::focalLen = 27.0;

MatrixXf CoordToWorld::transMat() {
  Matrix3f intrinsic;
  intrinsic << focalLen, 0, 0, 0, focalLen, 0, 0, 0, 1;
  MatrixXf extrinsic(3, 4);
  extrinsic << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1;
  MatrixXf T(3, 4);
  T = intrinsic * extrinsic;
  return T;
}

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
