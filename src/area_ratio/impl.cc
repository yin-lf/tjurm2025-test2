#include "impls.h"


float compute_area_ratio(const std::vector<cv::Point>& contour) {//传入点集即轮廓（每个轮廓都是由多个 cv::Point（二维点）组成的向量）
    /**
     * 要求：
     *      计算输入的轮廓的面积与它的最小外接矩形面积的比例。自行查找
     * 获得轮廓面积的函数。这个量可以用来判断一个轮廓到底有多靠近一个矩形。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件:
     * 运行测试点，通过即可。
     */
     // 计算轮廓
    double contour_area = cv::contourArea(contour);
    // 计算最小外接矩形
    cv::RotatedRect min_rect = cv::minAreaRect(contour);
    double rect_area = min_rect.size.width * min_rect.size.height;
    // 防止分母为0
    if (rect_area == 0) {
        return 0.f;
    }
    float area_ratio = static_cast<float>(contour_area / rect_area);
    return area_ratio;
}