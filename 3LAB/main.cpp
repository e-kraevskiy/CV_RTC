#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task_1.h"
#include "task_2.h"

using namespace std;
using namespace cv;

const string allababah_0 = "../3LAB/img_zadan/allababah/ig_0.jpg";
const string allababah_1 = "../3LAB/img_zadan/allababah/ig_1.jpg";
const string allababah_2 = "../3LAB/img_zadan/allababah/ig_2.jpg";

const string teplovizor_0 = "../3LAB/img_zadan/teplovizor/0.jpg";
const string teplovizor_1 = "../3LAB/img_zadan/teplovizor/1.jpg";
const string teplovizor_2 = "../3LAB/img_zadan/teplovizor/2.jpg";
const string teplovizor_3 = "../3LAB/img_zadan/teplovizor/3.png";
const string teplovizor_4 = "../3LAB/img_zadan/teplovizor/4.jpg";



int main() {
//    findTarget(allababah_0);
//    findTarget(allababah_1);
//    findTarget(allababah_2);

    findVehicle(teplovizor_0);
    findVehicle(teplovizor_1);
    findVehicle(teplovizor_2);
    findVehicle(teplovizor_3);
    findVehicle(teplovizor_4);

    return 0;
}
