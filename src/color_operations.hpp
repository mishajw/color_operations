#ifndef COLOR_OPERATIONS_COLOR_OPERATIONS_H
#define COLOR_OPERATIONS_COLOR_OPERATIONS_H

#include <boost/program_options.hpp>
#include "operation.hpp"

namespace color_operations {

void add_operations_program_options(boost::program_options::options_description &options_description);

void apply_with_program_options(
        std::string input_file, std::string output_file, boost::program_options::variables_map variables_map);

void apply(std::string input_file, std::string output_file, std::vector<std::shared_ptr<Operation>> operations);

}

#endif //COLOR_OPERATIONS_COLOR_OPERATIONS_H
