#include "crop_filter.h"

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

void CropFilter::Apply(Image &image) const {
    auto old_width = image.GetWidth();
    auto old_height = image.GetHeight();

    auto new_width = std::min(width_, old_width);
    auto new_height = std::min(height_, old_height);

    size_t offset = old_height - new_height;

    for (size_t y = offset; y < old_height; ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            image.SetColor(x, y - offset, image.GetColor(x, y));
        }
    }

    image.Resize(new_width, new_height);
}
