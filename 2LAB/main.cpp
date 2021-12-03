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

//Вычисление среднего взвешанного в окрестности точки
int getCoef(Mat& img, int kernel_size);
//Фильтр среднего
void myBlur(Mat& src, Mat &res, int rows, int cols, int kernel_size);
//Mat& myBlur(Mat& src, int rows, int cols, int kernel_size);

int main()
{
    //Счмтываем Елену одноканально
    Mat src = imread(LENA_IMG, IMREAD_GRAYSCALE);
    Mat m_blur = src.clone();

    int rows = src.rows;            // Получить количество строк;
    int cols = src.cols;            // Получить количество столбцов;
//    cout << "rows = " << rows << endl;
//    cout << "cols = " << cols << endl;

    myBlur(src, m_blur, rows, cols, 5);
    imshow("Source image", src);
    imshow("My blul image", m_blur);
    waitKey(0);
    return 0;
}

int getCoef(Mat& img, int x, int y, int kernel_size) {
    int offset = kernel_size/2;
    int res = 0;
    for (int i = x - offset; i <= x + offset; i++) {
        for (int j = y - offset; j <= y + offset; j++) {
            res += (int)img.at<uchar>(i, j);
//            cout << "img = " << img.at<uchar>(i, j) << endl;
        }
    }
    res /= kernel_size*kernel_size;
    return res;
}

void myBlur(Mat& src, Mat &res, int rows, int cols, int kernel_size) {
//    Mat res = src.clone();
    for (int i = 1; i <= rows - 2; i++)
        for (int j = 1; j <= cols - 2; j++) {
            int coef = getCoef(src, i, j, kernel_size);
            res.at<uchar>(i, j) = coef;
//            cout << "res = " << res.at<uchar>(i, j) << "src = " << src.at<uchar>(i, j) << endl;
        }
//    return res;
}

