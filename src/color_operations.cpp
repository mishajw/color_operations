#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "color_operations.hpp"
#include "brightness_operation.hpp"
#include "matrix_operation.hpp"
#include "random_operation.hpp"

namespace color_operations {

const std::vector<std::shared_ptr<OperationProgramOptionsCreator>> operation_creators = {
        std::make_shared<BrightnessProgramOptionsCreator>(),
        std::make_shared<MatrixProgramOptionsCreator>(),
        std::make_shared<RandomProgramOptionsCreator>()
};

void add_operations_program_options(boost::program_options::options_description &options_description) {
    std::for_each(
            operation_creators.begin(),
            operation_creators.end(),
            [&options_description](std::shared_ptr<OperationProgramOptionsCreator> creator) {
                creator->add_program_options(options_description);
            });
}

std::vector<std::shared_ptr<Operation>> get_operations_from_program_options(
        const boost::program_options::variables_map &variables_map) {

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

    return operations;
}

void apply(
        const std::string &input_file,
        const std::string &output_file,
        const std::vector<std::shared_ptr<Operation>> &operations) {

    cv::Mat image;

    // Read image from file
    try {
        image = cv::imread(input_file);
    } catch (const cv::Exception &e) {
        std::cerr << "Can't open file " << input_file << ": " << e.what() << std::endl;
        return;
    }

    const std::string image_name = boost::filesystem::path(input_file).filename().string();
    apply(image, operations, image_name);

    // Save the final image
    try {
        boost::filesystem::create_directories(boost::filesystem::path(output_file).parent_path());
        cv::imwrite(output_file, image);
    } catch (const cv::Exception &e) {
        std::cerr << "Can't write to file " << output_file << ": " << e.what() << std::endl;
    }
}

void apply(cv::Mat &image, const std::vector<std::shared_ptr<Operation>> &operations, const std::string &image_name) {
    for (const auto &operation : operations) {
        operation->apply(image, image_name);
    }
}

}
