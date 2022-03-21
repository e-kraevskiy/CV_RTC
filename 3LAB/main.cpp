#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task_1.h"

using namespace std;
using namespace cv;

const string allababah_0 = "../3LAB/img_zadan/allababah/ig_0.jpg";
const string allababah_1 = "../3LAB/img_zadan/allababah/ig_1.jpg";
const string allababah_2 = "../3LAB/img_zadan/allababah/ig_2.jpg";




int main() {
    findTarget(allababah_0);
    findTarget(allababah_1);
    findTarget(allababah_2);
    return 0;
}
