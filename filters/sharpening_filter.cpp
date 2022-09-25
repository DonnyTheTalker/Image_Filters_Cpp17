#include "sharpening_filter.h"

SharpeningFilter::SharpeningFilter()
{
    matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
}
