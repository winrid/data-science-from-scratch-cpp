#include <vector>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include "../common/probabilities.h"

namespace plt = matplotlibcpp;

int main() {
    std::vector<double> xs{};
    std::vector<double> beta_1_1{};
    std::vector<double> beta_10_10{};
    std::vector<double> beta_4_16{};
    std::vector<double> beta_16_4{};

    for (double i = 0.0; i <= 1; i += 0.1) {
        xs.push_back(i);
        beta_1_1.push_back(probabilities::beta_pdf(i, 1, 1));
        beta_10_10.push_back(probabilities::beta_pdf(i, 10, 10));
        beta_4_16.push_back(probabilities::beta_pdf(i, 4, 16));
        beta_16_4.push_back(probabilities::beta_pdf(i, 16, 4));
    }

    plt::xkcd();
    plt::title("Example Beta distributions");
    plt::named_plot("Beta(1, 1)", xs, beta_1_1, "r");
    plt::named_plot("Beta(10, 10)", xs, beta_10_10, "g");
    plt::named_plot("Beta(4, 16)", xs, beta_4_16, "b");
    plt::named_plot("Beta(16, 4)", xs, beta_16_4, "grey");
    plt::legend();
    plt::show();
}
