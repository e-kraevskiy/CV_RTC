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

const string LENA_IMG = "/home/euheniy/git/CV_RTC/CV_IMGs/Lenna.png";

//Вычисление среднего взвешанного в окрестности точки
int getCoef(Mat& img, int kernel_size);
//Фильтр среднего
void myBlur(Mat& src, Mat &res, int kernel_size);
//Mat& myBlur(Mat& src, int rows, int cols, int kernel_size);
void checkAccuracy (Mat& my, Mat& cv, string method);

int main()
{
    //Счмтываем Елену одноканально
    Mat src = imread(LENA_IMG, IMREAD_GRAYSCALE);
    Mat my_blur = src.clone();
    Mat cv_blur;
    Mat diff = src.clone();

    blur(src, cv_blur, Size(5, 5));
    myBlur(src, my_blur, 5);
    checkAccuracy(my_blur, cv_blur, "Blur");
    diff = my_blur - cv_blur;

    imshow("Source image", src);
    imshow("My blul image", my_blur);
    imshow("Difference image", diff);
    waitKey(0);
    return 0;
}

int getCoef(Mat& img, int x, int y, int kernel_size) {
    int offset = kernel_size/2;
    int res = 0;
    for (int i = x - offset; i <= x + offset; i++) {
        for (int j = y - offset; j <= y + offset; j++) {
            res += (int)img.at<uchar>(i, j);
        }
    }
    res /= kernel_size*kernel_size;
    return res;
}

void myBlur(Mat& src, Mat &res, int kernel_size) {
    int offset = kernel_size/2;
    for (int i = offset; i <= src.rows - offset - 1; i++)
        for (int j = offset; j <= src.cols - offset - 1; j++) {
            res.at<uchar>(i, j) = getCoef(src, i, j, kernel_size);
        }
}

void checkAccuracy (Mat& my, Mat& cv, string method) {
    float count = 0;
    float diff = 0;
    for (int i = 0; i < my.rows; i++) {
        for (int j = 0; j < my.cols; j++) {
            if (my.at<char>(i, j) - cv.at<char>(i, j) > 1)
                diff++;
            count++;
        }
    }
    float res = ((count - diff) / count) * 100;
    cout << method << " accuracy is: " << fixed << setprecision(2) <<  res << "%" << endl;
}

