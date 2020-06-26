#include <../common/gradient.h>
#include <../common/vectormath.h>
#include <vector>
#include <iostream>
#include <random>

#define WITHOUT_NUMPY 1

#include "../common/matplotlib.h"

namespace plt = matplotlibcpp;

int main() {

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-10, 10); // define the range

    std::vector<double> v{};
    for (int i = 0; i < 4; i++) {
        v.push_back(distr(gen));
    }

    double tolerance = 0.0000001; // the smaller you make this, the closer the items in v will be to zero at the end.
    while (true) {
        std::vector<double> gradient = gradient::sum_of_squares_gradient(v);
        std::vector<double> next_v = gradient::step(v, gradient, -0.01);
        if (vectormath::vector_distance(next_v, v) < tolerance) {
            break;
        }
        v = next_v;
    }
    for (double v_i : v) {
        std::cout << v_i << " ";
    }
}
