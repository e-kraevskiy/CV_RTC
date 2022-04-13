//#include "task_1.h"


//static bool readDetectorParameters(string filename, aruco::DetectorParameters &params) {
//    FileStorage fs(filename, FileStorage::READ);
//    if(!fs.isOpened())
//        return false;
//    fs["adaptiveThreshWinSizeMin"] >> params.adaptiveThreshWinSizeMin;
//    fs["adaptiveThreshWinSizeMax"] >> params.adaptiveThreshWinSizeMax;
//    fs["adaptiveThreshWinSizeStep"] >> params.adaptiveThreshWinSizeStep;
//    fs["adaptiveThreshConstant"] >> params.adaptiveThreshConstant;
//    fs["minMarkerPerimeterRate"] >> params.minMarkerPerimeterRate;
//    fs["maxMarkerPerimeterRate"] >> params.maxMarkerPerimeterRate;
//    fs["polygonalApproxAccuracyRate"] >> params.polygonalApproxAccuracyRate;
//    fs["minCornerDistanceRate"] >> params.minCornerDistanceRate;
//    fs["minDistanceToBorder"] >> params.minDistanceToBorder;
//    fs["minMarkerDistanceRate"] >> params.minMarkerDistanceRate;
//    fs["doCornerRefinement"] >> params.doCornerRefinement;
//    fs["cornerRefinementWinSize"] >> params.cornerRefinementWinSize;
//    fs["cornerRefinementMaxIterations"] >>
//                                           params.cornerRefinementMaxIterations;
//    fs["cornerRefinementMinAccuracy"] >> params.cornerRefinementMinAccuracy;
//    fs["markerBorderBits"] >> params.markerBorderBits;
//    fs["perspectiveRemovePixelPerCell"] >>
//                                           params.perspectiveRemovePixelPerCell;
//    fs["perspectiveRemoveIgnoredMarginPerCell"] >>
//                                                   params.perspectiveRemoveIgnoredMarginPerCell;
//    fs["maxErroneousBitsInBorderRate"] >> params.maxErroneousBitsInBorderRate;
//    fs["minOtsuStdDev"] >> params.minOtsuStdDev;
//    fs["errorCorrectionRate"] >> params.errorCorrectionRate;
//    return true;
//}

//void calivbrateMyCamera() {
//    aruco::Dictionary dictionary =
//            aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
//    // dictionaryId - номер словаря
//    Mat camMatrix, distCoeffs;
//    aruco::DetectorParameters detectorParams;
//    vector< int > ids;
//    vector< vector< Point2f > > corners, rejected;
//    vector< Vec3d > rvecs, tvecs;
//    // detect markers and estimate pose
//    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams,
//                         rejected);
//    if(ids.size() > 0)
//    aruco::estimatePoseSingleMarkers(corners, markerLength, camMatrix,
//                                     distCoeffs, rvecs, tvecs);

//}
