#include <iostream>
#include <cv.hpp>
#include "matrix_operation.hpp"
#include "brightness_operation.hpp"
#include "color_operations.hpp"

int main(int argc, const char **argv) {
    // Set up program options
    boost::program_options::options_description options_description("Allowed options");
    options_description.add_options()
            ("help", "Show help message")
            (
                    "input",
                    boost::program_options::value<std::string>()->required(),
                    "Path of the image to apply operations to")
            (
                    "output",
                    boost::program_options::value<std::string>()->required(),
                    "Path to write the output image to");
    color_operations::add_operations_program_options(options_description);

    // Parse program options
    boost::program_options::variables_map variables_map;
    boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, options_description), variables_map);

    // Check that program options are correct
    try {
        boost::program_options::notify(variables_map);
    } catch (const std::exception &e) {
        std::cerr << "Error with program options: " << e.what() << std::endl;
        std::exit(1);
    }

    // Print help message if requested
    if (variables_map.count("help")) {
        std::cout << options_description << std::endl;
        std::exit(0);
    }

    // Get input/output from program options
    const std::string input_path = variables_map["input"].as<std::string>();
    const std::string output_path = variables_map["output"].as<std::string>();

    color_operations::apply_with_program_options(input_path, output_path, variables_map);
}
