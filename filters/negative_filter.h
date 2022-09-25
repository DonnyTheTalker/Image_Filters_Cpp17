#pragma once

#include "complex_filter.h"

class NegativeFilter : public ComplexFilter {
public:
    void ModifyPixel(Image& image, size_t x, size_t y) const override;
};