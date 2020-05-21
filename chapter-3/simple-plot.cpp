#include <iostream>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    std::vector<int> years{1950, 1960, 1970, 1980, 1990, 2000, 2010};
    std::vector<float> gdp{300.2, 543.3, 1075.9, 2862.5, 5979.6, 10289.7, 14958.3};

    plt::xkcd();
    plt::plot(years, gdp, "go");
    plt::show();
}
