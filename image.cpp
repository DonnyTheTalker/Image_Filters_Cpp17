#include "image.h"
#include "bmp_format.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>

Image::Image(size_t width, size_t height) {
    Resize(width, height);
}

Color Image::GetColor(size_t x, size_t y) const {
    return pixels_[y][x];
}

void Image::SetColor(size_t x, size_t y, const Color &color) {
    pixels_[y][x] = color;
}

void Image::Clear() {
    width_ = 0;
    height_ = 0;
    pixels_.clear();
}

size_t Image::GetPadding() const {
    return (bmp_format::BYTES_OFFSET - (width_ * bmp_format::COLOR_CHANNELS) % bmp_format::BYTES_OFFSET) %
           bmp_format::BYTES_OFFSET;
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

void Image::SetWidth(size_t value) {
    width_ = value;
}

void Image::SetHeight(size_t value) {
    height_ = value;
}

void Image::Resize(size_t width, size_t height) {
    SetWidth(width);
    SetHeight(height);

    pixels_.resize(height_);
    for (size_t y = 0; y < height_; ++y) {
        pixels_[y].resize(width_);
    }
}
