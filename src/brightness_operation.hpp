#ifndef COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
#define COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H

#include "color_operation.hpp"
#include <boost/program_options.hpp>
#include <boost/optional.hpp>

namespace color_operations {

struct BrightnessCliCreator : OperationCliCreator {
    void add_cli_arguments(boost::program_options::options_description &description) override;

    std::shared_ptr<ColorOperation> parse_arguments(const boost::program_options::variables_map &arguments) override;
};

class BrightnessOperation : public ColorOperation {
public:
    BrightnessOperation(double brightness);

    const double brightness;

    void apply(cv::Mat &image) override;
};

}

#endif //COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
