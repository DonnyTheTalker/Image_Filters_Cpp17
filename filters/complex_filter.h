#pragma once

#include "filter.h"

class ComplexFilter : public Filter
{
public:
    void Apply(Image& image) const override;
    virtual void ModifyPixel(Image& image, size_t x, size_t y) const = 0;
};