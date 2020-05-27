#include <../common/probabilities.h>
#include <vector>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"

namespace plt = matplotlibcpp;

int main() {
    std::vector<double> sigma_1;
    std::vector<double> sigma_2;
    std::vector<double> sigma_0_5;
    std::vector<double> sigma_1_mu_ne1;

    std::vector<double> xs;

    for (int i = -50; i <= 50; i++) {
        int x = i / 10;
        xs.push_back(x);
        sigma_1.push_back(probabilities::normal_pdf(x, 0, 1));
        sigma_2.push_back(probabilities::normal_pdf(x, 0, 2));
        sigma_0_5.push_back(probabilities::normal_pdf(x, 0, 0.5));
        sigma_1_mu_ne1.push_back(probabilities::normal_pdf(x, -1, 1));
    }

    plt::xkcd();
    plt::named_plot("mu=0, sigma=1", xs, sigma_1, "r");
    plt::named_plot("mu=0, sigma=2", xs, sigma_2, "g");
    plt::named_plot("mu=0, sigma=0.5", xs, sigma_0_5, "b");
    plt::named_plot("mu=-1, sigma=1", xs, sigma_1_mu_ne1, "y");
    plt::legend();
    plt::show();
}
