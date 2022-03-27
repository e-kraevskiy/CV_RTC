#ifndef TASK_3_H
#define TASK_3_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <array>

#include "task_1.h"

using namespace std;
using namespace cv;

void findRobots(Mat &src_color, bool is_video = false);

void morphoFiltering(Mat &src);

void processRobots(Mat &src, Mat &src_color, const Scalar& color, Point bulbCenter);

Point findLamp(Mat &src_color, Mat &src_hsv, const Scalar& color);

void copeWithBeam (Mat &src, vector<vector<Point>> &contours);

void processVideo(string video_path);

#endif // TASK_3_H
