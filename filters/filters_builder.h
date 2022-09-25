#pragma once

#include "../args_parser.h"
#include "filter.h"

#include <memory>
#include <vector>

#include "complex_filter.h"
#include "crop_filter.h"
#include "edge_detection_filter.h"
#include "grayscale_filter.h"
#include "matrix_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "blur_filter.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace FiltersBuilder {
void create_crop_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

void create_grayscale_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

void create_negative_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

void create_sharpening_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

void create_edge_detection_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

void create_blur_filter(ArgsParser &parser, std::unique_ptr<Filter> &result);

std::unordered_map<std::string, std::function<void(ArgsParser &, std::unique_ptr<Filter> &)>> get_filters() {
    return {{"-crop", create_crop_filter},           {"-gs", create_grayscale_filter},
            {"-neg", create_negative_filter},        {"-sharp", create_sharpening_filter},
            {"-edge", create_edge_detection_filter}, {"-blur", create_blur_filter}};
}
}  // namespace FiltersBuilder

namespace FiltersBuilder {
void Build(ArgsParser &parser, std::vector<std::unique_ptr<Filter>> &result) {
    auto filters = get_filters();
    while (!parser.IsOver()) {
        auto filter_name = parser.GetArgument<std::string>();
        std::unique_ptr<Filter> filter;

        auto it = filters.find(filter_name);
        if (it == filters.end()) {
            std::string error_msg = "Invalid filter name " + filter_name;
            throw std::invalid_argument(error_msg.c_str());
        }

        try {
            it->second(parser, filter);
            result.push_back(std::move(filter));
        } catch (const std::exception &ex) {
            std::string error_msg = "Invalid " + filter_name + " filter arguments";
            throw std::invalid_argument(error_msg.c_str());
        }
    }
}
}  // namespace FiltersBuilder

namespace FiltersBuilder {
void create_crop_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    auto width = parser.GetArgument<size_t>();
    auto height = parser.GetArgument<size_t>();
    result = std::move(std::make_unique<CropFilter>(width, height));
}

void create_grayscale_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    result = std::move(std::make_unique<GrayscaleFilter>());
}

void create_negative_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    result = std::move(std::make_unique<NegativeFilter>());
}

void create_sharpening_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    result = std::move(std::make_unique<SharpeningFilter>());
}

void create_edge_detection_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    auto threshold = parser.GetArgument<float>();
    result = std::move(std::make_unique<EdgeDetectionFilter>(threshold));
}

void create_blur_filter(ArgsParser &parser, std::unique_ptr<Filter> &result) {
    auto sigma = parser.GetArgument<float>();
    result = std::move(std::make_unique<BlurFilter>(sigma));
}
}  // namespace FiltersBuilder
