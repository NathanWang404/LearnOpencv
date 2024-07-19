//
// Created by Administrator on 2024/7/4/004.
//

#include "cvAPITest.hpp"

void cvAPITest::thresholdProcess() {
    // ref: https://learnopencv.com/otsu-thresholding-with-opencv/
    // ref: https://learnopencv.com/opencv-threshold-python-cpp/
    // ref: https://docs.opencv.org/4.5.3/d7/d4d/tutorial_py_thresholding.html
    cv::Mat srcImage = cv::imread(R"(D:\code\LearnOpencv\input\processed_img-1-768x514.jpg)",cv::IMREAD_GRAYSCALE);
    cv::Mat dst0,dst127,dstMax128,dst127Inv,dstTrunc,dstZero,dstZeroInv,dstMask,dstOtsu,dstTriangle;
    cv::threshold(srcImage,dst0,0.0,255,cv::THRESH_BINARY);
    cv::threshold(srcImage,dst127,127,255,cv::THRESH_BINARY);
    cv::threshold(srcImage,dst127Inv,127,255,cv::THRESH_BINARY_INV);
    cv::threshold(srcImage,dstMax128,0.0,128,cv::THRESH_BINARY);

    cv::threshold(srcImage,dstTrunc,127,255,cv::THRESH_TRUNC);
    cv::threshold(srcImage,dstZero,127,255,cv::THRESH_TOZERO);
    cv::threshold(srcImage,dstZeroInv,127,255,cv::THRESH_TOZERO_INV);
    cv::threshold(srcImage,dstMask,127,255,cv::THRESH_MASK);
    cv::threshold(srcImage,dstOtsu,132,255,cv::THRESH_OTSU);
    cv::threshold(srcImage,dstTriangle,127,255,cv::THRESH_TRIANGLE);
    std::cout << "" << std::endl;

}

void cvAPITest::copyToTest() {
    cv::Mat src = (cv::Mat_<uchar>(3, 3) << 1, 2, 3,
            4, 5, 6,
            7, 8, 9);
    //cv::Mat src2 = (cv::Mat_<uchar>(3, 3) << 11, 22, 33, 44, 55, 66, 77, 88, 99);

    cv::Mat dst;

    cv::Mat mask = (cv::Mat_<uchar>(3, 3) << 1, 0, 1, 0, 1, 0, 1, 0, 1);

    cv::copyTo(src, dst, mask);
    //src.copyTo(dst, mask);
    //src2.copyTo(dst, mask);

    std::cout << "Source Matrix:\n" << src << std::endl;
    std::cout << "Mask Matrix:\n" << mask << std::endl;
    std::cout << "Destination Matrix after copyTo:\n" << dst << std::endl;
}

void cvAPITest::subMatTest() {
    cv::Mat m = cv::Mat::zeros(300, 300, CV_32F);
    //    std::cout << m << std::endl;
    // 定义子矩阵的左上角坐标和宽高
    int i0 = 100; // 左上角的 x 坐标
    int j0 = 50;  // 左上角的 y 坐标
    int w = 100;  // 子矩阵的宽度
    int h = 50;  // 子矩阵的高度

    cv::Rect roi(i0, j0, w, h);

    cv::Mat subMat = m(roi);

    // 输出子矩阵的大小
    std::cout << "SubMat size: " << subMat.size() << std::endl;

    // 输出子矩阵的前几个元素以验证
    std::cout << "SubMat first element: " << subMat.at<float>(0, 0) << std::endl;

    // 验证子矩阵的范围
    std::cout << "Original matrix element at (i1, i0): " << m.at<float>(j0, i0) << std::endl;
    std::cout << "Original matrix element at (i1 + h - 1, i0 + w - 1): " << m.at<float>(j0 + h - 1, i0 + w - 1)
    << std::endl;
    // 修改子矩阵并验证原矩阵变化

    for (int i = 0; i < subMat.rows; i++) {
        for (int j = 0; j < subMat.cols; j++) {
            subMat.at<float>(i, j) = 2;  //蓝色通道
        }
    }
    //    imshow("Alpha",m);

    std::cout << "Modified subMat first element: " << subMat.at<float>(0, 0) << std::endl;
    std::cout << "Original matrix element at (i1, i0) after modification: " << m.at<float>(j0, i0) << std::endl;
}
