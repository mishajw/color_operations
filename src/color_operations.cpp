#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "color_operations.hpp"
#include "brightness_operation.hpp"
#include "matrix_operation.hpp"

namespace color_operations {

const std::vector<std::shared_ptr<OperationProgramOptionsCreator>> operation_creators = {
        std::make_shared<BrightnessProgramOptionsCreator>(),
        std::make_shared<MatrixProgramOptionsCreator>()
};

void add_operations_program_options(boost::program_options::options_description &options_description) {
    std::for_each(
            operation_creators.begin(),
            operation_creators.end(),
            [&options_description](std::shared_ptr<OperationProgramOptionsCreator> creator) {
                creator->add_program_options(options_description);
            });
}

void apply_with_program_options(
        std::string input_file, std::string output_file, boost::program_options::variables_map variables_map) {

    std::cout << "Processing image " << input_file << " and writing to " << output_file << std::endl;

    // Get operations from program options
    std::vector<std::shared_ptr<Operation>> operations;
    operations.resize(operation_creators.size());
    std::transform(
            operation_creators.begin(),
            operation_creators.end(),
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

    apply(input_file, output_file, operations);
}

void apply(std::string input_file, std::string output_file, std::vector<std::shared_ptr<Operation>> operations) {
    // Read image from file
    cv::Mat image = cv::imread(input_file);

    // Apply operations to image
    std::for_each(operations.begin(), operations.end(), [&image](std::shared_ptr<Operation> operation) {
        operation->apply(image);
    });

    // Save the final image
    cv::imwrite(output_file, image);
}

}
