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

const string IMG_PATH = "/home/euheniy/test_image.jpg";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mat img;
    string path = IMG_PATH;
    img = imread(path, IMREAD_COLOR);
    namedWindow("Display Window",WINDOW_AUTOSIZE);
    imshow("Display Window",img);
    waitKey(0);
    return a.exec();
}
