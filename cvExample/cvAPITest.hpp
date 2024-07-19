//
// Created by Administrator on 2024/7/4/004.
//

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc.hpp"

#include <iostream>


class cvAPITest {
public:
    //二值化处理
    void thresholdProcess();
    //cv::copyTo()函数测试  使用mask进行选择性复制
    void copyToTest();
    //cv::Mat 区块访问
    void subMatTest();
};


