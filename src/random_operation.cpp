#include <fstream>
#include "color_operations.hpp"
#include "random_operation.hpp"
#include "brightness_operation.hpp"
#include "matrix_operation.hpp"

namespace color_operations {

RandomOperation::RandomOperation(bool brightness, bool matrix) :
        RandomOperation(brightness, matrix, boost::optional<std::string>()) {}

RandomOperation::RandomOperation(bool brightness, bool matrix, const std::string &random_variables_path) :
        RandomOperation(brightness, matrix, boost::optional<std::string>(random_variables_path)) {}

RandomOperation::RandomOperation(
        bool brightness, bool matrix, const boost::optional<std::string> &random_variables_path_opt) :
            Operation("random"),
            brightness(brightness),
            matrix(matrix),
            random_variables_path_opt(random_variables_path_opt),
            random_generator(std::random_device()()) {}

void RandomOperation::apply(cv::Mat &image, const std::string &image_name) {
    boost::program_options::variables_map variables_map;

    if (this->brightness) {
        add_random_brightness_options(variables_map);
    }

    if (this->matrix) {
        add_random_matrix_options(variables_map);
    }

    if (this->random_variables_path_opt) {
        write_variables_map(variables_map, this->random_variables_path_opt.get(), image_name);
    }

    auto operations = color_operations::get_operations_from_program_options(variables_map);
    color_operations::apply(image, operations, image_name);
}

void RandomOperation::add_random_brightness_options(boost::program_options::variables_map &variables_map) {
    std::uniform_real_distribution<> distribution(0, 1);
    const double brightness_value = distribution(random_generator);

    variables_map.insert(
            std::make_pair("brightness", boost::program_options::variable_value(brightness_value, false)));
}

void RandomOperation::add_random_matrix_options(boost::program_options::variables_map &variables_map) {
    std::normal_distribution<> distribution(0, 0.5);

    const auto high_distribution_fn = [&distribution, this]() -> double {
        double value = distribution(this->random_generator);
        double clipped = std::max(-1.0, std::min(1.0, value));

        return value > 0 ? 1 - clipped : 1 + clipped;
    };

    const auto low_distribution_fn = [&high_distribution_fn]() -> double {
        return 1 - high_distribution_fn();
    };

    std::stringstream ss_red, ss_green, ss_blue;
    ss_red << high_distribution_fn() << "," << low_distribution_fn() << "," << low_distribution_fn();
    ss_green << low_distribution_fn() << "," << high_distribution_fn() << "," << low_distribution_fn();
    ss_blue << low_distribution_fn() << "," << low_distribution_fn() << "," << high_distribution_fn();

    variables_map.insert(
            std::make_pair("matrix.red", boost::program_options::variable_value(ss_red.str(), false)));
    variables_map.insert(
            std::make_pair("matrix.green", boost::program_options::variable_value(ss_green.str(), false)));
    variables_map.insert(
            std::make_pair("matrix.blue", boost::program_options::variable_value(ss_blue.str(), false)));
}

void RandomOperation::write_variables_map(
        const boost::program_options::variables_map &variables_map,
        const std::string &random_variables_path,
        const std::string &image_name) {

    std::stringstream output;
    output << image_name << ": ";

    for (const auto &kv : variables_map) {
        output << kv.first << " ";

        if (typeid(double) == kv.second.value().type()) {
            output << kv.second.as<double>();
        } else if (typeid(int) == kv.second.value().type()) {
            output << kv.second.as<int>();
        } else if (typeid(std::string) == kv.second.value().type()) {
            output << kv.second.as<std::string>();
        }

        output << "; ";
    }

    output << "\n";

    std::ofstream output_stream(random_variables_path, std::ios::app | std::ios::out);
    output_stream << output.str();
}

void RandomProgramOptionsCreator::add_program_options(boost::program_options::options_description &description) {
    description.add_options()
            ("random", "Randomly apply operations to image(s)")
            (
                    "random.brightness",
                    boost::program_options::value<bool>()->default_value(true),
                    "Randomly apply brightness operation")
            (
                    "random.matrix",
                    boost::program_options::value<bool>()->default_value(true),
                    "Randomly apply matrix operation")
            (
                    "random.write_variables",
                    boost::program_options::value<std::string>(),
                    "Where to write out random variables");
}

std::shared_ptr<Operation> RandomProgramOptionsCreator::parse_arguments(
        const boost::program_options::variables_map &arguments) {

    if (!arguments.count("random")) {
        return std::shared_ptr<Operation>();
    }

    bool brightness = arguments["random.brightness"].as<bool>();
    bool matrix = arguments["random.matrix"].as<bool>();

    if (arguments.count("random.write_variables")) {
        const std::string &random_variables_path = arguments["random.write_variables"].as<std::string>();

        return std::make_shared<RandomOperation>(brightness, matrix, random_variables_path);
    } else {
        return std::make_shared<RandomOperation>(brightness, matrix);
    }
}

}
