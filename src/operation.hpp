#ifndef COLOR_OPERATIONS_COLOR_OPERATION_H
#define COLOR_OPERATIONS_COLOR_OPERATION_H

#include <string>
#include <opencv2/core/mat.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/optional.hpp>

namespace color_operations {

class Operation {
public:
    Operation(const std::string name) : name(name) {}

    const std::string name;

    virtual void apply(cv::Mat &image) = 0;
};

struct OperationProgramOptionsCreator {
    virtual void add_program_options(boost::program_options::options_description &description) = 0;

    virtual std::shared_ptr<Operation> parse_arguments(const boost::program_options::variables_map &arguments) = 0;
};

}

#endif //COLOR_OPERATIONS_COLOR_OPERATION_H
