
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "pixOperator.hpp"
#include "TrackbarExample.hpp"
#include "UseMouse.hpp"
#include "cvAPITest.hpp"
#include <iostream>

using namespace std;



//int main() {
//    Mat srcImage = imread(R"(D:\code\LearnOpencv\input\1.jpg)");
//    imshow("origin", srcImage);
//
//    Mat dstImage;
//    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
//
//    double time0 = static_cast<double>(getTickCount());
//
//    pixOperator::iterColorReduce(srcImage, dstImage, 32);
//    time0 = ((double) getTickCount() - time0) / getTickFrequency();
//
//    imshow("output", dstImage);
//    waitKey(0);
//}

int main() {
    //改变控制台的前景色和背景色
    system("color 9F");
//    TrackbarExample trackbar;
//    trackbar.createTrackBar();
//    trackbar.createContrastAndBrightTrackBar();

    Mat srcImage = imread(R"(D:\code\Blizzard\output\preview\oriImage\oriImage_0.png)",IMREAD_UNCHANGED);
//
//    Mat dstImage;
//    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
//
//    double time0 = static_cast<double>(getTickCount());
//
//    pixOperator::forEachColorReduce(srcImage, dstImage, 32);
////    imshow("dstImage", dstImage);
//    time0 = ((double) getTickCount() - time0) / getTickFrequency();
//    waitKey(0);
//
//    return 0;
    cv::Mat mat1 = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat mat2 = (cv::Mat_<float>(3, 3) << 9, 8, 7, 6, 5, 4, 3, 2, 1);

    cv::Mat mask = (cv::Mat_<uchar>(3, 3) << 1, 0, 1, 0, 1, 0, 1, 0, 1);

    cv::Mat result;

    cv::add(mat1, mat2, result, mask);

    std::cout << "mat1:\n" << mat1 << std::endl;
    std::cout << "mat2:\n" << mat2 << std::endl;
    std::cout << "mask:\n" << mask << std::endl;
    std::cout << "result (mat1 + mat2 with mask):\n" << result << std::endl;

    cvAPITest test;
    test.subMatTest();


//	pixOperator::baseImageMat();
//
//    Mat alphaMat;
//	Mat mat(480, 640, CV_8UC4);
//	pixOperator::createAlphaMat(mat);
//
//	vector<int> compression_params;
//	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
//	compression_params.push_back(9);
////
//    imwrite("Alpha.png", mat,compression_params);
//    imshow("Alpha",mat);
    waitKey(0);

    return 0;
}


