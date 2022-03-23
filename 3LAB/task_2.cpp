#include "task_2.h"

const double MIN_CONTOUR_AREA = 80;
const double MAX_TO_MIN_COUNTOUR_RATIO = 2;


void findVehicle(string img_path) {
    Mat src_color = imread(img_path, IMREAD_COLOR);
    Mat src_hsv = src_color.clone();
    // Перевод картинки в HSV формат
    cvtColor(src_color, src_hsv, COLOR_BGR2HSV);
    Mat threshold_color;
    inRange(src_hsv, Scalar(0, 50, 100), Scalar(30, 255, 255), threshold_color);
    imshow("threshold_color", threshold_color);
    Mat kernel;
    //Morphological filtering to remove small areas.
    for (int j = 0; j < 1; j++) {
        erode(threshold_color, threshold_color, kernel);
    }
    for (int j = 0; j < 3; j++) {
        dilate(threshold_color, threshold_color, kernel);
    }
    imshow("threshold_color_morphoroded", threshold_color);

    Mat thr_clone = threshold_color.clone();
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
        if (biggest_area / contours_areas.at(i) >= MAX_TO_MIN_COUNTOUR_RATIO)
            continue;
        drawContours(src_color, contours, i, CV_RGB(255, 255, 255));
        circle(src_color, findCenter(src_color, contours.at(i)), 5, CV_RGB(0, 0, 0), FILLED);
    }
    imshow("DST", src_color);
    waitKey(0);
}
