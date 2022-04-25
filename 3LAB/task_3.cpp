#include "task_3.h"

#include "task_1.h"

bool SHOW_DEBUG = 0;
int BEAM_WIDTH = 25;
int BULB_AND_LAMPSHADE_DIST = 40;

void findRobots(Mat &src_color, bool is_video) {
  Mat src_hsv = src_color.clone();
  // Перевод картинки в HSV формат
  cvtColor(src_color, src_hsv, COLOR_BGR2HSV);

  Point bulbCenter = findLamp(src_color, src_hsv, CV_RGB(0, 0, 0));

  Mat threshold_red;
  Mat threshold_red_add;
  Mat threshold_green;
  Mat threshold_blue;
  inRange(src_hsv, Scalar(0, 50, 100), Scalar(10, 255, 255), threshold_red);
  inRange(src_hsv, Scalar(170, 50, 100), Scalar(180, 255, 255),
          threshold_red_add);
  inRange(src_hsv, Scalar(68, 50, 100), Scalar(78, 255, 255), threshold_green);
  inRange(src_hsv, Scalar(90, 50, 50), Scalar(160, 255, 255), threshold_blue);
  threshold_red = threshold_red + threshold_red_add;
  if (SHOW_DEBUG) {
    imshow("threshold_green", threshold_green);
    imshow("threshold_blue", threshold_blue);
    imshow("threshold_red", threshold_red);
    waitKey(0);
  }
  Mat kernel;
  // Morphological filtering to remove small areas.
  morphoFiltering(threshold_red);
  morphoFiltering(threshold_green);
  morphoFiltering(threshold_blue);

  if (SHOW_DEBUG) {
    imshow("threshold_green_morphoroded", threshold_green);
    imshow("threshold_blue_morphoroded", threshold_blue);
    imshow("threshold_red_morphoroded", threshold_red);
    waitKey(0);
  }

  processRobots(threshold_green, src_color, CV_RGB(0, 255, 0), bulbCenter);
  processRobots(threshold_blue, src_color, CV_RGB(0, 0, 255), bulbCenter);
  processRobots(threshold_red, src_color, CV_RGB(255, 0, 0), bulbCenter);

  imshow("Task 3 result", src_color);
  if (!is_video) waitKey(0);
}

void morphoFiltering(Mat &src) {
  Mat kernel;
  for (int j = 0; j < 2; j++) {
    erode(src, src, kernel);
  }
  for (int j = 0; j < 3; j++) {
    dilate(src, src, kernel);
  }
  for (int j = 0; j < 2; j++) {
    erode(src, src, kernel);
  }
  for (int j = 0; j < 2; j++) {
    dilate(src, src, kernel);
  }
}

void processRobots(Mat &src, Mat &src_color, const Scalar &color,
                   Point bulbCenter) {
  Mat thr_clone = src.clone();
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  vector<double> contours_areas;
  double biggest_area = 0;
  findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL,
               CHAIN_APPROX_SIMPLE);
  copeWithBeam(src, contours);
  thr_clone = src;
  findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL,
               CHAIN_APPROX_SIMPLE);

  // Обработка красного абажура лампы
  if (color == CV_RGB(255, 0, 0)) {
    for (int i = 0; i < contours.size(); i++) {
      Rect rect = boundingRect(contours.at(i));
      Point center = findCenter(contours.at(i));
      double dist = norm(bulbCenter - center);  // Euclidian distance
      if (dist > BULB_AND_LAMPSHADE_DIST - 10 and
          dist < BULB_AND_LAMPSHADE_DIST + 10 and bulbCenter.y > center.y) {
        contours.erase(contours.begin() + i);
        i--;
      }
    }
  }
  // Находим нибольшую площадь контура
  for (int i = 0; i < contours.size(); i++) {
    double current_area = contourArea(contours.at(i));
    if (current_area > biggest_area) biggest_area = current_area;
    contours_areas.push_back(current_area);
  }
  double smollest_lamp_dist = 999;
  double smollest_lamp_dist_id = 0;
  for (int i = 0; i < contours.size(); i++) {
    // Убираем слишком маленькие контуры и считаем расстояние до лампы
    if (biggest_area / contours_areas.at(i) >= 5) continue;
    Rect rect = boundingRect(contours.at(i));
    drawContours(src_color, contours, i, color, 3);
    double dist = norm(bulbCenter - findCenter(contours.at(i)));
    if (dist < smollest_lamp_dist) {
      smollest_lamp_dist = dist;
      smollest_lamp_dist_id = i;
    }
  }
  circle(src_color, findCenter(contours.at(smollest_lamp_dist_id)), 3,
         CV_RGB(0, 0, 0), FILLED);
}

Point findLamp(Mat &src_color, Mat &src_hsv, const Scalar &color) {
  Mat threshold_lamp;
  inRange(src_hsv, Scalar(0, 0, 245), Scalar(180, 10, 255), threshold_lamp);
  morphoFiltering(threshold_lamp);
  if (SHOW_DEBUG) {
    imshow("threshold_lamp", threshold_lamp);
    waitKey(0);
  }
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  Mat thr_clone = threshold_lamp.clone();
  findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL,
               CHAIN_APPROX_SIMPLE);
  Point lamp_center;
  // Находим наибольшую площадь контура
  double biggest_area = 0;
  int biggest_area_id = 0;
  vector<double> contours_areas;
  for (int i = 0; i < contours.size(); i++) {
    double current_area = contourArea(contours.at(i));
    if (current_area > biggest_area) {
      biggest_area = current_area;
      biggest_area_id = i;
    }
    contours_areas.push_back(current_area);
  }
  drawContours(src_color, contours, biggest_area_id, color, 3);
  lamp_center = findCenter(contours.at(biggest_area_id));
  circle(src_color, lamp_center, 3, color, FILLED);
  return lamp_center;
}

void copeWithBeam(Mat &src, vector<vector<Point>> &contours) {
  for (int i = 0; i < contours.size(); i++) {
    vector<Point> current_contour = contours.at(i);
    Point current_center = findCenter(contours.at(i));
    for (int j = 0; j < contours.size(); j++) {
      Point center = findCenter(contours.at(j));
      double dist = norm(current_center - center);  // Euclidian distance
      if (dist > BEAM_WIDTH - 5 and dist < BEAM_WIDTH + 5 and
          current_center.x < center.x) {
        Point print_center(current_center.x + (int)dist / 2, current_center.y);
        circle(src, print_center, (int)dist - 5, Scalar(255), FILLED);
      }
    }
  }
  contours.clear();
}

void processVideo(string video_path) {
  VideoCapture cap(video_path);
  Mat frame;
  cap >> frame;

  // check if we succeeded
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return;
  }
  //--- GRAB AND WRITE LOOP
  cout << "Press any key to exit" << endl;
  for (;;) {
    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);
    // check if we succeeded
    if (frame.empty()) {
      cerr << "ERROR! blank frame grabbed\n";
      break;
    }
    findRobots(frame, true);
    // show live and wait for a key with timeout long enough to show images
    imshow("Live", frame);
    if (waitKey(500) >= 0) break;
  }
}
