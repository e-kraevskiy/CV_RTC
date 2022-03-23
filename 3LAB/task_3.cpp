#include "task_3.h"
bool SHOW_DEBUG = true;
void findRobots(string img_path) {
    Mat src_color = imread(img_path, IMREAD_COLOR);
    Mat src_hsv = src_color.clone();
    // Перевод картинки в HSV формат
    cvtColor(src_color, src_hsv, COLOR_BGR2HSV);
    Mat threshold_red;
    Mat threshold_red_add;
    Mat threshold_green;
    Mat threshold_blue;
    inRange(src_hsv, Scalar(0, 50, 50), Scalar(20 , 255, 255), threshold_red);
    inRange(src_hsv, Scalar(170, 50, 50), Scalar(180, 255, 255), threshold_red_add);
    inRange(src_hsv, Scalar(68, 50, 50), Scalar(80, 255, 255), threshold_green);
    inRange(src_hsv, Scalar(90, 50, 50), Scalar(160, 255, 255), threshold_blue);
    if (SHOW_DEBUG) {
        threshold_red = threshold_red + threshold_red_add;
        imshow("threshold_green", threshold_green);
//        imshow("threshold_blue", threshold_blue);
//        imshow("threshold_red", threshold_red);
        waitKey(0);
    }
    Mat kernel;
    //Morphological filtering to remove small areas.
    morphoFiltering(threshold_red);
    morphoFiltering(threshold_green);
    morphoFiltering(threshold_blue);

    if (SHOW_DEBUG) {
        imshow("threshold_green_morphoroded", threshold_green);
//        imshow("threshold_blue_morphoroded", threshold_blue);
//        imshow("threshold_red_morphoroded", threshold_red);
        waitKey(0);
    }

    processRobots(threshold_green, src_color, CV_RGB(0, 255, 0));
    processRobots(threshold_blue, src_color, CV_RGB(0, 0, 255));
    processRobots(threshold_red, src_color, CV_RGB(255, 0, 0));

    waitKey(0);
}

void morphoFiltering(Mat &src) {
    Mat kernel;
    for (int j = 0; j < 2; j++) {
        erode(src, src, kernel);
    }
    for (int j = 0; j < 3; j++) {
        dilate(src, src, kernel);
    }
}

void processRobots(Mat &src, Mat &src_color, const Scalar& color) {
    Mat thr_clone = src.clone();
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<double> contours_areas;
    double biggest_area = 0;
    findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Находим нибольшую площадь контура
    for (int i = 0; i < contours.size(); i++) {
        double current_area = contourArea(contours.at(i));
        if (current_area > biggest_area)
            biggest_area = current_area;
        contours_areas.push_back(current_area);
    }
    for (int i = 0; i < contours.size(); i++) {
        // Убираем слишком маленькие контуры
        if (biggest_area / contours_areas.at(i) >= 5)
            continue;
        drawContours(src_color, contours, i, color, 3);
        circle(src_color, findCenter(src_color, contours.at(i)), 3, CV_RGB(0, 0, 0), FILLED);
    }
    imshow("DST", src_color);
    if (SHOW_DEBUG) {
    }

}
