#include "edge_detection_filter.h"
#include "grayscale_filter.h"

EdgeDetectionFilter::EdgeDetectionFilter(float threshold) {
    threshold_ = threshold;
    matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}

void EdgeDetectionFilter::Apply(Image &image) const {
    auto filter = GrayscaleFilter();
    filter.Apply(image);
    MatrixFilter::Apply(image);

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            if (image.GetColor(x, y).r > threshold_) {
                image.SetColor(x, y, Color(1.0f, 1.0f, 1.0f));
            } else {
                image.SetColor(x, y, Color(0.0f, 0.0f, 0.0f));
            }
        }
    }
}
