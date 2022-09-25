#include "grayscale_filter.h"

void GrayscaleFilter::ModifyPixel(Image &image, size_t x, size_t y) const {
    auto [r, g, b] = image.GetColor(x, y);
    auto new_color = r_mod * r + g_mod * g + b_mod * b;
    image.SetColor(x, y, Color(new_color, new_color, new_color));
}
