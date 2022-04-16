#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/highgui.hpp>

#include "task_1.h"
//#include "task_2.h"
#include "task_3.h"
#include "task_4.h"

using namespace std;

void createBoard() {
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(5, 7, 0.04f, 0.02f, dictionary);
    cv::Mat boardImage;
    board->draw(cv::Size(1500, 2100), boardImage, 10, 1);
    cv::imwrite("BoardImage.jpg", boardImage);
}

int main()
{
    createBoard();

    cout << "Hello World!" << endl;
    return 0;
}
