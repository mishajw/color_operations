#include "matrix_operation.hpp"

namespace color_operations {

void MatrixOperation::apply(cv::Mat &image) {
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

void MatrixCliCreator::add_cli_arguments(boost::program_options::options_description &description) {

}

std::shared_ptr<ColorOperation> MatrixCliCreator::parse_arguments(
        const boost::program_options::variables_map &arguments) {

    return nullptr;
}

}
