#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace cv;

const string LENA_IMG = "/home/eugeniy/git/CV_RTC/CV_IMGs/Lenna.png";

//Фильтр среднего
void myBlur(Mat& src, Mat &res, int kernel_size);

//Фльтр Лапласа
void myLaplace(Mat& src, Mat& dst);

//Повышение резкости с box фильром
void unsharpBlur(Mat& src, Mat& dst, int k);

//Повышение резкости с фильром Гаусса
void unsharpGauss(Mat& src, Mat& dst, int k);

//Повышение резкости с фильром Лапласа
void unsharpLaplace(Mat& src, Mat& dst, float k);

//Вычисление среднего взвешанного в окрестности точки
int getBoxCoef(Mat& img, int kernel_size);

//Cравнение разности изображений и вывода его в консоль
void checkAccuracy(Mat& my, Mat& cv, string method);

//Вычисление разницы (логарифмической, если log == true)
void diff(Mat& img1, Mat& img2, Mat& dst, bool log = false);

int main() {
    //Счмтываем Елену одноканально
    Mat src = imread(LENA_IMG, IMREAD_GRAYSCALE);
    imshow("Stock", src);
    //**********************BOX FILTER**********************
    Mat my_blur;
    Mat cv_blur;
    //Вызов собственной функции Blur и измерение времени ёё работы
    auto time_begin = std::chrono::steady_clock::now();
    myBlur(src, my_blur, 3);
    auto time_end = std::chrono::steady_clock::now();
    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin);
    cout << "my_blur function time is - " << time_diff.count() << " ms" << endl;

    //Вызов функции cv::blur и измерение времени ёё работы
    time_begin = std::chrono::steady_clock::now();
    blur(src, cv_blur, Size(3, 3));
    time_end = std::chrono::steady_clock::now();
    time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin);
    cout << "cv::blur function time is - " << time_diff.count() << " ms" << endl;

    imshow("My blul", my_blur);
    imshow("cv::blul", cv_blur);

    //***********************LAPLACE************************
    Mat my_laplace;
    Mat laplace;

    Laplacian(src, laplace, CV_8U);
    myLaplace(src, my_laplace);

    imshow("My Laplace", my_laplace);
//    imshow("Laplace", laplace);

    //***********************UNSHARP************************
    Mat unsharp_blur;
    Mat unsharp_gauss;
    Mat unsharp_laplace;

    unsharpBlur(src, unsharp_blur, 2);
    unsharpGauss(src, unsharp_gauss, 2);
    unsharpLaplace(src, unsharp_laplace, -0.1);

    imshow("Unsharp blur", unsharp_blur);
    imshow("Unsharp Gauss", unsharp_gauss);
    imshow("Unsharp Laplace", unsharp_laplace);

    //*********************DIFFERENCE***********************
    Mat blur_diff;
    checkAccuracy(my_blur, cv_blur, "Blur");
    diff(my_blur, cv_blur, blur_diff, true);
    imshow("Blur diff", blur_diff);

//    Mat laplace_diff;
//    diff(my_laplace, laplace, laplace_diff);
//    imshow("Laplace diff", laplace_diff);

    Mat unsharp_blur_gauss_diff;
    diff(unsharp_blur, unsharp_gauss, unsharp_blur_gauss_diff, true);
    imshow("Unsharp Blur Gauss log diff", unsharp_blur_gauss_diff);

    Mat unsharp_laplace_gauss_diff;
    diff(unsharp_laplace, unsharp_gauss, unsharp_laplace_gauss_diff);
    imshow("Unsharp Laplace Gauss diff", unsharp_laplace_gauss_diff);
    //******************************************************
    waitKey(0);
    return 0;
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

int getBoxCoef(Mat& img, int x, int y, int kernel_size) {
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

void myBlur(Mat& src, Mat &dst, int kernel_size) {
    dst = src.clone();
    int offset = kernel_size/2;
    for (int i = offset; i <= src.rows - offset - 1; i++)
        for (int j = offset; j <= src.cols - offset - 1; j++) {
            dst.at<uchar>(i, j) = getBoxCoef(src, i, j, kernel_size);
        }
}

void diff(Mat& img1, Mat& img2, Mat& dst, bool log) {
    dst = img1.clone();
    for (int i = 0; i < img1.rows; i++) {
        for (int j = 0; j < img1.cols; j++) {
            dst.at<uchar>(i, j) = abs(img1.at<uchar>(i, j) - img2.at<uchar>(i, j));
            if (log) {
                if (dst.at<uchar>(i, j) != 0) {
                    dst.at<uchar>(i, j) = (std::log(dst.at<uchar>(i, j)) / std::log(255)) * 255;
                } else
                    continue;
            }
        }
    }
}

void unsharpBlur(Mat& src, Mat& dst, int k) {
    dst = src.clone();
    Mat blur_img = src.clone();
    blur(src, blur_img, Size(3, 3));
    Mat gmask = src - blur_img;
    dst = src + k * gmask;
}

void unsharpGauss(Mat& src, Mat& dst, int k) {
    dst = src.clone();
    Mat blur_img = src.clone();
    GaussianBlur(src, blur_img, Size(3, 3), 0);
    Mat gmask = src - blur_img;
    dst = src + k * gmask;
}

void unsharpLaplace(Mat& src, Mat& dst, float k) {
    dst = src.clone();
    Mat blur_img = src.clone();
    Laplacian(src, blur_img, CV_8U);
    Mat gmask = src - blur_img;
    dst = src + k * gmask;
}

void myLaplace(Mat& src, Mat& dst) {
    dst = src.clone();
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 1; j < src.cols - 1; j++) {
            int sum = src.at<uchar>(i - 1, j)
                    + src.at<uchar>(i + 1, j)
                    + src.at<uchar>(i, j - 1)
                    + src.at<uchar>(i, j + 1)
                - 4 * src.at<uchar>(i, j);
            dst.at<uchar>(i, j) = cv::saturate_cast<uchar>(sum);
        }
    }
}
