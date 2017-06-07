#include <iostream>
#include "matrix_operation.hpp"

namespace color_operations {

char const matrix_name[] = "matrix";

void MatrixOperation::apply(const MatrixParameters &parameters, cv::Mat &image) {
    std::cout << "Applying " << this->name << std::endl;
}

}
