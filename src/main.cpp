// Copyright 2023 Tarun Trilokesh

/**
 * @file main.cpp
 * @author  Tarun Trilokesh
 * @date    10/23/2023
 * @version 1.0
 * 
 * @brief Main entry point for the AcmeRobotics-PerceptionModule project.
 *
 * This program initializes video capture from a camera using OpenCV,
 * sets up a window to display the video feed, and implements
 * human detection using YOLO.
 */

#include "Camera.h"
#include "YOLO.h"
#include "OpenCVProcessor.h"
#include "CoordToWorld.h"

/**
 * @brief Main function to run the AcmeRobotics-PerceptionModule project.
 * 
 * Initializes the Camera, YOLO, and OpenCVProcessor classes. Captures video frames
 * from the camera, detects humans using the YOLO model, processes the frames using
 * OpenCV functions, and displays the processed frames in a window.
 * 
 * @return int - Returns 0 on successful execution.
 */
int main() {
    // Camera object to capture video frames.
    Camera camera;
    // YOLO object for human detection.
    YOLO yolo;
    // OpenCVProcessor object for image processing.
    OpenCVProcessor opencvProcessor;
    // CoordToWorld object for coordinate transformation.
    CoordToWorld world_coord;
    
    while (true) {  // Continuous loop to process video frames
        // Capture image using Camera class.
        cv::Mat frame = camera.captureImage();
        if (frame.empty()) {
            break;  // Break the loop if no more frames
        }
        
        // Detect humans using YOLO.
        std::vector<double> pixel_coords = yolo.detect(frame);
        // Process the captured frame.
        opencvProcessor.processImages(frame);
        // Compute the transformation matrix.
        MatrixXf TM(3, 4);
        TM = world_coord.transMat();
        // Compute real world coordinates.
        std::vector<double> real_world = world_coord.worldPoints(TM, pixel_coords);
        int count = 1;  // Counter for number of persons detected
        for (long unsigned int i = 0; i < 2; i = i + 3) {
            std::cout << "Person " << count
                      << " world coordinates :" << real_world.at(i) << ", "
                      << real_world.at(i + 1) << ", " << real_world.at(i + 2) << "\n";
            count++;
        }
        // @brief Display the processed frame.
        cv::imshow("Camera", frame);
        if (cv::waitKey(1) == 'q') {
            break;  // Break the loop if 'q' is pressed
        }

    }
    // Release the camera.
    camera.release();
    // Destroy all OpenCV windows.
    cv::destroyAllWindows();

    return 0;
}
