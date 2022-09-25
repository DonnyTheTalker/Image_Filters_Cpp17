#include "negative_filter.h"

void NegativeFilter::ModifyPixel(Image &image, size_t x, size_t y) const {
    auto [r, g, b] = image.GetColor(x, y);
    image.SetColor(x, y, Color(1.0f - r, 1.0f - g, 1.0f - b));
}
