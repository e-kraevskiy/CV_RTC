#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

const string FOURIER_IMG_PATH = "../4LAB/Joseph_Fourier.jpg";
const string LENNA_IMG_PATH = "../4LAB/Lenna.png";

void task_1(Mat img, vector<vector<int>> filter_kernel, string filter_name);
void task_2(Mat img);

// Фильтр низких частот
Mat getLowFrequence(const Mat& spectr);
// Фильтр высоких частот
Mat getHighFrequence(const Mat& spectr);
// Получить "красивый" образ
Mat getRotatedQuadrants(const Mat& src);
// Получить спектр
Mat getImgSpectr(const Mat& img);

Mat LENNA_IMG;
Mat FOURIER_IMG;
Mat convoluteDft(Mat img, vector<vector<int>> filter, Mat output,
                 int task_number, string filter_name);
Mat correlateDft(Mat img1, Mat img2);

Mat vecToMat(const vector<vector<int>> input);

Mat show_dft(Mat img, bool beauty_spectrum);

vector<vector<int>> Laplasse_kernel = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
vector<vector<int>> Box_kernel = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
vector<vector<int>> Sobel_x_kernel = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
vector<vector<int>> Sobel_y_kernel = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

int main() {
  LENNA_IMG = imread(LENNA_IMG_PATH, IMREAD_GRAYSCALE);
  FOURIER_IMG = imread(FOURIER_IMG_PATH, IMREAD_GRAYSCALE);
  imshow("Lenna image", LENNA_IMG);
  LENNA_IMG.convertTo(LENNA_IMG, CV_32FC1);
  FOURIER_IMG.convertTo(FOURIER_IMG, CV_32FC1);

  task_1(LENNA_IMG, Laplasse_kernel, "Laplasse");
  task_1(LENNA_IMG, Box_kernel, "Box");
  task_1(LENNA_IMG, Sobel_x_kernel, "Sobel x");
  task_1(LENNA_IMG, Sobel_y_kernel, "Sobel y");

  task_2(FOURIER_IMG);

  waitKey();
}

void task_1(Mat img, vector<vector<int>> filter_kernel, string filter_name) {
  Mat convolute;
  convolute = convoluteDft(img, filter_kernel, convolute, 1, filter_name);
  normalize(convolute, convolute, 0, 1, NORM_MINMAX);
  string show_name = "Task 1. " + filter_name;
  imshow(show_name, convolute);

  waitKey();
  destroyAllWindows();
}

void task_2(Mat img) {
  Mat spectr_og = getImgSpectr(img);
  imshow("Task 2. src DFT", show_dft(spectr_og, true));
  Mat low_freq, high_freq;
  high_freq = getHighFrequence(spectr_og);
  low_freq = getLowFrequence(spectr_og);

  dft(high_freq, high_freq, DFT_INVERSE | DFT_REAL_OUTPUT);
  dft(low_freq, low_freq, DFT_INVERSE | DFT_REAL_OUTPUT);

  high_freq(Rect(0, 0, img.cols, img.rows)).copyTo(high_freq);
  low_freq(Rect(0, 0, img.cols, img.rows)).copyTo(low_freq);

  normalize(high_freq, high_freq, 0, 1, NORM_MINMAX);
  imshow("Task 2. Hight freq", high_freq);
  normalize(low_freq, low_freq, 0, 1, NORM_MINMAX);
  imshow("Task 2. Low freq", low_freq);

  waitKey();
  destroyAllWindows();
}

Mat convoluteDft(Mat img, vector<vector<int>> filter, Mat output,
                 int task_number, string filter_name) {
  Size dft_optimum_size;
  Mat filter_mat;
  filter_mat = vecToMat(filter);
  filter_mat.convertTo(filter_mat, CV_32FC1);

  output.create(img.rows, img.cols, img.type());

  // Оптимальные размеры холста
  dft_optimum_size.width = getOptimalDFTSize(img.cols + filter_mat.cols - 1);
  dft_optimum_size.height = getOptimalDFTSize(img.rows + filter_mat.rows - 1);

  Mat canvas_image(dft_optimum_size, img.type(), Scalar::all(0));
  Mat canvas_filter(dft_optimum_size, filter_mat.type(), Scalar::all(0));
  // Области записи на холст
  Mat insert_region_image(canvas_image, Rect(0, 0, img.cols, img.rows));
  Mat insert_region_filter(canvas_filter,
                           Rect(0, 0, filter_mat.cols, filter_mat.rows));

  img.copyTo(insert_region_image);
  filter_mat.copyTo(insert_region_filter);

  // Преобразование
  dft(canvas_image, canvas_image, DFT_COMPLEX_OUTPUT);
  dft(canvas_filter, canvas_filter, DFT_COMPLEX_OUTPUT);

  string show_name =
      "Task " + std::to_string(task_number) + ". " + filter_name + " src DFT";
  imshow(show_name, show_dft(canvas_image, true));
  show_name = "Task " + std::to_string(task_number) + ". " + filter_name +
              " filter DFT";
  imshow(show_name, show_dft(canvas_filter, true));

  mulSpectrums(canvas_image, canvas_filter, canvas_image, 0, false);

  show_name = "Task " + std::to_string(task_number) + ". " + filter_name +
              " convolute DFT";
  imshow(show_name, show_dft(canvas_image, false));
  //Обратное ДПФ
  dft(canvas_image, canvas_image, DFT_INVERSE | DFT_REAL_OUTPUT);

  // Убираем лишнее из холста
  output = canvas_image(Rect(0, 0, output.cols, output.rows));
  return output;
}

Mat correlateDft(Mat img1, Mat img2) {
  Size dftSize;
  Mat Output;
  // Output = img1.clone();
  // Output.create(img1.rows, img1.cols, img1.type());

  //Получаем оптимальные размеры холста:
  dftSize.width = getOptimalDFTSize(img1.cols + img2.cols - 1);
  dftSize.height = getOptimalDFTSize(img1.rows + img2.rows - 1);

  //Масштабируем фильтр и исходное изображение до размеров холста
  Mat canvas_image1(dftSize, img1.type(), Scalar::all(0));
  Mat canvas_image2(dftSize, img2.type(), Scalar::all(0));

  Mat insert_region_image1(canvas_image1, Rect(0, 0, img1.cols, img1.rows));
  Mat insert_region_image2(canvas_image2, Rect(0, 0, img2.cols, img2.rows));

  img1.copyTo(insert_region_image1);
  img2.copyTo(insert_region_image2);

  //ДПФ
  dft(canvas_image1, canvas_image1, DFT_COMPLEX_OUTPUT);
  dft(canvas_image2, canvas_image2, DFT_COMPLEX_OUTPUT);

  //Вывести красиво образы Фурье исходного изображения и фильтра
  imshow("znak dft", show_dft(canvas_image1, true));
  imshow("symbol dft", show_dft(canvas_image2, true));

  mulSpectrums(canvas_image1, canvas_image2, canvas_image1, 0, true);

  imshow("convolution dft", show_dft(canvas_image1, true));

  //Обратное ДПФ - уже свернутого с фильтром изображения
  dft(canvas_image1, canvas_image1, DFT_INVERSE | DFT_REAL_OUTPUT);

  canvas_image1.copyTo(Output);
  return Output;
}

Mat getHighFrequence(const Mat& src) {
  Mat spectr = getRotatedQuadrants(src);
  Mat mask(Size(spectr.cols, spectr.rows), CV_8U, Scalar::all(255));
  Point center(spectr.cols / 2, spectr.rows / 2);

  circle(mask, center, spectr.cols / 4, Scalar::all(0), -1);
  Mat output;
  spectr.copyTo(output, mask);
  imshow("Task 2. High freq DFT", show_dft(output, false));
  return output;
}

Mat getLowFrequence(const Mat& src) {
  Mat spectr = getRotatedQuadrants(src);
  Mat mask(Size(spectr.cols, spectr.rows), CV_8U, Scalar::all(0));
  Point center(spectr.cols / 2, spectr.rows / 2);

  circle(mask, center, spectr.cols / 4, Scalar::all(255), -1);
  Mat output;
  spectr.copyTo(output, mask);
  imshow("Task 2. Low freq DFT", show_dft(output, false));
  return output;
}

Mat getImgSpectr(const Mat& img) {
  Size dft_size;
  dft_size.width = getOptimalDFTSize(img.cols);
  dft_size.height = getOptimalDFTSize(img.rows);
  Mat canvas_image(dft_size, img.type(), Scalar::all(0));
  Mat insert_region_image(canvas_image, Rect(0, 0, img.cols, img.rows));
  img.copyTo(insert_region_image);
  dft(canvas_image, canvas_image, DFT_COMPLEX_OUTPUT);
  return canvas_image;
}

Mat show_dft(Mat img, bool beauty_spectrum) {
  Mat channels[2];
  Mat magn;
  // Разбиваем многоканальное изображение
  split(img, channels);
  // Находим магнитуду
  magnitude(channels[0], channels[1], magn);
  // Переходим в log масштаб
  magn += Scalar::all(1);
  log(magn, magn);
  // Нормализуем
  normalize(magn, magn, 0, 1, NormTypes::NORM_MINMAX);
  if (beauty_spectrum)
    return getRotatedQuadrants(magn);
  else
    return magn;
}

Mat vecToMat(const vector<vector<int>> input) {
  Mat_<int> output(input.size(), input.at(0).size());
  for (int i = 0; i < output.rows; ++i) {
    for (int j = 0; j < output.cols; ++j) {
      output(i, j) = input.at(i).at(j);
    }
  }
  return output;
}

Mat getRotatedQuadrants(const Mat& src) {
  Mat img = src.clone();
  int cx = img.cols / 2;
  int cy = img.rows / 2;

  Mat q0(img, Rect(0, 0, cx, cy));
  Mat q1(img, Rect(cx, 0, cx, cy));
  Mat q2(img, Rect(0, cy, cx, cy));
  Mat q3(img, Rect(cx, cy, cx, cy));

  Mat temp;
  q0.copyTo(temp);
  q3.copyTo(q0);
  temp.copyTo(q3);

  q1.copyTo(temp);
  q2.copyTo(q1);
  temp.copyTo(q2);

  return img;
}
