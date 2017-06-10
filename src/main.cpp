#include <iostream>
#include <cv.hpp>
#include <boost/filesystem.hpp>
#include "matrix_operation.hpp"
#include "brightness_operation.hpp"
#include "color_operations.hpp"

int main(int argc, const char **argv) {
    // Set up program options
    boost::program_options::options_description options_description("Allowed options");
    options_description.add_options()
            ("help", "Show help message")
            (
                    "input_file",
                    boost::program_options::value<std::string>(),
                    "Path of the image to apply operations to")
            (
                    "output_file",
                    boost::program_options::value<std::string>(),
                    "Path to write the output image to")
            (
                    "input_directory",
                    boost::program_options::value<std::string>(),
                    "Directory of images to apply operations to")
            (
                    "output_directory",
                    boost::program_options::value<std::string>(),
                    "Directory to write output images to");

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

    if (variables_map.count("input_file") && variables_map.count("output_file")) {
        const std::string input_file = variables_map["input_file"].as<std::string>();
        const std::string output_file = variables_map["output_file"].as<std::string>();

        color_operations::apply_with_program_options(input_file, output_file, variables_map);
    } else if (variables_map.count("input_directory") && variables_map.count("output_directory")) {
        const std::string input_directory = variables_map["input_directory"].as<std::string>();
        const std::string output_directory = variables_map["output_directory"].as<std::string>();
        boost::filesystem::create_directories(output_directory);

        // TODO: Parallelise
        boost::filesystem::directory_iterator directory_end_iter;
        for (
                boost::filesystem::directory_iterator directory_iter(input_directory);
                directory_iter != directory_end_iter;
                ++directory_iter) {

            const boost::filesystem::path input_file(directory_iter->path());
            const boost::filesystem::path output_file = output_directory / input_file.filename();

            color_operations::apply_with_program_options(input_file.string(), output_file.string(), variables_map);
        }
    } else {
        std::cerr <<
                "Must provide either input_file and output_file, or input_directory and output_directory arguments" <<
                std::endl;
    }
}
