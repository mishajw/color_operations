#ifndef COLOR_OPERATIONS_MATRIX_OPERATION_H
#define COLOR_OPERATIONS_MATRIX_OPERATION_H

#include "color_operation.hpp"

namespace color_operations {

extern char const matrix_name[];

struct MatrixParameters : ParameterBase {
    double rr, rb, rg, br, bb, bg, gr, gb, gg;

    MatrixParameters(
            double rr, double rb, double rg, double br, double bb, double bg, double gr, double gb, double gg) :
                    rr(rr), rb(rb), rg(rg), br(br), bb(bb), bg(bg), gr(gr), gb(gb), gg(gg) {}
};

class MatrixOperation : public ColorOperation<MatrixParameters, matrix_name> {
public:
    void apply(const MatrixParameters &parameters, cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_MATRIX_OPERATION_H
