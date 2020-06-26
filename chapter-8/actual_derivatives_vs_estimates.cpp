#include <../common/gradient.h>
#include <vector>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"

namespace plt = matplotlibcpp;

int main() {

    std::vector<double> xs;
    std::vector<double> actual;
    std::vector<double> estimate;

    class SquareCallback: public gradient::DoubleCallback {
        double operator() (double f) {
            return gradient::square(f);
        }
    };

    SquareCallback sc {};
    for (int i = -10; i < 11; i++) {
        xs.push_back(i);
        actual.push_back(gradient::derivative(i));
        estimate.push_back(gradient::difference_quotient(&sc, i, 0.00001));
    }

    plt::xkcd();
    plt::named_plot("Actual", xs, actual, "rx");
    plt::named_plot("Estimate", xs, estimate, "b+");
    plt::legend();
    plt::show();
}
