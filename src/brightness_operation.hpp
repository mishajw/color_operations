#ifndef COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
#define COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H

#include "color_operation.hpp"

namespace color_operations {

extern char const brightness_name[];

struct BrightnessParameters : ParameterBase {
    double brightness;

    BrightnessParameters(double brightness) : brightness(brightness) {}
};

class BrightnessOperation : public ColorOperation<BrightnessParameters, brightness_name> {
public:
    void apply(const BrightnessParameters &parameters, cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
