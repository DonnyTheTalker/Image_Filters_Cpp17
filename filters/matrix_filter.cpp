#include "matrix_filter.h"
#include <iostream>

Color MatrixFilter::CalculateWeightedSum(const Image &image, size_t x, size_t y) const {
    std::vector<float> cur_colors = {0, 0, 0};

    x += 1;
    y += 1;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            size_t cur_y = y + dy;
            size_t cur_x = x + dx;

            if (cur_y > 0 && cur_y <= image.GetHeight() && cur_x > 0 && cur_x <= image.GetWidth()) {
                auto [r, g, b] = image.GetColor(cur_x - 1, cur_y - 1);
                std::vector<float> new_colors{r, g, b};

                for (size_t i = 0; i < 3; ++i) {
                    cur_colors[i] += new_colors[i] * matrix_[dy + 1][dx + 1];
                }
            }
        }
    }

    for (size_t i = 0; i < 3; ++i) {
        cur_colors[i] = std::min(1.0f, std::max(0.0f, cur_colors[i]));
    }

    return Color(cur_colors[0], cur_colors[1], cur_colors[2]);
}

void MatrixFilter::Apply(Image &image) const {
    Image copy = image;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetColor(x, y, CalculateWeightedSum(copy, x, y));
        }
    }
}
