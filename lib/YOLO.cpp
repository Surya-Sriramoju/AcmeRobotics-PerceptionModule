// Copyright 2023 Tarun Trilokesh

/**
 * @file YOLO.cpp
 * @brief Implementation of the YOLO class.
 * @author Tarun Trilokesh (driver Sprint 1)
           Sai Surya Sriramoju (Driver Sprint 2)
 * @date 10/23/2023
 */

#include "YOLO.h"
#include <stdexcept>

// If MODELS_DIR is defined, use it. Otherwise, use "./models"
#ifdef MODELS_DIR
    const std::string YOLO::modelsDir = MODELS_DIR;
#else
    const std::string YOLO::modelsDir = "./models";
#endif

/**
 * @brief Constructor for YOLO class that initializes the YOLO model.
 *
 * Loads the YOLO model weights and configurations. It also sets the backend
 * and target for the DNN module in OpenCV for efficient processing.
 */
YOLO::YOLO() {
    // Load the YOLO network
    std::string weightsPath = modelsDir + "/yolov3.weights";
    std::string cfgPath = modelsDir + "/yolov3.cfg";
    net = cv::dnn::readNet(weightsPath, cfgPath);

    // Error handling for network loading
    if (net.empty()) {
        throw std::runtime_error("Error loading YOLO model");
    }

    // Set the backend and target for efficient processing
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

/**
 * @brief Detects objects in the given frame using the YOLO model.
 *
 * Processes the frame, detects objects, performs NMS, detects the number of objects and annotates the frame with bounding
 * boxes around detected objects.
 * 
 * @param frame The input frame (image) in which objects are to be detected.
 */
void YOLO::detect(const cv::Mat& frame) {
    // Convert the image to blob for neural network preprocessing
    cv::Mat blob = cv::dnn::blobFromImage(
        frame, 1/255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);

    std::vector<cv::Mat> d;
    net.forward(d, net.getUnconnectedOutLayersNames());
    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;
    std::vector<int> class_ids;

    struct Detection {
        int class_id;
        float confidence;
        cv::Rect box;
    };


    for (size_t i = 0; i < d.size(); ++i) {
        float* data = reinterpret_cast<float*>(d[i].data);
        for (int j = 0; j < d[i].rows; ++j, data += d[i].cols) {
            cv::Mat scores = d[i].row(j).colRange(5, d[i].cols);
            cv::Point classIdPoint;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

            if (confidence > 0.5) {
                class_ids.push_back(classIdPoint.x);
                int centerX = static_cast<int>(data[0] * frame.cols);
                int centerY = static_cast<int>(data[1] * frame.rows);
                int width = static_cast<int>(data[2] * frame.cols);
                int height = static_cast<int>(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                // Annotate the frame with a bounding box
                // cv::Point topL(left, top);
                // cv::Point bottomR(left + width, top + height);
                // cv::rectangle(frame, topL, bottomR, cv::Scalar(0, 255, 0), 2);

                boxes.push_back(cv::Rect(left, top, width, height));
                confidences.push_back(confidence);
            }
        }
    }

    // Non Maximum Suppression
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, 0.2, 0.2, indices);
    std::vector<Detection> output;

    for (size_t i=0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Detection result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }

    int no_detections = output.size();
    std::cout << "No of human detections: " << no_detections << "\n";
    std::vector<double> pixel_coords;
    const std::vector<cv::Scalar> colors = {
      cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255),
      cv::Scalar(255, 0, 0)};

    for (int i = 0; i < no_detections; ++i) {
        auto detection_params = output[i];
        auto box = detection_params.box;
        auto classIdx = detection_params.class_id;
        const auto color = colors[classIdx % colors.size()];
        pixel_coords.push_back(box.x);
        pixel_coords.push_back(box.y);
        cv::rectangle(frame, box, (color), 3);
        cv::rectangle(frame, cv::Point(box.x, box.y - 35), cv::Point(box.x + box.width, box.y), color, cv::FILLED);
        cv::putText(frame,
                ("Human_" + std::to_string(i + 1)),
                cv::Point(box.x, box.y - 5), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(0, 0, 0), 2);
    }

}

/**
 * @brief Placeholder method for classifying objects in a frame.
 *
 * This function can be expanded to classify objects detected in the frame in
 * future implementations.
 * 
 * @param frame The input frame (image) in which objects can be classified.
 */
void YOLO::classify(const cv::Mat& frame) {
    // Classification logic can be added here in the future
}

