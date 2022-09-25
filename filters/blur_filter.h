#pragma once

#include "filter.h"

class BlurFilter : public Filter {
public:
    explicit BlurFilter(float sigma);
    void Apply(Image& image) const override;
    Color CalculateGaussValue(Image& image, size_t x, size_t y) const;

private:
    float sigma_;
};
