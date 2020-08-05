#include <../common/gradient.h>
#include <../common/vectormath.h>
#include <vector>
#include <iostream>
#include <random>

#define WITHOUT_NUMPY 1

#include "../common/matplotlib.h"
#include "../common/probabilities.h"

namespace plt = matplotlibcpp;

double bucketize(double point, int bucket_size) {
    return bucket_size * std::floor(point / bucket_size);
}

std::unordered_map<double, double> make_histogram(std::vector<double> points, int bucket_size) {
    std::unordered_map<double, double> result;
    for(double point : points) {
        result[bucketize(point, bucket_size)]++;
    }
    return result;
}

void plot_histogram(std::vector<double> points, int bucket_size, std::string title="") {
    auto histogram = make_histogram(points, bucket_size);

    std::vector<double> x(histogram.size());
    std::vector<double> y(histogram.size());

    for (auto kv : histogram) {
        x.push_back(kv.first);
        y.push_back(kv.second);
    }

//    plt::xkcd();
    plt::title(title);
    plt::bar(x, y, "black", "-", bucket_size);
    plt::legend();
    plt::show();
}

int main() {

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distrA(-100, 100); // define the range
    std::uniform_real_distribution<> distrB(0, 1); // define the range

    std::vector<double> uniform{};
    std::vector<double> normal{};
    for (int i = 0; i < 10000; i++) {
        uniform.push_back(distrA(gen));
        normal.push_back(57 * probabilities::inverse_normal_cdf(distrB(gen)));
    }

    plot_histogram(uniform, 10, "Uniform Histogram");
    plot_histogram(normal, 10, "Normal Histogram");
}
