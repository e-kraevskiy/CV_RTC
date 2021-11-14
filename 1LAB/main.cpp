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

float getCorrectedCos (int x, int scale, int offset = 0) {
    float tmp = cos(float(x)/scale)*scale;
    return tmp + float(offset);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    MainWindow w;
//    w.show();
    Mat img;
    string path = IMG_PATH;
    img = imread(path, IMREAD_COLOR);
    int sin_center = img.size().height/2;

    //Рисуем синусоиду
    for (int t = 0; t <= img.size().width; t++) {
        circle(img, Point( t, getCorrectedCos(t, 100)+sin_center), 4.0, Scalar( 255, 255, 255 ), -1);
    }

    namedWindow("Display Window",WINDOW_AUTOSIZE);
    imshow("Display Window",img);

    //Сдесь должна отрисовываться тележка
    for (int t = 0; t <= img.size().width; t++) {
        Mat tmpImg = img.clone();
//        rectangle(,)
        rectangle(tmpImg, Point( t-15, getCorrectedCos(t, 100, -10)+sin_center),
                  Point( t+15, getCorrectedCos(t, 100, 10)+sin_center), Scalar( 0, 0, 255 ), -1);
//        circle(tmpImg, Point( t, getCorrectedCos(t, 100)+sin_center), 10.0, Scalar( 0, 0, 255 ), -1);
        imshow("Display Window",tmpImg);

        if (waitKey(1) == 27)
            break;

    }

    return app.exec();
}
