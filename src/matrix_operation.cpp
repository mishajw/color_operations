#include <regex>
#include <iostream>
#include "matrix_operation.hpp"

namespace color_operations {

MatrixOperation::MatrixOperation(cv::Mat matrix) : Operation("matrix"), matrix(matrix) {
    assert(matrix.cols == 3 && matrix.rows == 3);
}

void MatrixOperation::apply(cv::Mat &image, const std::string &image_name) {
    for (auto iter = image.begin<cv::Vec3b>(); iter != image.end<cv::Vec3b>(); ++iter) {
        double current_pixel_double_data[] = {
                static_cast<double>((*iter)[0]),
                static_cast<double>((*iter)[1]),
                static_cast<double>((*iter)[2])
        };

        cv::Mat current_pixel = cv::Mat(3, 1, CV_64FC1, current_pixel_double_data);

        const cv::Mat_<double> &new_pixel = this->matrix * current_pixel;
        const cv::Vec3b &new_pixel_vec = cv::Vec3b(new_pixel);

        *iter = new_pixel_vec;
    }
}

void MatrixProgramOptionsCreator::add_program_options(boost::program_options::options_description &description) {
    description.add_options()
            ("matrix.red", boost::program_options::value<std::string>(),"A list of modifiers for red, respectively "
                    "how much red, blue, and green should be in the output red")
            ("matrix.blue", boost::program_options::value<std::string>(),"A list of modifiers for blue, respectively "
                    "how much red, blue, and green should be in the output blue")
            ("matrix.green", boost::program_options::value<std::string>(),"A list of modifiers for green, respectively "
                    "how much red, blue, and green should be in the output green");
}

std::shared_ptr<Operation> MatrixProgramOptionsCreator::parse_arguments(
        const boost::program_options::variables_map &arguments) {

    const std::vector<std::string> colors{"red", "green", "blue"};
    std::vector<double> matrix_values;

    for (const auto &color : colors) {
        std::string argument_name = "matrix." + color;

        if (!arguments.count(argument_name)) {
            return std::shared_ptr<Operation>();
        }

        std::string argument_value = arguments[argument_name].as<std::string>();

        std::regex regex("([\\.0-9]+),([\\.0-9]+),([\\.0-9]+)");

        std::smatch matches;

        if (std::regex_search(argument_value, matches, regex)/* && matches.size() == 3*/) {
            for (unsigned int i = 1; i <= 3; i++) {
                matrix_values.push_back(std::stod(matches[i]));
            }
        }
    }

    if (matrix_values.size() == 9) {
        cv::Mat matrix(3, 3, CV_64FC1);

        std::memcpy(matrix.data, matrix_values.data(), matrix_values.size() * sizeof(double));

        return std::make_shared<MatrixOperation>(matrix);
    } else {
        return std::shared_ptr<Operation>();
    }
}

}
