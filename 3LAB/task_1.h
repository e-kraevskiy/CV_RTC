#ifndef TASK_1_H
#define TASK_1_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

Point findCenter(vector<Point> contour);

void findTarget(string img_path);

#endif // TASK_1_H
