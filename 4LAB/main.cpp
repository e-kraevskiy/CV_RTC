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
const string FOURIER_MOUTH_IMG_PATH = "../4LAB/Joseph_Fourier_mouth.jpg";

const string LENNA_IMG_PATH = "../4LAB/Lenna.png";
const string LENNA_EYE_IMG_PATH = "../4LAB/Lenna_eye.png";

const string NUMBER_1_IMG_PATH = "../4LAB/123.png";
const string NUMBER_SYMBOL_IMG_PATH = "../4LAB/2_symbol.png";
const string LETTER_SYMBOL_IMG_PATH = "../4LAB/m_symbol.png";

void task_2(Mat img, vector<vector<int>> filter_kernel, string filter_name);
void task_3(Mat img);
void task_4(Mat src_img, Mat template_img);

// Фильтр низких частот
Mat getLowFrequence(const Mat& spectr);
// Фильтр высоких частот
Mat getHighFrequence(const Mat& spectr);
// Получить "красивый" образ
Mat getRotatedQuadrants(const Mat& src);
// Получить спектр изображения
Mat getImgSpectr(const Mat& img);

Mat LENNA_IMG;
Mat LENNA_EYE_IMG;

Mat FOURIER_IMG;
Mat FOURIER_MOUTH_IMG;

Mat NUMBER_1_IMG;
Mat NUMBER_SYMBOL_IMG;
Mat LETTER_SYMBOL_IMG;

// Получить свертку ДФТ
Mat convoluteDft(Mat img, vector<vector<int>> filter, Mat output,
                 int task_number, string filter_name, bool show_image = true);
// Получить кореляцию ДФТ
Mat correlateDft(Mat src_image, Mat target_img);
// Перевод из вектора векторов в CV::Mat
Mat vecToMat(const vector<vector<int>> input);
// Отрисовка Фурье-образа
Mat getDftImage(Mat img, bool beauty_spectrum);

vector<vector<int>> Laplasse_kernel = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
vector<vector<int>> Box_kernel = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
vector<vector<int>> Sobel_x_kernel = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
vector<vector<int>> Sobel_y_kernel = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

int main() {
  // Чтение картинок
  LENNA_IMG = imread(LENNA_IMG_PATH, IMREAD_GRAYSCALE);
  LENNA_EYE_IMG = imread(LENNA_EYE_IMG_PATH, IMREAD_GRAYSCALE);

  FOURIER_IMG = imread(FOURIER_IMG_PATH, IMREAD_GRAYSCALE);
  FOURIER_MOUTH_IMG = imread(FOURIER_MOUTH_IMG_PATH, IMREAD_GRAYSCALE);

  NUMBER_1_IMG = imread(NUMBER_1_IMG_PATH, IMREAD_GRAYSCALE);
  NUMBER_SYMBOL_IMG = imread(NUMBER_SYMBOL_IMG_PATH, IMREAD_GRAYSCALE);
  LETTER_SYMBOL_IMG = imread(LETTER_SYMBOL_IMG_PATH, IMREAD_GRAYSCALE);

  //  imshow("Lenna image", LENNA_IMG);
  // Перевод изображений в другой формат
  LENNA_IMG.convertTo(LENNA_IMG, CV_32FC1);
  LENNA_EYE_IMG.convertTo(LENNA_EYE_IMG, CV_32FC1);

  FOURIER_IMG.convertTo(FOURIER_IMG, CV_32FC1);
  FOURIER_MOUTH_IMG.convertTo(FOURIER_MOUTH_IMG, CV_32FC1);

  NUMBER_1_IMG.convertTo(NUMBER_1_IMG, CV_32FC1);
  NUMBER_SYMBOL_IMG.convertTo(NUMBER_SYMBOL_IMG, CV_32FC1);
  LETTER_SYMBOL_IMG.convertTo(LETTER_SYMBOL_IMG, CV_32FC1);

  //  task_2(LENNA_IMG, Laplasse_kernel, "Laplasse");
  //  task_2(LENNA_IMG, Box_kernel, "Box");
  //  task_2(LENNA_IMG, Sobel_x_kernel, "Sobel x");
  //  task_2(LENNA_IMG, Sobel_y_kernel, "Sobel y");

  //  task_3(LENNA_IMG);

  task_4(NUMBER_1_IMG, NUMBER_SYMBOL_IMG);
  task_4(NUMBER_1_IMG, LETTER_SYMBOL_IMG);

  waitKey();
  //  while (true) {}
}

void task_2(Mat img, vector<vector<int>> filter_kernel, string filter_name) {
  Mat convolute;
  convolute = convoluteDft(img, filter_kernel, convolute, 2, filter_name);
  normalize(convolute, convolute, 0, 1, NORM_MINMAX);
  string show_name = "Task 2. " + filter_name;
  imshow(show_name, convolute);

  waitKey();
  destroyAllWindows();
}

void task_3(Mat img) {
  Mat spectr_og = getImgSpectr(img);
  imshow("Task 3. src DFT", getDftImage(spectr_og, true));
  Mat low_freq, high_freq;
  high_freq = getHighFrequence(spectr_og);
  low_freq = getLowFrequence(spectr_og);

  dft(high_freq, high_freq, DFT_INVERSE | DFT_REAL_OUTPUT);
  dft(low_freq, low_freq, DFT_INVERSE | DFT_REAL_OUTPUT);

  high_freq(Rect(0, 0, img.cols, img.rows)).copyTo(high_freq);
  low_freq(Rect(0, 0, img.cols, img.rows)).copyTo(low_freq);

  normalize(high_freq, high_freq, 0, 1, NORM_MINMAX);
  imshow("Task 3. Hight freq", high_freq);
  normalize(low_freq, low_freq, 0, 1, NORM_MINMAX);
  imshow("Task 3. Low freq", low_freq);

  waitKey();
  destroyAllWindows();
}

void task_4(Mat src_img, Mat target_img) {
  imshow("src_img", src_img);
  imshow("target_img", target_img);
  Mat result_mat;
  Mat Output = src_img.clone();
  Scalar src_scalar_mean = mean(src_img);
  Scalar target_scalar_mean = mean(target_img);

  src_img =
      convoluteDft(src_img, Laplasse_kernel, src_img, 4, "Laplasse", false);
  target_img = convoluteDft(target_img, Laplasse_kernel, target_img, 4,
                            "Laplasse", false);

  src_img.convertTo(src_img, CV_8U);
  target_img.convertTo(target_img, CV_8U);

  Mat src_mean(src_img.rows, src_img.cols, src_img.type(),
               Scalar::all(src_scalar_mean[0]));
  Mat template_mean(target_img.rows, target_img.cols, target_img.type(),
                    Scalar::all(target_scalar_mean[0]));
  src_img = src_img - src_mean;
  normalize(src_img, src_img, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  src_img.convertTo(src_img, CV_32FC1);

  target_img = target_img - template_mean;
  normalize(target_img, target_img, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  target_img.convertTo(target_img, CV_32FC1);

  result_mat = correlateDft(src_img, target_img);
  normalize(result_mat, result_mat, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
  imshow("Task 4. Correlation", result_mat);

  double minVal;
  double maxVal;
  Point minLoc, maxLoc, matchLoc;
  minMaxLoc(result_mat, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
  matchLoc = maxLoc;
  threshold(result_mat, result_mat, maxVal - 0.01, 255, CV_8U);
  imshow("Task 4. Threshold", result_mat);
  rectangle(
      Output, matchLoc,
      cv::Point(matchLoc.x + target_img.cols, matchLoc.y + target_img.rows),
      CV_RGB(255, 0, 0), 2);

  imshow("Task 4. Result", Output);
  waitKey();
  //  destroyAllWindows();
}

Mat convoluteDft(Mat img, vector<vector<int>> filter, Mat output,
                 int task_number, string filter_name, bool show_image) {
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
  string show_name = "";
  if (show_image) {
    show_name =
        "Task " + std::to_string(task_number) + ". " + filter_name + " src DFT";
    imshow(show_name, getDftImage(canvas_image, true));
    show_name = "Task " + std::to_string(task_number) + ". " + filter_name +
                " filter DFT";
    imshow(show_name, getDftImage(canvas_filter, true));
  }

  mulSpectrums(canvas_image, canvas_filter, canvas_image, 0, false);

  if (show_image) {
    show_name = "Task " + std::to_string(task_number) + ". " + filter_name +
                " convolute DFT";
    imshow(show_name, getDftImage(canvas_image, false));
  }
  //Обратное ДПФ
  dft(canvas_image, canvas_image, DFT_INVERSE | DFT_REAL_OUTPUT);

  // Убираем лишнее из холста
  output = canvas_image(Rect(0, 0, output.cols, output.rows));
  return output;
}

Mat correlateDft(Mat src_image, Mat target_img) {
  Size dftSize;
  Mat Output;

  //Получаем оптимальные размеры холста:
  dftSize.width = getOptimalDFTSize(src_image.cols + target_img.cols - 1);
  dftSize.height = getOptimalDFTSize(src_image.rows + target_img.rows - 1);

  //Масштабируем фильтр и исходное изображение до размеров холста
  Mat canvas_image1(dftSize, src_image.type(), Scalar::all(0));
  Mat canvas_image2(dftSize, target_img.type(), Scalar::all(0));

  Mat insert_region_image1(canvas_image1,
                           Rect(0, 0, src_image.cols, src_image.rows));
  Mat insert_region_image2(canvas_image2,
                           Rect(0, 0, target_img.cols, target_img.rows));

  src_image.copyTo(insert_region_image1);
  target_img.copyTo(insert_region_image2);

  dft(canvas_image1, canvas_image1, DFT_COMPLEX_OUTPUT);
  dft(canvas_image2, canvas_image2, DFT_COMPLEX_OUTPUT);

  imshow("Task 4. Src DFT", getDftImage(canvas_image1, true));
  imshow("Task 4. Target DFT", getDftImage(canvas_image2, true));

  mulSpectrums(canvas_image1, canvas_image2, canvas_image1, 0, true);

  imshow("Task 4. Convolution DFT", getDftImage(canvas_image1, true));

  //Обратное ДПФ
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
  imshow("Task 3. High freq DFT", getDftImage(output, false));
  return output;
}

Mat getLowFrequence(const Mat& src) {
  Mat spectr = getRotatedQuadrants(src);
  Mat mask(Size(spectr.cols, spectr.rows), CV_8U, Scalar::all(0));
  Point center(spectr.cols / 2, spectr.rows / 2);

  circle(mask, center, spectr.cols / 4, Scalar::all(255), -1);
  Mat output;
  spectr.copyTo(output, mask);
  imshow("Task 3. Low freq DFT", getDftImage(output, false));
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

Mat getDftImage(Mat img, bool beauty_spectrum) {
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
