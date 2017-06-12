#ifndef COLOR_OPERATIONS_RANDOM_OPERATION_H
#define COLOR_OPERATIONS_RANDOM_OPERATION_H

#include <random>
#include "operation.hpp"

namespace color_operations {

struct RandomProgramOptionsCreator : OperationProgramOptionsCreator {
    void add_program_options(boost::program_options::options_description &description);

    std::shared_ptr<Operation> parse_arguments(const boost::program_options::variables_map &arguments) override;
};

class RandomOperation : public Operation {
public:
    std::mt19937 random_generator;

    bool brightness;

    bool matrix;

    const boost::optional<std::string> random_variables_path_opt;

    RandomOperation(bool brightness, bool matrix);

    RandomOperation(bool brightness, bool matrix, const std::string &random_variables_path);

    RandomOperation(bool brightness, bool matrix, const boost::optional<std::string> &random_variables_path_opt);

    void apply(cv::Mat &image, const std::string &image_name) override;

private:
    void add_random_brightness_options(boost::program_options::variables_map &variables_map);

    void add_random_matrix_options(boost::program_options::variables_map &variables_map);

    void write_variables_map(
            const boost::program_options::variables_map &map,
            const std::string &random_variables_path,
            const std::string &image_name);
};

}

#endif //COLOR_OPERATIONS_RANDOM_OPERATION_H
