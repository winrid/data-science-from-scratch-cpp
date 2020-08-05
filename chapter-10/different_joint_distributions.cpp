#include <../common/gradient.h>
#include <../common/vectormath.h>
#include <vector>
#include <iostream>
#include <random>

#define WITHOUT_NUMPY 1

#include "../common/matplotlib.h"
#include "../common/probabilities.h"
#include "../common/statistics.h"

namespace plt = matplotlibcpp;

int main() {

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(0, 1); // define the range

    std::vector<double> xs{};
    std::vector<double> ys1{};
    std::vector<double> ys2{};
    for (int i = 0; i < 10000; i++) {
        double xRandom = probabilities::inverse_normal_cdf(distr(gen));
        xs.push_back(xRandom);
        ys1.push_back(xRandom + probabilities::inverse_normal_cdf(distr(gen)) / 2);
        ys2.push_back(-xRandom + probabilities::inverse_normal_cdf(distr(gen)) / 2);
    }

    std::cout << statistics::correlation(xs, ys1) << "\n";
    std::cout << statistics::correlation(xs, ys2) << "\n";

    plt::xkcd();
    plt::scatter(xs, ys1);
    plt::scatter(xs, ys2);
    plt::xlabel("xs");
    plt::ylabel("ys");
    plt::title("Very Different Join Distributions");
    plt::legend();
    plt::show();
}
