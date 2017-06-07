#ifndef COLOR_OPERATIONS_MATRIX_OPERATION_H
#define COLOR_OPERATIONS_MATRIX_OPERATION_H

#include "color_operation.hpp"

namespace color_operations {

extern char const matrix_name[];

struct MatrixParameters : ParameterBase {
    cv::Mat matrix;

    MatrixParameters(
            double rr, double rg, double rb, double gr, double gg, double gb, double br, double bg, double bb) :
                    matrix((cv::Mat_<double>(3, 3) << rr, rg, rb, gr, gg, gb, br, bg, bb)) {}
};

class MatrixOperation : public ColorOperation<MatrixParameters, matrix_name> {
public:
    void apply(const MatrixParameters &parameters, cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_MATRIX_OPERATION_H
