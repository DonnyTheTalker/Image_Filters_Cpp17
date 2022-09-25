#pragma once

#include "color.h"
#include <string>
#include <vector>

class Image
{
public:
    explicit Image(size_t width = 0, size_t height = 0);
    ~Image() = default;

    void Clear();

    Color GetColor(size_t x, size_t y) const;
    size_t GetPadding() const;
    size_t GetWidth() const;
    size_t GetHeight() const;

    void SetColor(size_t x, size_t y, const Color& color);
    void SetWidth(size_t value);
    void SetHeight(size_t value);
    void Resize(size_t width, size_t height);

private:
    size_t width_;
    size_t height_;
    std::vector<std::vector<Color>> pixels_;
};