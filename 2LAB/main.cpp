#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
//https://russianblogs.com/article/5156367103/
using namespace std;
using namespace cv;

const string LENA_IMG = "/home/eugeniy/git/CV_RTC/CV_IMGs/Lenna.png";

int main()
{
    Mat img;
    string path = LENA_IMG;
    img = imread(path, IMREAD_COLOR);

    int rows = img.rows;            // Получить количество строк;
    int cols = img.cols;            // Получить количество столбцов;
    int channels = img.channels();  // Получить количество каналов;
    cout << "rows = " << rows << endl;
    cout << "cols = " << cols << endl;
    cout << "channels =" << channels << endl;

    Mat_<Vec3b>::iterator it = img.begin<Vec3b>();
    while (it != img.end<Vec3b>())
    {
        (*it)[0] = 0;// Синий канал
        (*it)[1] = 0;// Зеленый канал
//        (*it)[2] = 0;// Красный канал
        it++;
    }

    imshow("Display Window",img);
    waitKey(0);
    return 0;
}
