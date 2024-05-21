//
// Created by Administrator on 2024/5/14/014.
//
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;


class pixOperator {
public:
    //【15】利用imwrite生成透明png图像
    static void createAlphaMat(Mat &mat);

    //【19】基础图像容器Mat类的使用
    static void baseImageMat();

    //【21】【22】【23】均执行颜色空间缩减函数
    //【21】用指针访问像素
    static void colorReduce(Mat &inputImage, Mat &outputImage, int div);

    //【22】用迭代器访问像素
    static void iterColorReduce(Mat &inputImage, Mat &outputImage, int div);

    //【23】用动态地址计算配合at访问像素 outputImage.at<Vec3b>(y, x)
    static void ptrColorReduce(Mat &inputImage, Mat &outputImage, int div);

    // learn 使用forEach访问像素 https://learnopencv.com/parallel-pixel-access-in-opencv-using-foreach/
    static void forEachColorReduce(Mat &inputImage, Mat &outputImage, int div);

    static void forEachLambdaColorReduce(Mat &inputImage, Mat &outputImage, int div);

    //【25】初级图像混合
    bool ROI_AddImage();

    //实现图像线性混合
    bool LinearBlending();

    //指定区域线性图像混合
    bool ROI_LinearBlending();

    //【26】多通道图像混合
    static bool MultiChannelBlending();

};


