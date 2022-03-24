#include "task_1.h"

Point findCenter(vector<Point> contour) {
    Rect r = boundingRect(contour);
    Point center(r.x+0.5*r.width, r.y+0.5*r.height);
    return center;
}

void findTarget(string img_path) {
    Mat src_color = imread(img_path, IMREAD_COLOR);
    Mat src = imread(img_path, IMREAD_GRAYSCALE);
    Mat thr;
    threshold(src, thr, 200, 255, THRESH_BINARY);
    Mat kernel;
    //Morphological filtering to remove small areas.
    for (int j = 0; j < 3; j++) {
        erode(thr, thr, kernel);
    }
    for (int j = 0; j < 5; j++) {
        dilate(thr, thr, kernel);
    }

    Mat thr_clone = thr.clone();
    vector<vector<Point>>contours;
    vector<Vec4i> hierarchy;
    findContours(thr_clone, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); i++) {
        drawContours(src_color, contours, i, CV_RGB(0, 0, 255));
        circle(src_color, findCenter(contours.at(i)), 5, CV_RGB(255, 0, 0), FILLED);
    }
    imshow("DST", src_color);
    waitKey(0);
}
