#pragma once

#include "matrix_filter.h"

class EdgeDetectionFilter : public MatrixFilter
{
public:
    EdgeDetectionFilter(float threshold);
    void Apply(Image& image) const override;

private:
    float threshold_;
};
