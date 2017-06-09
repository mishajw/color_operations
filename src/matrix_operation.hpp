#ifndef COLOR_OPERATIONS_MATRIX_OPERATION_H
#define COLOR_OPERATIONS_MATRIX_OPERATION_H

#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include "operation.hpp"

namespace color_operations {

struct MatrixProgramOptionsCreator : OperationProgramOptionsCreator {
    void add_program_options(boost::program_options::options_description &description);

    std::shared_ptr<Operation> parse_arguments(const boost::program_options::variables_map &arguments) override;
};

class MatrixOperation : public Operation {
public:
    MatrixOperation(
            double rr, double rg, double rb, double gr, double gg, double gb, double br, double bg, double bb) :
                    Operation("matrix"), matrix((cv::Mat_<double>(3, 3) << rr, rg, rb, gr, gg, gb, br, bg, bb)) {}

    cv::Mat matrix;

    void apply(cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_MATRIX_OPERATION_H
