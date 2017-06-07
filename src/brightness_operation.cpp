#include <iostream>
#include "brightness_operation.hpp"

namespace color_operations {

char const brightness_name[] = "brightness";

void BrightnessOperation::apply(const BrightnessParameters &parameters, cv::Mat &image) {
    std::cout << "Applying " << this->name << std::endl;
}

}
