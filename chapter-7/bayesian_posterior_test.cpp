#include <vector>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include "../common/probabilities.h"

namespace plt = matplotlibcpp;

int main() {
    std::vector<double> xs{};
    std::vector<double> beta_4_8 {};
    std::vector<double> beta_23_27 {};
    std::vector<double> beta_33_17 {};

    for(double i = 0.0; i <= 1; i += 0.1) {
        xs.push_back(i);
        beta_4_8.push_back(probabilities::beta_pdf(i, 4, 8));
        beta_23_27.push_back(probabilities::beta_pdf(i, 23, 27));
        beta_33_17.push_back(probabilities::beta_pdf(i, 33, 17));
    }

    plt::xkcd();
    plt::title("Posteriors arising from different priors");
    plt::named_plot("Beta(4, 8)", xs, beta_4_8, "r");
    plt::named_plot("Beta(23, 27)", xs, beta_23_27, "g");
    plt::named_plot("Beta(33, 17)", xs, beta_33_17, "b");
    plt::legend();
    plt::show();
}
