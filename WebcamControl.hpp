#pragma once
#include "GenericCHeader.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
class WebcamControl
{
private:
    int x;
    int y;
    int webcamThreshold;
    void prepareAndThresholdFrame(cv::Mat& image, cv::Mat& image_gray, cv::Mat& res);
    void getBiggestContour(cv::Mat& res, std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Vec4i>& hierarchy, int& savedContour);
    void drawBiggestBlob(cv::Mat& img, std::vector<std::vector<cv::Point>>& contours, int savedContour);
    void getAndDrawCentroid(cv::Mat& img);
public:
    void run();
    int getX();
    int getY();
    void setThreshold(int targetThreshold);
    int getThreshold();
};