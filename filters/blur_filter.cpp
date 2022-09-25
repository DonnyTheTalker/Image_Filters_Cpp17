#include "blur_filter.h"

#define _USE_MATH_DEFINES

#include <cmath>

BlurFilter::BlurFilter(float sigma) : sigma_(sigma) {
}

void BlurFilter::Apply(Image &image) const {
    Image copy = image;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetColor(x, y, CalculateGaussValue(copy, x, y));
        }
    }
}

Color BlurFilter::CalculateGaussValue(Image &image, size_t x, size_t y) const {
    std::vector<float> new_color_values = {0, 0, 0};

    size_t start_y = static_cast<size_t>(std::max(0.0, y * 1.0 - 2 * sigma_ - 2));
    size_t end_y = static_cast<size_t>(std::min(image.GetHeight() * 1.0, y * 1.0 + 2 * sigma_ + 2));

    size_t start_x = static_cast<size_t>(std::max(0.0, x * 1.0 - 2 * sigma_ - 2));
    size_t end_x = static_cast<size_t>(std::min(image.GetWidth() * 1.0, x * 1.0 + 2 * sigma_ + 2));

    for (size_t y1 = start_y; y1 < end_y; ++y1) {
        for (size_t x1 = start_x; x1 < end_x; ++x1) {
            auto [r, g, b] = image.GetColor(x1, y1);
            std::vector<float> colors = {r, g, b};

            for (size_t i = 0; i < 3; ++i) {
                new_color_values[i] +=
                    colors[i] *
                    pow(M_E, -((pow(x * 1.0 - x1 * 1.0, 2) + pow(y * 1.0 - y1 * 1.0, 2)) / (2 * pow(sigma_, 2))));
            }
        }
    }

    for (size_t i = 0; i < 3; ++i) {
        new_color_values[i] *= (1.0 / (2 * M_PI * pow(sigma_, 2)));
        new_color_values[i] = std::max(0.0f, std::min(1.0f, new_color_values[i]));
    }

    return Color(new_color_values[0], new_color_values[1], new_color_values[2]);
}
