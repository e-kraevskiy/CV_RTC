#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "mainwindow.h"

using namespace std;
using namespace cv;

const string IMG_PATH = "/home/eugeniy/CV_1.jpg";

float getCorrectedCos (int x, int scale) {
    float tmp = cos(float(x)/scale)*scale;
    return tmp;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    MainWindow w;
//    w.show();
    Mat img;
    string path = IMG_PATH;
    img = imread(path, IMREAD_COLOR);

//    line(img, (60, 20), (400, 200), (0, 0, 255), 5);
//    line(img, Point(60, 20), Point(400, 200), Scalar(0, 0, 255), 5);
//    circle(img, Point( 300, 300 ), 32.0, Scalar( 0, 0, 255 ), 20);
//    circle(img, Point( 200, 200 ), 32.0, Scalar( 0, 0, 255 ), -1, 8 );

    int sin_center = img.size().height/2;

    //Рисуем синусоиду
    for (int t = 0; t <= img.size().width; t++) {
//        circle(img, Point( t, (cos(((float)t)/100)*100)+100 ), 1.0, Scalar( 255, 255, 255 ), -1);
        circle(img, Point( t, getCorrectedCos(t, 100)+sin_center), 4.0, Scalar( 255, 255, 255 ), -1);
    }

    namedWindow("Display Window",WINDOW_AUTOSIZE);
    imshow("Display Window",img);

    //Сдесь должна отрисовываться тележка
    for (int t = 0; t <= img.size().width; t++) {
        circle(img, Point( t, getCorrectedCos(t, 100)+sin_center), 2.0, Scalar( 0, 0, 255 ), -1);
        imshow("Display Window",img);
        waitKey(1);
    }


    return app.exec();
}
