//
// Created by Administrator on 2024/5/16/016.
//

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

class TrackbarExample {
public:
    void createTrackBar();

    void updateImage(int SliderValue);

    static void onTrackBar(int SliderValue, void *userdata);

    void createContrastAndBrightTrackBar();

    void updateImageContrastAndBright(int value);

    static void onTrackBarContrastAndBright(int value, void *userdata);

public:
    cv::Mat mSrcImage1;
    cv::Mat mSrcImage2;
    cv::Mat mSrcImage3;
    cv::Mat mDstImage;

};



