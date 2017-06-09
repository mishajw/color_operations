#ifndef COLOR_OPERATIONS_MATRIX_OPERATION_H
#define COLOR_OPERATIONS_MATRIX_OPERATION_H

#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include "color_operation.hpp"

namespace color_operations {

struct MatrixCliCreator : OperationCliCreator {
    void add_cli_arguments(boost::program_options::options_description &description);

    std::shared_ptr<ColorOperation> parse_arguments(const boost::program_options::variables_map &arguments) override;
};

class MatrixOperation : public ColorOperation {
public:
    MatrixOperation(
            double rr, double rg, double rb, double gr, double gg, double gb, double br, double bg, double bb) :
                    ColorOperation("matrix"), matrix((cv::Mat_<double>(3, 3) << rr, rg, rb, gr, gg, gb, br, bg, bb)) {}

    cv::Mat matrix;

    void apply(cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_MATRIX_OPERATION_H
