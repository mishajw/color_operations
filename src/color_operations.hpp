#ifndef COLOR_OPERATIONS_COLOR_OPERATIONS_H
#define COLOR_OPERATIONS_COLOR_OPERATIONS_H

#include <boost/program_options.hpp>
#include "operation.hpp"

namespace color_operations {

void add_operations_program_options(boost::program_options::options_description &options_description);

std::vector<std::shared_ptr<Operation>> get_operations_from_program_options(
        const boost::program_options::variables_map &variables_map);

void apply(
        const std::string &input_file,
        const std::string &output_file,
        const std::vector<std::shared_ptr<Operation>> &operations);

void apply(cv::Mat &image, const std::vector<std::shared_ptr<Operation>> &operations, const std::string &image_name);

}

#endif //COLOR_OPERATIONS_COLOR_OPERATIONS_H
