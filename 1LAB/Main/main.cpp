#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const string IMG_PATH = "/home/eugeniy/git/CV_RTC/CV_IMGs/CV_1.jpg";

float getCorrectedCos (int x, int scale, int offset = 0) {
    float tmp = cos(float(x)/scale)*scale;
    return tmp + float(offset);
}

int main()
{
    Mat img;
    string path = IMG_PATH;
    img = imread(path);
    int sin_center = img.size().height/2;
    //Отрисовка синусоиды
    for (int t = 0; t <= img.size().width; t++) {
        circle(img, Point( t, getCorrectedCos(t, 100)+sin_center), 4.0, Scalar( 255, 255, 255 ), -1);
    }
    //Отрисовка тележки
    for (int t = 0; t <= img.size().width; t++) {
        Mat tmpImg = img.clone();
        rectangle(tmpImg,
                  Point( t-15, getCorrectedCos(t, 100, -10)+sin_center),
                  Point( t+15, getCorrectedCos(t, 100, 10)+sin_center),
                  Scalar( 0, 0, 255 ), -1);
        imshow("Display Window",tmpImg);
        //Сохранение изображения на половине пути тележки
        if (t == img.size().width/2)
            imwrite("result.jpg", tmpImg);
        if (waitKey(1) == 27)
            break;
    }
    waitKey(-1);
    return 0;
}
