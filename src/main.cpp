#include <iostream>
#include <cv.hpp>
#include "matrix_operation.hpp"
#include "brightness_operation.hpp"

using namespace color_operations;

int main(int argc, const char **argv) {
    // Set up all operation creators
    std::vector<std::shared_ptr<OperationProgramOptionsCreator>> program_options_creators = {
            std::make_shared<BrightnessProgramOptionsCreator>(),
            std::make_shared<MatrixProgramOptionsCreator>()
    };

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
    std::for_each(
            program_options_creators.begin(),
            program_options_creators.end(),
            [&options_description](std::shared_ptr<OperationProgramOptionsCreator> creator) {
                creator->add_program_options(options_description);
            });

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

    // Get operations from program options
    std::vector<std::shared_ptr<Operation>> operations;
    operations.resize(program_options_creators.size());
    std::transform(
            program_options_creators.begin(),
            program_options_creators.end(),
            operations.begin(),
            [&variables_map](std::shared_ptr<OperationProgramOptionsCreator> creator) {
                return creator->parse_arguments(variables_map);
            });

    // Remove operations that weren't successfully parsed from program options
    operations.erase(
            std::remove_if(
                    operations.begin(),
                    operations.end(),
                    [](std::shared_ptr<Operation> operation) { return !operation; }),
            operations.end());

    // Read image from file
    cv::Mat image = cv::imread(input_path);

    // Apply operations to image
    std::for_each(operations.begin(), operations.end(), [&image](std::shared_ptr<Operation> operation) {
        operation->apply(image);
    });

    // Save the final image
    cv::imwrite(output_path, image);
}
