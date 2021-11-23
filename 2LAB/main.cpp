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

const string LENA_IMG = "/home/eugeniy/git/CV_RTC/CV_IMGs/Lenna.png";

int main()
{
    Mat img;
    string path = LENA_IMG;
    img = imread(path, IMREAD_COLOR);
    imshow("Display Window",img);
    waitKey(0);
    return 0;
}
