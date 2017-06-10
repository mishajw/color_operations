#ifndef COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
#define COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H

#include "operation.hpp"
#include <boost/program_options.hpp>
#include <boost/optional.hpp>

namespace color_operations {

struct BrightnessProgramOptionsCreator : OperationProgramOptionsCreator {
    void add_program_options(boost::program_options::options_description &description) override;

    std::shared_ptr<Operation> parse_arguments(const boost::program_options::variables_map &arguments) override;
};

class BrightnessOperation : public Operation {
public:
    BrightnessOperation(double brightness);

    const double brightness;

    void apply(cv::Mat &image, const std::string &image_name) override;
};

}

#endif //COLOR_OPERATIONS_BRIGHTNESS_OPERATION_H
