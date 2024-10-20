#include "impls.h"


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& input) {//返回值是一个二维向量，存储的是多个轮廓，每个轮廓都是由多个 cv::Point（二维点）组成的向量。
    /**
     * 要求：
     * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
     * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
     * 
     * 提示：
     * 1. 使用cv::imshow来查看输入图像。
     * 2. 使用cv::drawContours来在一张图上绘制轮廓。
     * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理。
     * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
     * 
     * 通过条件：
     * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
     */
    
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray;//用来储存
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);//COLOR_BGR2GRAY 表示将 BGR 颜色空间转换为灰度空间。
    //用 cvtColor 函数将输入的三通道彩色图像 input 转换为单通道的灰度图 gray

    cv::Mat binary;
    cv::threshold(gray, binary, 50, 255, cv::THRESH_BINARY);//二值化操作
    //使用 threshold 函数对灰度图进行二值化，将像素值大于50的点设置为 255（白色），其余的点设置为 0（黑色）。这使得图像变成了黑白图，方便后续的轮廓查找。
   
    std::vector<std::vector<cv::Point>> contours;//存储多个轮廓，每个轮廓都是一个cv::Point类型的向量（即一组点）。
    std::vector<cv::Vec4i> hierarchy;  // 存储轮廓的层次结构
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);//查找轮廓
    //findContours 函数查找图像中的轮廓：
    // 第一个参数 binary 是输入的二值化图像。
    // 第二个参数 contours 是存储找到的轮廓的变量。
    //hierarchy获取层次结构
    // RETR_EXTERNAL 仅提取最外层的轮廓。
    // CHAIN_APPROX_SIMPLE 会压缩轮廓信息，只保存必要的顶点，减少内存使用。
    
    // 只提取最内层轮廓根据层次结构进行判断
    std::vector<std::vector<cv::Point>> innerContours;
    for (size_t i = 0; i < contours.size(); i++) {
        // 如果 hierarchy[i][2] == -1，表示该轮廓有子轮廓（即内部有空洞）
        if (hierarchy[i][2] == -1) {
            innerContours.push_back(contours[i]);
        }
    }
    return innerContours;
}