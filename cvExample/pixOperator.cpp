//
// Created by Administrator on 2024/5/14/014.
//

#include "pixOperator.hpp"

// tic is called to start timer
void tic(double &t) {
    t = (double) cv::getTickCount();
}

// toc is called to end timer
double toc(double &t) {
    return ((double) cv::getTickCount() - t) / cv::getTickFrequency();
}


void pixOperator::colorReduce(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();

    double t;
    tic(t);
    for (int i = 0; i < rowNumber; i++) {
        uchar *data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
    toc(t);
    cout << "forEach : " << toc(t) << endl;
}

void pixOperator::iterColorReduce(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();
    Mat_<Vec3b>::iterator iter = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator iterEnd = outputImage.end<Vec3b>();
    int index = 0;
//
    double t;
    tic(t);
    for (; iter != iterEnd; ++iter) {
        index++;
        (*iter)[0] = (*iter)[0] / div * div + div / 2;
        (*iter)[1] = (*iter)[1] / div * div + div / 2;
        (*iter)[2] = (*iter)[2] / div * div + div / 2;
    }
    std::cout << index << std::endl;
    toc(t);
    cout << "forEach : " << toc(t) << endl;
}

void pixOperator::ptrColorReduce(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数

    double t;
    tic(t);
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < colNumber; j++) {
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  //蓝色通道
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  //绿色通道
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  //红是通道
        }
    }
    toc(t);
    cout << "forEach : " << toc(t) << endl;
}

// Define a pixel
typedef cv::Point3_<cv::uint8_t> Pixel;

struct Operator {
    void operator()(Pixel &pixel, const int *position) const {
        // Perform a simple threshold operation
        int div = 32;
        pixel.x = pixel.x / div * div + div / 2;
        pixel.y = pixel.y / div * div + div / 2;
        pixel.z = pixel.z / div * div + div / 2;
    }
};

void pixOperator::forEachColorReduce(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数
    double t;
    tic(t);
    outputImage.forEach<Pixel>(Operator());
    toc(t);
    cout << "forEach : " << toc(t) << endl;
}

void pixOperator::forEachLambdaColorReduce(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数
    double t;
    tic(t);
    outputImage.forEach<Pixel>(
            [](Pixel &pixel, const int *pos) {
                int div = 32;
                pixel.x = pixel.x / div * div + div / 2;
                pixel.y = pixel.y / div * div + div / 2;
                pixel.z = pixel.z / div * div + div / 2;
            }
    );
    toc(t);
    cout << "forEachLambdaColorReduce : " << toc(t) << endl;
}


bool pixOperator::ROI_AddImage() {

    Mat srcImage1 = imread(R"(D:\code\LearnOpencv\input\dota_pa.jpg)");
    Mat logoImage = imread(R"(D:\code\LearnOpencv\input\dota_logo.jpg)");
    if (!srcImage1.data) {
        printf("读取srcImage1错误~！ \n");
        return false;
    }
    if (!logoImage.data) {
        return false;
    }

    Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

    Mat mask = imread(R"(D:\code\LearnOpencv\input\dota_logo.jpg)", 0);

    logoImage.copyTo(imageROI, mask);

    imshow("<1>ROI_AddImage<1>", srcImage1);

    return true;
}


//---------------------------------【LinearBlending（）函数】-------------------------------------
// 函数名：LinearBlending（）
// 描述：利用cv::addWeighted（）函数实现图像线性混合
//--------------------------------------------------------------------------------------------
bool pixOperator::LinearBlending() {
    double alphaValue = 0.5;
    double betaValue;
    Mat srcImage2, srcImage3, dstImage;

    srcImage2 = imread(R"(D:\code\LearnOpencv\input\mogu.jpg)");
    srcImage3 = imread(R"(D:\code\LearnOpencv\input\rain.jpg)");

    if (!srcImage2.data) {
        return false;
    }
    if (!srcImage3.data) {
        return false;
    }

    betaValue = (1.0 - alphaValue);
    cv::addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

    //    imshow("origin", srcImage2);
    imshow("output", dstImage);

    return true;

}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------
// 函数名：ROI_LinearBlending（）
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义
//			  感兴趣区域ROI，实现自定义区域的线性混合
//--------------------------------------------------------------------------------------------
bool pixOperator::ROI_LinearBlending() {

    Mat srcImage4 = imread(R"(D:\code\LearnOpencv\input\dota_pa.jpg)", 1);
    Mat logoImage = imread(R"(D:\code\LearnOpencv\input\dota_logo.jpg)");

    if (!srcImage4.data) {
        return false;
    }
    if (!logoImage.data) {
        return false;
    }

    Mat imageROI, dstImage;
    imageROI = srcImage4(Rect(500, 200, logoImage.cols, logoImage.rows));
    //imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));
    addWeighted(imageROI, 0.8, logoImage, 0.1, 0., dstImage);

    imshow("imageROI", dstImage);

    return true;
}

bool pixOperator::MultiChannelBlending() {
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;
    Mat imageBlueChannel, imageGreenChannel, imageRedChannel;


    logoImage = imread(R"(D:\code\LearnOpencv\input\dota_logo.jpg)", 0);
    srcImage = imread(R"(D:\code\LearnOpencv\input\dota_jugg.jpg)");

    if (!logoImage.data) {
        printf("Oh，no，读取logoImage错误~！ \n");
        return false;
    }
    if (!srcImage.data) {
        printf("Oh，no，读取srcImage错误~！ \n");
        return false;
    }

    split(srcImage, channels);//分离色彩通道

    imageBlueChannel = channels.at(0);
    addWeighted(imageBlueChannel(Rect(0, 250, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageBlueChannel(Rect(0, 250, logoImage.cols, logoImage.rows)));

    imageBlueChannel = channels.at(1);
    addWeighted(imageBlueChannel(Rect(250, 250, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageBlueChannel(Rect(250, 250, logoImage.cols, logoImage.rows)));

    imageRedChannel = channels.at(2);
    addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));


    merge(channels, srcImage);

    namedWindow(" <1>游戏原画+logo蓝色通道");
    imshow(" <1>游戏原画+logo蓝色通道", srcImage);

    return true;
}

void pixOperator::createAlphaMat(Mat &mat) {

    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            Vec4b &rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float) mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float) mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}

void pixOperator::baseImageMat() {
    Mat I = Mat::eye(4, 4, CV_64F);
    I.at<double>(1, 1) = CV_PI;
    cout << "\nI = " << I << ";\n" << endl;

    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));

    //此段代码的OpenCV2版为：
    //cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
    //cout << "r (Python风格) = " << format(r,"python") << ";" << endl << endl;
    //cout << "r (Numpy风格) = " << format(r,"numpy") << ";" << endl << endl;
    //cout << "r (逗号分隔风格) = " << format(r,"csv") << ";" << endl<< endl;
    //cout << "r (C语言风格) = " << format(r,"C") << ";" << endl << endl;
    //此段代码的OpenCV3版为：
    cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
    cout << "r (Python风格) = " << cv::format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (Numpy风格) = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    cout << "r (逗号分隔风格) = " << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    cout << "r (C语言风格) = " << format(r, Formatter::FMT_C) << ";" << endl << endl;


    Point2f p(6, 2);
    cout << "【2维点】p = " << p << ";\n" << endl;

    Point3f p3f(8, 2, 0);
    cout << "【3维点】p3f = " << p3f << ";\n" << endl;

    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);

    cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n" << endl;

    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float) (i * 5), (float) (i % 7));

    cout << "【二维点向量】points = " << points << ";";
}




