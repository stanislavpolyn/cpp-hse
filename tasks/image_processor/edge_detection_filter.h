#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>

#include "filter.h"
#include "grayscale_filter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold) : threshold_{threshold} {
    }
    void Apply(Image& image) override;

protected:
    static constexpr double FILTER_MATRIX[3][3] = {// NOLINT
                                                   {0.0, -1.0, 0.0},
                                                   {-1.0, 4.0, -1.0},
                                                   {0.0, -1.0, 0.0}};
    double threshold_;
};

Filter* ProduceEdgeDetectionFilter(const FilterSettings& filter_settings);