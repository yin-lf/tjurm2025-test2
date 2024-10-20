#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat output(new_rows, new_cols, input.type());
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            //resize前的坐标
            float x0 = j / scale;
            float y0 = i / scale;
            //找邻居点
            int x1 = static_cast<int>(x0);
            int y1 = static_cast<int>(y0);
            int x2 = x1 + 1;
            int y2 = y1 + 1;
            // 边界检查
            x2 = std::min(x2, input.cols - 1);
            y2 = std::min(y2, input.rows - 1);
            //Q = P1 * (1 - dx)(1 - dy) + P2 * dx(1 - dy) + P3 * (1 - dx)dy + P4 * dxdy
            float dx = x0 - x1;
            float dy = y0 - y1;
            int c=input.channels();
            for (int k = 0; k < c; k++){//遍历图像的每个颜色通道
                float P1 = input.at<cv::Vec3b>(y1, x1)[k]; // (x1, y1)
                float P2 = input.at<cv::Vec3b>(y1, x2)[k]; // (x2, y1)
                float P3 = input.at<cv::Vec3b>(y2, x1)[k]; // (x1, y2)
                float P4 = input.at<cv::Vec3b>(y2, x2)[k]; // (x2, y2)
                float Q = P1*(1-dx)*(1-dy) + P2*dx*(1-dy) + P3*(1-dx)*dy + P4*dx*dy;
            //cv::Mat 并不支持通过下标 [] 来直接访问矩阵元素。要访问图像中的像素值，应该使用 cv::Mat::at() 或其他类似的方法
            //赋值
                output.at<cv::Vec3b>(i, j)[k] = static_cast<uchar>(Q);
            }
        }
    }
    return output;
}