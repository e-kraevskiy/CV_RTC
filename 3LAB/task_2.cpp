#include "task_2.h"

const double MIN_CONTOUR_AREA = 80;

Point findCenter1(Mat image, vector<Point> contour) {
    Rect r = boundingRect(contour);
    Point center(r.x+0.5*r.width, r.y+0.5*r.height);
    return center;
}

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
    findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours.at(i)) < MIN_CONTOUR_AREA)
            continue;
        cout << "contour area =" << contourArea(contours.at(i)) << endl;
        drawContours(src_color, contours, i, CV_RGB(255, 255, 255));
        circle(src_color, findCenter1(src_color, contours.at(i)), 5, CV_RGB(0, 0, 0), FILLED);
    }
    cout << endl;
    imshow("DST", src_color);
    waitKey(0);
}
