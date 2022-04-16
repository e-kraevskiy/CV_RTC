//#include <iostream>
////#include <opencv2/aruco.hpp>
////#include <opencv2/aruco/charuco.hpp>
//#include <opencv2/calib3d.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <vector>

////#include "aruco_samples_utility.hpp"

//using namespace std;
//using namespace cv;

//inline static bool saveCameraParams(const std::string &filename,
//                                    cv::Size imageSize, float aspectRatio,
//                                    int flags, const cv::Mat &cameraMatrix,
//                                    const cv::Mat &distCoeffs,
//                                    double totalAvgErr) {
//  cv::FileStorage fs(filename, cv::FileStorage::WRITE);
//  if (!fs.isOpened()) return false;

//  time_t tt;
//  time(&tt);
//  struct tm *t2 = localtime(&tt);
//  char buf[1024];
//  strftime(buf, sizeof(buf) - 1, "%c", t2);

//  fs << "calibration_time" << buf;
//  fs << "image_width" << imageSize.width;
//  fs << "image_height" << imageSize.height;

//  if (flags & cv::CALIB_FIX_ASPECT_RATIO) fs << "aspectRatio" << aspectRatio;

//  if (flags != 0) {
//    sprintf(buf, "flags: %s%s%s%s",
//            flags & cv::CALIB_USE_INTRINSIC_GUESS ? "+use_intrinsic_guess" : "",
//            flags & cv::CALIB_FIX_ASPECT_RATIO ? "+fix_aspectRatio" : "",
//            flags & cv::CALIB_FIX_PRINCIPAL_POINT ? "+fix_principal_point" : "",
//            flags & cv::CALIB_ZERO_TANGENT_DIST ? "+zero_tangent_dist" : "");
//  }
//  fs << "flags" << flags;
//  fs << "camera_matrix" << cameraMatrix;
//  fs << "distortion_coefficients" << distCoeffs;
//  fs << "avg_reprojection_error" << totalAvgErr;
//  return true;
//}

//namespace {
//const char *about =
//    "Calibration using a ChArUco board\n"
//    "  To capture a frame for calibration, press 'c',\n"
//    "  If input comes from video, press any key for next frame\n"
//    "  To finish capturing, press 'ESC' key and calibration starts.\n";
//const char *keys =
//    "{w        |       | Number of squares in X direction }"
//    "{h        |       | Number of squares in Y direction }"
//    "{sl       |       | Square side length (in meters) }"
//    "{ml       |       | Marker side length (in meters) }"
//    "{d        |       | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
//    "DICT_4X4_250=2,"
//    "DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, DICT_5X5_250=6, "
//    "DICT_5X5_1000=7, "
//    "DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, DICT_6X6_1000=11, "
//    "DICT_7X7_50=12,"
//    "DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = "
//    "16}"
//    "{cd       |       | Input file with custom dictionary }"
//    "{@outfile |<none> | Output file with calibrated camera parameters }"
//    "{v        |       | Input from video file, if ommited, input comes from "
//    "camera }"
//    "{ci       | 0     | Camera id if input doesnt come from video (-v) }"
//    "{dp       |       | File of marker detector parameters }"
//    "{rs       | false | Apply refind strategy }"
//    "{zt       | false | Assume zero tangential distortion }"
//    "{a        |       | Fix aspect ratio (fx/fy) to this value }"
//    "{pc       | false | Fix the principal point at the center }"
//    "{sc       | false | Show detected chessboard corners after calibration }";
//}  // namespace

//int main(int argc, char *argv[]) {
//  CommandLineParser parser(argc, argv, keys);
//  parser.about(about);

//  if (argc < 7) {
//    parser.printMessage();
//    return 0;
//  }

//  int squaresX = 5;                        // parser.get<int>("w");
//  int squaresY = 7;                        // parser.get<int>("h");
//  float squareLength = 0.04;               // parser.get<float>("sl");
//  float markerLength = 0.02;               // parser.get<float>("ml");
//  string outputFile = "camera_calib.txt";  // parser.get<string>(0);

//  //  bool showChessboardCorners = parser.get<bool>("sc");

//  int calibrationFlags = 0;
//  float aspectRatio = 1;


//  //  if (parser.get<bool>("zt")) calibrationFlags |= CALIB_ZERO_TANGENT_DIST;
//  //  if (parser.get<bool>("pc")) calibrationFlags |= CALIB_FIX_PRINCIPAL_POINT;

//  Ptr<aruco::DetectorParameters> detectorParams =
//      aruco::DetectorParameters::create();
//  if (parser.has("dp")) {
//    FileStorage fs(parser.get<string>("dp"), FileStorage::READ);
//    bool readOk = aruco::DetectorParameters::readDetectorParameters(
//        fs.root(), detectorParams);
//    if (!readOk) {
//      cerr << "Invalid detector parameters file" << endl;
//      return 0;
//    }
//  }

//  //  bool refindStrategy = parser.get<bool>("rs");
//  //  int camId = parser.get<int>("ci");
//  String video;

//  video = "path_aruco/tutorials/aruco_calibration/images/img_%02d.jpg";

//  VideoCapture inputVideo;
//  int waitTime;
//  if (!video.empty()) {
//    inputVideo.open(video);
//    waitTime = 0;
//  }

//  Ptr<aruco::Dictionary> dictionary;
//  if (parser.has("d")) {
//    int dictionaryId = parser.get<int>("d");
//    dictionary = aruco::getPredefinedDictionary(
//        aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
//  } else if (parser.has("cd")) {
//    FileStorage fs(parser.get<std::string>("cd"), FileStorage::READ);
//    bool readOk = aruco::Dictionary::readDictionary(fs.root(), dictionary);
//    if (!readOk) {
//      cerr << "Invalid dictionary file" << endl;
//      return 0;
//    }
//  } else {
//    cerr << "Dictionary not specified" << endl;
//    return 0;
//  }

//  // create charuco board object
//  Ptr<aruco::CharucoBoard> charucoboard = aruco::CharucoBoard::create(
//      squaresX, squaresY, squareLength, markerLength, dictionary);
//  Ptr<aruco::Board> board = charucoboard.staticCast<aruco::Board>();

//  // collect data from each frame
//  vector<vector<vector<Point2f> > > allCorners;
//  vector<vector<int> > allIds;
//  vector<Mat> allImgs;
//  Size imgSize;

//  while (inputVideo.grab()) {
//    Mat image, imageCopy;
//    inputVideo.retrieve(image);

//    vector<int> ids;
//    vector<vector<Point2f> > corners, rejected;

//    // detect markers
//    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams,
//                         rejected);

//    // refind strategy to detect more markers
//    if (refindStrategy)
//      aruco::refineDetectedMarkers(image, board, corners, ids, rejected);

//    // interpolate charuco corners
//    Mat currentCharucoCorners, currentCharucoIds;
//    if (ids.size() > 0)
//      aruco::interpolateCornersCharuco(corners, ids, image, charucoboard,
//                                       currentCharucoCorners,
//                                       currentCharucoIds);

//    // draw results
//    image.copyTo(imageCopy);
//    if (ids.size() > 0) aruco::drawDetectedMarkers(imageCopy, corners);

//    if (currentCharucoCorners.total() > 0)
//      aruco::drawDetectedCornersCharuco(imageCopy, currentCharucoCorners,
//                                        currentCharucoIds);

//    putText(imageCopy,
//            "Press 'c' to add current frame. 'ESC' to finish and calibrate",
//            Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);

//    imshow("out", imageCopy);
//    char key = (char)waitKey(waitTime);
//    if (key == 27) break;
//    if (key == 'c' && ids.size() > 0) {
//      cout << "Frame captured" << endl;
//      allCorners.push_back(corners);
//      allIds.push_back(ids);
//      allImgs.push_back(image);
//      imgSize = image.size();
//    }
//  }

//  if (allIds.size() < 1) {
//    cerr << "Not enough captures for calibration" << endl;
//    return 0;
//  }

//  Mat cameraMatrix, distCoeffs;
//  vector<Mat> rvecs, tvecs;
//  double repError;

//  if (calibrationFlags & CALIB_FIX_ASPECT_RATIO) {
//    cameraMatrix = Mat::eye(3, 3, CV_64F);
//    cameraMatrix.at<double>(0, 0) = aspectRatio;
//  }

//  // prepare data for calibration
//  vector<vector<Point2f> > allCornersConcatenated;
//  vector<int> allIdsConcatenated;
//  vector<int> markerCounterPerFrame;
//  markerCounterPerFrame.reserve(allCorners.size());
//  for (unsigned int i = 0; i < allCorners.size(); i++) {
//    markerCounterPerFrame.push_back((int)allCorners[i].size());
//    for (unsigned int j = 0; j < allCorners[i].size(); j++) {
//      allCornersConcatenated.push_back(allCorners[i][j]);
//      allIdsConcatenated.push_back(allIds[i][j]);
//    }
//  }

//  // calibrate camera using aruco markers
//  double arucoRepErr;
//  arucoRepErr = aruco::calibrateCameraAruco(
//      allCornersConcatenated, allIdsConcatenated, markerCounterPerFrame, board,
//      imgSize, cameraMatrix, distCoeffs, noArray(), noArray(),
//      calibrationFlags);

//  // prepare data for charuco calibration
//  int nFrames = (int)allCorners.size();
//  vector<Mat> allCharucoCorners;
//  vector<Mat> allCharucoIds;
//  vector<Mat> filteredImages;
//  allCharucoCorners.reserve(nFrames);
//  allCharucoIds.reserve(nFrames);

//  for (int i = 0; i < nFrames; i++) {
//    // interpolate using camera parameters
//    Mat currentCharucoCorners, currentCharucoIds;
//    aruco::interpolateCornersCharuco(
//        allCorners[i], allIds[i], allImgs[i], charucoboard,
//        currentCharucoCorners, currentCharucoIds, cameraMatrix, distCoeffs);

//    allCharucoCorners.push_back(currentCharucoCorners);
//    allCharucoIds.push_back(currentCharucoIds);
//    filteredImages.push_back(allImgs[i]);
//  }

//  if (allCharucoCorners.size() < 4) {
//    cerr << "Not enough corners for calibration" << endl;
//    return 0;
//  }

//  // calibrate camera using charuco
//  repError = aruco::calibrateCameraCharuco(
//      allCharucoCorners, allCharucoIds, charucoboard, imgSize, cameraMatrix,
//      distCoeffs, rvecs, tvecs, calibrationFlags);

//  bool saveOk =
//      saveCameraParams(outputFile, imgSize, aspectRatio, calibrationFlags,
//                       cameraMatrix, distCoeffs, repError);
//  if (!saveOk) {
//    cerr << "Cannot save output file" << endl;
//    return 0;
//  }

//  cout << "Rep Error: " << repError << endl;
//  cout << "Rep Error Aruco: " << arucoRepErr << endl;
//  cout << "Calibration saved to " << outputFile << endl;

//  // show interpolated charuco corners for debugging
//  if (showChessboardCorners) {
//    for (unsigned int frame = 0; frame < filteredImages.size(); frame++) {
//      Mat imageCopy = filteredImages[frame].clone();
//      if (allIds[frame].size() > 0) {
//        if (allCharucoCorners[frame].total() > 0) {
//          aruco::drawDetectedCornersCharuco(imageCopy, allCharucoCorners[frame],
//                                            allCharucoIds[frame]);
//        }
//      }

//      imshow("out", imageCopy);
//      char key = (char)waitKey(0);
//      if (key == 27) break;
//    }
//  }

//  return 0;
//}
