#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

using namespace std;
using namespace cv;

const string img_path = "/home/eugeniy/CV_1.jpg";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Mat img;
    string path = img_path;
    img = imread(path, IMREAD_COLOR);

//    circle(img,)
//    line(img, (60, 20), (400, 200), (0, 0, 255), 5);
    line(img, Point(60, 20), Point(400, 200), Scalar(0, 0, 255), 5);
    circle(img, Point( 200, 200 ), 32.0, Scalar( 0, 0, 255 ), 1, 8 );
    circle(img, Point( 300, 300 ), 32.0, Scalar( 0, 0, 255 ), 20);

    for (int t = 0; t <= 1256; t++) {
        circle(img, Point( t, (cos(((float)t)/100)*100)+100 ), 1.0, Scalar( 0, 0, 255 ), 2);
//        circle()
    }




    namedWindow("Display Window",WINDOW_AUTOSIZE);
    imshow("Display Window",img);
    waitKey(0);

    return a.exec();
}
