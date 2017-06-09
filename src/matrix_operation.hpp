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
    MatrixOperation(cv::Mat matrix);

    cv::Mat matrix;

    void apply(cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_MATRIX_OPERATION_H
