#include <iostream>
#include <string>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    std::vector<int> variance{1, 2, 4, 8, 16, 32, 64, 128, 256};
    std::vector<int> bias_squared{256, 128, 64, 32, 18, 8, 4, 2, 1};
    std::vector<int> total_error;
    std::vector<int> xAxis;
    for (int i = 0; i < variance.size(); i++) {
        total_error.push_back(variance[i] + bias_squared[i]);
        xAxis.push_back(i);
    }

    plt::named_plot("variance", xAxis, variance, "g-");
    plt::named_plot("bias^2", xAxis, bias_squared, "r-");
    plt::named_plot("total error", xAxis, total_error, "b:");
    plt::legend();

    plt::xlabel("model complexity");
    plt::title("The Bias-Variance Trade off");

    plt::xkcd();
    plt::show();
}
