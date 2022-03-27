#include "task_4.h"
#include "task_1.h"


void findRightGK(string img_path, string ref_img_path) {
    // img reading
    Mat src_color = imread(img_path, IMREAD_COLOR);
    Mat ref_color = imread(ref_img_path, IMREAD_COLOR);
    waitKey(0);
    Mat src = imread(img_path, IMREAD_GRAYSCALE);
    Mat ref = imread(ref_img_path, IMREAD_GRAYSCALE);
    // threshold mat
    Mat src_thr;
    Mat ref_thr;
    // threshold
    threshold(src, src_thr, 200, 255, THRESH_BINARY);
    threshold(ref, ref_thr, 200, 255, THRESH_BINARY);
    // invert src image
    bitwise_not(src_thr, src_thr);

    Mat src_thr_clone = src_thr.clone();
    Mat ref_thr_clone = ref_thr.clone();
    vector<vector<Point>> contours;
    vector<vector<Point>> ref_countour;
    vector<Vec4i> hierarchy;

    findContours(src_thr_clone, contours, hierarchy,
                 RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(ref_thr_clone, ref_countour, hierarchy,
                 RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<int> valid_id;

    // Сравнение при помощи matchShapes
    for (int i = 0; i < contours.size(); i++) {
        double dif = matchShapes(contours.at(i),  ref_countour.at(0),
                                 CONTOURS_MATCH_I2, 0);
        drawContours(src_color, contours, i, CV_RGB(255, 0, 0), 3);
        if (dif < 0.1) {
            cout << "if pushed back=" << i << endl;
            valid_id.push_back(i);
        }
    }
    // draw valid keys
    for (int i = 0; i < valid_id.size(); i++) {
        drawContours(src_color, contours, valid_id.at(i), CV_RGB(50, 200, 50), 3);
    }

    imshow("Task 4 result", src_color);
    waitKey(0);
}
