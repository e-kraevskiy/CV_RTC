#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"

using namespace std;
using namespace cv;
// img for 1 task
const string allababah_0 = "../3LAB/img_zadan/allababah/ig_0.jpg";
const string allababah_1 = "../3LAB/img_zadan/allababah/ig_1.jpg";
const string allababah_2 = "../3LAB/img_zadan/allababah/ig_2.jpg";
// img for 2 task
const string teplovizor_0 = "../3LAB/img_zadan/teplovizor/0.jpg";
const string teplovizor_1 = "../3LAB/img_zadan/teplovizor/1.jpg";
const string teplovizor_2 = "../3LAB/img_zadan/teplovizor/2.jpg";
const string teplovizor_3 = "../3LAB/img_zadan/teplovizor/3.png";
const string teplovizor_4 = "../3LAB/img_zadan/teplovizor/4.jpg";
// img for 3 task
const string roboti_0 = "../3LAB/img_zadan/roboti/1.jpg";
const string roboti_1 = "../3LAB/img_zadan/roboti/2.jpg";
const string video = "../3LAB/img_zadan/roboti/robot_video.mp4";
// img for 4 task
const string gk = "../3LAB/img_zadan/gk/gk.jpg";
const string gk_ref = "../3LAB/img_zadan/gk/gk_ref.jpg";

int main() {
  // ******** 1 TASK ********
  findTarget(allababah_0);
  findTarget(allababah_1);
  findTarget(allababah_2);
  // ******** 2 TASK ********
  findVehicle(teplovizor_0);
  findVehicle(teplovizor_1);
  findVehicle(teplovizor_2);
  findVehicle(teplovizor_3);
  findVehicle(teplovizor_4);
  // ******** 3 TASK ********
  Mat tmp = imread(roboti_0, IMREAD_COLOR);
  findRobots(tmp);
  tmp = imread(roboti_1, IMREAD_COLOR);
  findRobots(tmp);

  //    processVideo(video);
  // ******** 4 TASK ********
  findRightGK(gk, gk_ref);

  return 0;
}
