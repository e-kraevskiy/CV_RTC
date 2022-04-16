#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

#include "cube.h"

using namespace std;
using namespace cv;




int main() {

    startDetecting();
//    cv::VideoCapture inputVideo;
//    inputVideo.open(0);
//    cv::Mat cameraMatrix, distCoeffs;
//    // You can read camera parameters from tutorial_camera_params.yml
//    readCameraParameters("../5LAB/calibration.xml", cameraMatrix, distCoeffs); // This function is located in detect_markers.cpp
//    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
//    while (inputVideo.grab()) {
//        cv::Mat image, imageCopy;
//        inputVideo.retrieve(image);
//        image.copyTo(imageCopy);
//        std::vector<int> ids;
//        std::vector<std::vector<cv::Point2f>> corners;
//        cv::aruco::detectMarkers(image, dictionary, corners, ids);
//        // if at least one marker detected
//        if (ids.size() > 0) {
//            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
//            std::vector<cv::Vec3d> rvecs, tvecs;
//            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
//            // draw axis for each marker
//            for(int i=0; i<ids.size(); i++)
//                cv::drawFrameAxes(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.05);
//        }
//        cv::imshow("camra", imageCopy);
//        char key = (char) cv::waitKey(5);
//        if (key == 27)
//            break;
//    }
}
