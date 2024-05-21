//
// Created by Administrator on 2024/5/8/008.
//

#pragma once
#include <iostream>
#include <fstream>
#include <numeric>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Histogram {
public:
    void drawHistogram(cv::Mat& src);
    void rgbDrawHistogram(cv::Mat& src);
};


