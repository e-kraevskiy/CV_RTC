#include "cube.h"


int startDetecting() {
    int dictionaryId = DICTINARY_ID;
    float marker_length_m = MARKER_SIZE;
    int wait_time = 10;

    cv::VideoCapture input_video;
    input_video.open(0);

    if (!input_video.isOpened()) {
        std::cerr << "failed to open video input " << std::endl;
        return 1;
    }


    cv::Mat image, image_copy;
    cv::Mat camera_matrix, dist_coeffs;
    std::ostringstream vector_to_marker;

    cv::Ptr<cv::aruco::Dictionary> dictionary =
        cv::aruco::getPredefinedDictionary(
        cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

    cv::FileStorage fs(CAMERA_CALIB_PARAM, cv::FileStorage::READ);

    fs["camera_matrix"] >> camera_matrix;
    fs["distortion_coefficients"] >> dist_coeffs;

    std::cout << "camera_matrix\n"
              << camera_matrix << std::endl;
    std::cout << "\ndist coeffs\n"
              << dist_coeffs << std::endl;

    int frame_width = input_video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = input_video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = 30;
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter video(
        "output.avi", fourcc, fps, cv::Size(frame_width, frame_height), true);

    while (input_video.grab()) {

        input_video.retrieve(image);
        image.copyTo(image_copy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // if at least one marker detected
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(image_copy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(
                corners, marker_length_m, camera_matrix, dist_coeffs,
                rvecs, tvecs
            );

            // draw axis for each marker
            for (int i = 0; i < ids.size(); i++) {
                drawCube(
                    image_copy, camera_matrix, dist_coeffs, rvecs[i], tvecs[i],
                    marker_length_m
                );
            }
        }

        video.write(image_copy);
        cv::imshow("Pose estimation", image_copy);
        char key = (char)cv::waitKey(wait_time);
        if (key == 27)
            break;
    }

    input_video.release();

    return 0;
}

void drawCube(
    cv::InputOutputArray image, cv::InputArray cameraMatrix,
    cv::InputArray distCoeffs, cv::InputArray rvec, cv::InputArray tvec,
    float edge_size) {


    // project cube points
    std::vector<cv::Point3f> axisPoints;
    // точки основания
    axisPoints.push_back(cv::Point3f(edge_size, edge_size, 0));
    axisPoints.push_back(cv::Point3f(edge_size, 0, 0));
    axisPoints.push_back(cv::Point3f(0, 0, 0));
    axisPoints.push_back(cv::Point3f(0, edge_size, 0));
    // верхние течки
    axisPoints.push_back(cv::Point3f(edge_size, edge_size, -edge_size));
    axisPoints.push_back(cv::Point3f(edge_size, 0, -edge_size));
    axisPoints.push_back(cv::Point3f(0, 0, -edge_size));
    axisPoints.push_back(cv::Point3f(0, edge_size, -edge_size));

    std::vector<cv::Point2f> imagePoints;
    projectPoints(
        axisPoints, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

    // отрисовка линий
    // оси координат
    cv::line(image, imagePoints[1], imagePoints[2], cv::Scalar(0, 255, 0), 3);
    cv::line(image, imagePoints[2], imagePoints[3], cv::Scalar(0, 0, 255), 3);
    cv::line(image, imagePoints[2], imagePoints[6], cv::Scalar(255, 0, 0), 3);
    // остальные линии
    cv::line(image, imagePoints[0], imagePoints[1], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[0], imagePoints[3], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[0], imagePoints[4], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[1], imagePoints[5], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[3], imagePoints[7], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[4], imagePoints[5], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[4], imagePoints[7], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[5], imagePoints[6], CUBE_COLOUR, 3);
    cv::line(image, imagePoints[6], imagePoints[7], CUBE_COLOUR, 3);
}
