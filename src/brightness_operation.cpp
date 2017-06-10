#include "brightness_operation.hpp"

namespace color_operations {

BrightnessOperation::BrightnessOperation(double brightness) : Operation("brightness"), brightness(brightness) {}

void BrightnessOperation::apply(cv::Mat &image, const std::string &image_name) {
    for (auto iter = image.begin<cv::Vec3b>(); iter != image.end<cv::Vec3b>(); ++iter) {
        *iter *= this->brightness;
    }
}

void BrightnessProgramOptionsCreator::add_program_options(boost::program_options::options_description &description) {
    description.add_options()
            (
                    "brightness",
                    boost::program_options::value<double>(),
                    "Set brightness level of image. 1 keeps brightness the same.");
}

std::shared_ptr<Operation> BrightnessProgramOptionsCreator::parse_arguments(
        const boost::program_options::variables_map &arguments) {

    if (arguments.count("brightness")) {
        return std::make_shared<BrightnessOperation>(arguments["brightness"].as<double>());
    } else {
        return std::shared_ptr<Operation>();
    }
}

}
