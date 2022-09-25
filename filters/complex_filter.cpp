#include "complex_filter.h"

void ComplexFilter::Apply(Image &image) const {
    auto width = image.GetWidth();
    auto height = image.GetHeight();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            ModifyPixel(image, x, y);
        }
    }
}