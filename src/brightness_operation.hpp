#ifndef COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
#define COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H

#include "color_operation.hpp"
#include <boost/program_options.hpp>
#include <boost/optional.hpp>

namespace color_operations {

extern char const brightness_name[];

struct BrightnessParameters : ParameterBase {
    double brightness;

    BrightnessParameters(double brightness) : brightness(brightness) {}
};

struct BrightnessParametersParser {
    static void add_cli_arguments(boost::program_options::options_description &description);

    static boost::optional<const BrightnessParameters> parse_arguments(
            const boost::program_options::variables_map &arguments);
};

class BrightnessOperation : public ColorOperation<BrightnessParameters, BrightnessParametersParser, brightness_name> {
public:
    void apply(const BrightnessParameters &parameters, cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
