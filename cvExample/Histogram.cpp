//
// Created by Administrator on 2024/5/8/008.
//

#include "Histogram.hpp"

void Histogram::drawHistogram(cv::Mat &src) {
    cv::Mat image = src.clone();
    if (image.empty()) {
        std::cerr << "Failed to read image!" << std::endl;
        return;
    }

    // 将图像分割成三个单通道图像
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // 设置直方图参数
    int histSize = 256; // 直方图的 bin 数量
    float range[] = {0, 256}; // 像素值范围
    const float *histRange = {range};

    // 计算直方图
    cv::Mat hist_R, hist_G, hist_B;
    cv::calcHist(&channels[0], 1, 0, cv::Mat(), hist_R, 1, &histSize, &histRange);
    cv::calcHist(&channels[1], 1, 0, cv::Mat(), hist_G, 1, &histSize, &histRange);
    cv::calcHist(&channels[2], 1, 0, cv::Mat(), hist_B, 1, &histSize, &histRange);

    // 绘制直方图
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    // 归一化直方图数据
    cv::normalize(hist_R, hist_R, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(hist_G, hist_G, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(hist_B, hist_B, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // 绘制直方图
    for (int i = 1; i < histSize; ++i) {
        cv::line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist_R.at<float>(i - 1))),
             cv::Point(bin_w * (i), hist_h - cvRound(hist_R.at<float>(i))),
             cv::Scalar(0, 0, 255), 2, 8, 0);
        cv::line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist_G.at<float>(i - 1))),
             cv::Point(bin_w * (i), hist_h - cvRound(hist_G.at<float>(i))),
             cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist_B.at<float>(i - 1))),
             cv::Point(bin_w * (i), hist_h - cvRound(hist_B.at<float>(i))),
             cv::Scalar(255, 0, 0), 2, 8, 0);
    }

    // 显示直方图
    cv::imshow("RGB Histogram", histImage);
    cv::waitKey(0);
}

void Histogram::rgbDrawHistogram(cv::Mat &src) {
    cv::Mat srcImage = src.clone();
    if (srcImage.empty()) {
        std::cerr << "Failed to read image!" << std::endl;
        return;
    }
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = { 0, 256 };
    const float* ranges[] = { range};
    cv::MatND redHist,grayHist,blueHist;
    int channels_r[] = {0};

    //【3】进行直方图的计算（红色分量部分）
    cv::calcHist( &srcImage, 1, channels_r, cv::Mat(), //不使用掩膜
              redHist, 1, hist_size, ranges,
              true, false );

    //【4】进行直方图的计算（绿色分量部分）
    int channels_g[] = {1};
    calcHist( &srcImage, 1, channels_g, cv::Mat(), // do not use mask
              grayHist, 1, hist_size, ranges,
              true, // the histogram is uniform
              false );

    //【5】进行直方图的计算（蓝色分量部分）
    int channels_b[] = {2};
    cv::calcHist( &srcImage, 1, channels_b, cv::Mat(), // do not use mask
              blueHist, 1, hist_size, ranges,
              true, // the histogram is uniform
              false );

    //-----------------------绘制出三色直方图------------------------
    //参数准备
    double maxValue_red,maxValue_green,maxValue_blue;
    cv::minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
    cv::minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
    cv::minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
    int scale = 1;
    int histHeight=256;
    cv::Mat histImage = cv::Mat::zeros(histHeight,bins*3, CV_8UC3);

    //正式开始绘制
    for(int i=0;i<bins;i++)
    {
        //参数准备
        float binValue_red = redHist.at<float>(i);
        float binValue_green = grayHist.at<float>(i);
        float binValue_blue = blueHist.at<float>(i);
        int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);  //要绘制的高度
        int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);  //要绘制的高度
        int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);  //要绘制的高度

        //绘制红色分量的直方图
        cv::rectangle(histImage,cv::Point(i*scale,histHeight-1),
                  cv::Point((i+1)*scale - 1, histHeight - intensity_red),
                  cv::Scalar(255,0,0));

        //绘制绿色分量的直方图
        cv::rectangle(histImage,cv::Point((i+bins)*scale,histHeight-1),
                  cv::Point((i+bins+1)*scale - 1, histHeight - intensity_green),
                  cv::Scalar(0,255,0));

        //绘制蓝色分量的直方图
        cv::rectangle(histImage,cv::Point((i+bins*2)*scale,histHeight-1),
                  cv::Point((i+bins*2+1)*scale - 1, histHeight - intensity_blue),
                  cv::Scalar(0,0,255));

    }

    //在窗口中显示出绘制好的直方图
    cv::imshow("RGB Histogram", histImage);
    cv::waitKey(0);
}
