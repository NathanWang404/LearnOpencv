//
// Created by Administrator on 2024/5/16/016.
//

#include "UseMouse.hpp"

cv::Rect mRectangle;
bool mIsDrawingBox = false;
cv::RNG mRng = cv::RNG(12345);

void DrawRectangle(cv::Mat &img, cv::Rect box) {
    cv::rectangle(img, box.tl(), box.br(),
                  cv::Scalar(mRng.uniform(0, 255), mRng.uniform(0, 255), mRng.uniform(0, 255)));//随机颜色
}

void onMouseHandle(int event, int x, int y, int flags, void *userdata) {
    cv::Mat &image = *(cv::Mat *) userdata;
    switch (event) {
        //鼠标移动消息
        case cv::EVENT_MOUSEMOVE: {
            if (mIsDrawingBox)//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
            {
                mRectangle.width = x - mRectangle.x;
                mRectangle.height = y - mRectangle.y;
            }
            break;
        }

            //左键按下消息
        case cv::EVENT_LBUTTONDOWN: {
            std::cout << " EVENT_LBUTTONDOWN " << std::endl;
            mIsDrawingBox = true;
            mRectangle = cv::Rect(x, y, 0, 0);//记录起始点
            break;
        }

            //左键抬起消息
        case cv::EVENT_LBUTTONUP: {
            std::cout << " EVENT_LBUTTONUP " << std::endl;

            mIsDrawingBox = false;//置标识符为false
            //对宽和高小于0的处理
            if (mRectangle.width < 0) {
                mRectangle.x += mRectangle.width;
                mRectangle.width *= -1;
            }

            if (mRectangle.height < 0) {
                mRectangle.y += mRectangle.height;
                mRectangle.height *= -1;
            }
            //调用函数进行绘制
            DrawRectangle(image, mRectangle);
            imshow("image", image);

        }
            break;

    }
}


void UseMouse::MouseUseTest() {
    mRectangle = cv::Rect(-1, -1, 0, 0);
    cv::Mat srcImage(600, 800, CV_8UC3), tempImage;
    srcImage.copyTo(tempImage);
    srcImage = cv::Scalar::all(0);

    cv::namedWindow("mouseUseTest");
    cv::setMouseCallback("mouseUseTest", onMouseHandle, (void *) &srcImage);

    while (1) {
        srcImage.copyTo(tempImage);//拷贝源图到临时变量
        if (mIsDrawingBox) {
            std::cout << " 11111 " << std::endl;
            DrawRectangle(tempImage, mRectangle);//当进行绘制的标识符为真，则进行绘制
        }
        imshow("mouseUseTest", tempImage);
        if (cv::waitKey(10) == 27) break;//按下ESC键，程序退出
    }
}



