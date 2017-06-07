#include "brightness_operation.hpp"

namespace color_operations {

char const brightness_name[] = "brightness";

void BrightnessOperation::apply(const BrightnessParameters &parameters, cv::Mat &image) {
    for (auto iter = image.begin<cv::Vec3b>(); iter != image.end<cv::Vec3b>(); ++iter) {
        *iter *= parameters.brightness;
    }
}

}
