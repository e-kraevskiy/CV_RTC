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

void findRobots(string img_path);

void morphoFiltering(Mat &src);

void processRobots(Mat &src, Mat &src_color, const Scalar& color);

void findLamp(Mat &src_color, Mat &src_hsv, const Scalar& color);

void copeWithBeam (Mat &src, vector<vector<Point>> &contours);

#endif // TASK_3_H
