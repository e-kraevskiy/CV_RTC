#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace std;
using namespace cv;

const string IMG_PATH = "/home/euheniy/CV_1.jpg";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mat img;
    img = imread(IMG_PATH, IMREAD_COLOR);
    namedWindow("Display Window",WINDOW_AUTOSIZE);
    imshow("Display Window",img);
    waitKey(0);
    return a.exec();
}
