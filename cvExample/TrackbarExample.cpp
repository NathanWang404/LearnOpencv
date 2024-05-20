//
// Created by Administrator on 2024/5/16/016.
//

#include "TrackbarExample.hpp"

const int g_nMaxAlphaValue = 100;//Alpha值的最大值
double g_dAlphaValue;
double g_dBetaValue;
int g_nContrastValue; //对比度值
int g_nBrightValue;  //亮度值


void TrackbarExample::updateImage(int SliderValue) {
    std::cout << " SliderValue " << SliderValue << std::endl;
    g_dAlphaValue = (double) SliderValue / g_nMaxAlphaValue;
    g_dBetaValue = (1.0 - g_dAlphaValue);

    cv::addWeighted(mSrcImage1,g_dAlphaValue,mSrcImage2,g_dBetaValue,0.0,mDstImage);

    cv::imshow("trackBar",mDstImage);
}

void TrackbarExample::createTrackBar() {
    mSrcImage1 = cv::imread(R"(D:\code\LearnOpencv\input\17-1.jpg)");
    mSrcImage2 = cv::imread(R"(D:\code\LearnOpencv\input\17-2.jpg)");

    int g_nAlphaValueSlider = 70;

    cv::namedWindow("trackBar", 1);

    char trackBarName[50];
    sprintf(trackBarName, "alpha %d", g_nMaxAlphaValue);
    // 创建轨迹条，使用静态回调函数
    cv::createTrackbar(trackBarName, "trackBar", &g_nAlphaValueSlider, g_nMaxAlphaValue, onTrackBar, this);
    // 调用一次回调函数以显示初始状态
    onTrackBar(g_nAlphaValueSlider, this);
}

void TrackbarExample::onTrackBar(int SliderValue, void *userdata) {
    auto* self = static_cast<TrackbarExample*>(userdata);
    self->updateImage(SliderValue);
}

void TrackbarExample::createContrastAndBrightTrackBar() {
    mSrcImage3 = cv::imread(R"(D:\code\LearnOpencv\input\27.jpg)");
    mDstImage = cv::Mat::zeros(mSrcImage3.size(),mSrcImage3.type());
    //设定对比度和亮度的初值
    g_nContrastValue=80;
    g_nBrightValue=80;

    cv::namedWindow("trackBar", 1);

    cv::createTrackbar("Contrast", "trackBar", &g_nContrastValue, 300, onTrackBarContrastAndBright, this);
    cv::createTrackbar("Bright", "trackBar", &g_nBrightValue, 200, onTrackBarContrastAndBright, this);

    onTrackBarContrastAndBright(g_nContrastValue, this);
    onTrackBarContrastAndBright(g_nBrightValue, this);
}

void TrackbarExample::updateImageContrastAndBright(int value) {

    // 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
    std::cout << " g_nContrastValue " << g_nContrastValue << std::endl;
    std::cout << " g_nBrightValue " << g_nBrightValue << std::endl;

    for( int y = 0; y < mSrcImage3.rows; y++ )
    {
        for( int x = 0; x < mSrcImage3.cols; x++ )
        {
            for( int c = 0; c < 3; c++ )
            {
                mDstImage.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>( (g_nContrastValue*0.01)*( mSrcImage3.at<cv::Vec3b>(y,x)[c] ) + g_nBrightValue );
            }
        }
    }

    // 显示图像
    imshow("trackBar", mDstImage);
}

void TrackbarExample::onTrackBarContrastAndBright(int value, void *userdata) {
    auto* self = static_cast<TrackbarExample*>(userdata);
    self->updateImageContrastAndBright(value);
}

