
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "pixOperator.hpp"
#include "TrackbarExample.hpp"
#include "UseMouse.hpp"
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

int main()
{
    //改变控制台的前景色和背景色
	system("color 9F");
//    TrackbarExample trackbar;
//    trackbar.createTrackBar();
//    trackbar.createContrastAndBrightTrackBar();

//    Mat srcImage = imread(R"(D:\code\LearnOpencv\input\6000-4000.jpg)");
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
    std::cout << "Original matrix element at (i1 + h - 1, i0 + w - 1): " << m.at<float>(j0 + h - 1, i0 + w - 1) << std::endl;
    // 修改子矩阵并验证原矩阵变化

    for (int i = 0; i < subMat.rows; i++) {
        for (int j = 0; j < subMat.cols; j++) {
            subMat.at<float>(i, j) = 2;  //蓝色通道
        }
    }
//    imshow("Alpha",m);

    std::cout << "Modified subMat first element: " << subMat.at<float>(0, 0) << std::endl;
    std::cout << "Original matrix element at (i1, i0) after modification: " << m.at<float>(j0, i0) << std::endl;



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


