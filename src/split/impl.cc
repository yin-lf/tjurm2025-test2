#include "impls.h"

std::vector<cv::Mat> split(const cv::Mat& rgb_image) {
    //每个 cv::Mat 对象分别表示蓝色、绿色和红色通道的图像; rgb_image表示一张彩色图像,它的数据类型是 cv::Mat;& 表示传递的是引用，避免复制图像数据，提高函数的执行效率
    /**
     * TODO: 将图像分割为 blue green red 三个通道，具体内容：
     *  1. 将彩色图片 rgb_image 转换为三个通道的 cv::Mat
     *  2. 将三个通道的 cv::Mat 保存到 std::vector<cv::Mat> 中
     * HINT:
     *  1. 使用 cv::split 函数，其参数如下
     *     void cv::split(
     *          InputArray          src,    // 输入的彩色图像
     *          OutputArrayOfArrays mv      // 输出的三个通道图像
     *     )
     * PS: 在 opencv 中，图像的通道顺序是 BGR: Blue Green Red
     * GOAL:
     *  1. 此任务会自动判断你的代码是否正确，通过测试 (打印出 pass ) 即可
     */
    std::vector<cv::Mat> result(3);

    // TODO: 实现代码
    cv::split(rgb_image, result);    // 分割图像为三个通道
    return result;
}
