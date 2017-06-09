#include "brightness_operation.hpp"

namespace color_operations {

char const brightness_name[] = "brightness";

void BrightnessOperation::apply(const BrightnessParameters &parameters, cv::Mat &image) {
    for (auto iter = image.begin<cv::Vec3b>(); iter != image.end<cv::Vec3b>(); ++iter) {
        *iter *= parameters.brightness;
    }
}

void BrightnessParametersParser::add_cli_arguments(boost::program_options::options_description &description) {
    description.add_options()
            (
                    BrightnessOperation::name,
                    boost::program_options::value<double>(),
                    "Set brightness level of image. 1 keeps brightness the same.");
}

boost::optional<const BrightnessParameters> BrightnessParametersParser::parse_arguments(
        const boost::program_options::variables_map &arguments) {

    if (arguments.count(BrightnessOperation::name)) {
        return boost::optional<const BrightnessParameters>(arguments[BrightnessOperation::name].as<double>());
    } else {
        return boost::optional<const BrightnessParameters>();
    }
}

}
