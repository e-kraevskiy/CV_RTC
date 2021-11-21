#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const string IMG1_PATH = "/home/eugeniy/git/CV_RTC/CV_IMGs/img1.jpg";
const string IMG2_PATH = "/home/eugeniy/git/CV_RTC/CV_IMGs/img2.jpg";

int main()
{
    double alpha = 0.5;
    double beta = 1.0 - alpha;
    Mat img1, img2, res;

    img1 = imread( IMG1_PATH );
    img2 = imread( IMG2_PATH );
    addWeighted( img1, alpha, img2, beta, 0.0, res);
    imshow("Display Window", res);
    waitKey(0);

    return 0;
}
