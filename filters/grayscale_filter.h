#pragma once

#include "complex_filter.h"

class GrayscaleFilter : public ComplexFilter
{
public:
    void ModifyPixel(Image& image, size_t x, size_t y) const override;

private:
    const float r_mod = 0.299f;
    const float g_mod = 0.587f;
    const float b_mod = 0.114f;
};
