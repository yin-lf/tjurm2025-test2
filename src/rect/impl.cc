#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;// 初始化返回值
    // IMPLEMENT YOUR CODE HERE
    //彩转灰
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    //对灰度图二值化
    cv::Mat binary;
    cv::Canny(gray, binary, 100, 200); // 使用Canny边缘检测得到二值化图像
    // 找到所有轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //RETR_EXTERNAL 会忽略内层的轮廓，只提取最外层的。这对于我们在图像中只想找到最大的轮廓（如最大的矩形）是理想的，因为内层的小轮廓（如噪声、空洞等）可能干扰结果。
    // 遍历找到的轮廓
    if (!contours.empty()) {
        std::vector<cv::Point> largestContour = contours[0];
        for (const auto& contour : contours) {
            if (cv::contourArea(contour) > cv::contourArea(largestContour)) {
                largestContour = contour;//熟悉的找最大操作
            }
        }
        // 获取外接矩形和最小面积外接矩形
        res.first = cv::boundingRect(largestContour);        // 外接矩形
        res.second = cv::minAreaRect(largestContour);        // 最小面积外接矩形
    }

    return res;
}