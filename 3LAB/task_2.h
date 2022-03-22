#ifndef TASK_2_H
#define TASK_2_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

Point findCenter1(Mat image, vector<Point> contour);

void findVehicle(string img_path);

#endif // TASK_2_H
