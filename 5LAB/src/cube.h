#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

const int DICTINARY_ID = 10;
const float MARKER_SIZE = 0.069;
const string CAMERA_CALIB_PARAM = "../5LAB/calibration.xml";
const cv::Scalar CUBE_COLOUR = cv::Scalar(255, 141, 187);


int startDetecting();

void drawCube(cv::InputOutputArray image, cv::InputArray cameraMatrix,
    cv::InputArray distCoeffs, cv::InputArray rvec, cv::InputArray tvec,
    float edge_size);

#endif // CUBE_H
