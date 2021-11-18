//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <string>

#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>



using namespace cv;
using namespace std;
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
//using std::cin;
//using std::cout;
//using std::endl;

const std::string IMG1_PATH = "/home/eugeniy/CV_imgs/img1.jpg";
const std::string IMG2_PATH = "/home/eugeniy/CV_imgs/img2.jpg";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Mat img;
//    img = imread(IMG_PATH, IMREAD_COLOR);
    namedWindow("Display Window",WINDOW_AUTOSIZE);
//    waitKey(0);
    double alpha = 0.5; double beta; //double input;
    Mat src1, src2, dst;
//    cout << " Simple Linear Blender " << endl;
//    cout << "-----------------------" << endl;
//    cout << "* Enter alpha [0.0-1.0]: ";
//    cin >> input;
    // We use the alpha provided by the user if it is between 0 and 1
//    if( input >= 0 && input <= 1 )
//      { alpha = input; }
    src1 = imread( IMG1_PATH );
    src2 = imread( IMG2_PATH );
    if( src1.empty() ) { cout << "Error loading src1" << endl; return EXIT_FAILURE; }
    if( src2.empty() ) { cout << "Error loading src2" << endl; return EXIT_FAILURE; }
    beta = ( 1.0 - alpha );
    addWeighted( src1, alpha, src2, beta, 0.0, dst);
    imshow("Display Window",dst);
//    imshow( "Linear Blend", dst );
    waitKey(0);
    return a.exec();

}
//int main( void )
//{
//   return 0;
//}
