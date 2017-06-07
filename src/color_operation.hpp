#ifndef COLOR_OPERATIONS_COLOR_OPERATION_H
#define COLOR_OPERATIONS_COLOR_OPERATION_H

#include <string>
#include <opencv2/core/mat.hpp>

namespace color_operations {

struct ParameterBase {};

template <typename ParameterType, char const *_name>
class ColorOperation {
public:
    constexpr static char const *name = _name;

    virtual void apply(const ParameterType &parameters, cv::Mat &image) = 0;
};

}

#endif //COLOR_OPERATIONS_COLOR_OPERATION_H
