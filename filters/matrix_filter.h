#pragma once

#include "complex_filter.h"

class MatrixFilter : public Filter
{
public:
    void Apply(Image& image) const override;
    Color CalculateWeightedSum(const Image& image, size_t x, size_t y) const;

protected:
    std::vector<std::vector<float>> matrix_ = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
};
