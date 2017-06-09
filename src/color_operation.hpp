#ifndef COLOR_OPERATIONS_COLOR_OPERATION_H
#define COLOR_OPERATIONS_COLOR_OPERATION_H

#include <string>
#include <opencv2/core/mat.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/optional.hpp>

namespace color_operations {

struct ParameterBase {};

template <typename ParameterType, typename ParametersParser, char const *_name>
class ColorOperation {
public:
    constexpr static char const *name = _name;

    typedef ParametersParser parameters_parser;

    virtual void apply(const ParameterType &parameters, cv::Mat &image) = 0;

    void add_cli_arguments(boost::program_options::options_description &description) {
        ParametersParser::add_cli_arguments(description);
    }

    boost::optional<const ParameterType> parse_arguments(const boost::program_options::variables_map &arguments) {
        return ParametersParser::parse_arguments(arguments);
    }
};

}

#endif //COLOR_OPERATIONS_COLOR_OPERATION_H
