#ifndef CHAPTER_13_MULTIPLE_REGRESSION_H
#define CHAPTER_13_MULTIPLE_REGRESSION_H

#include <utility>
#include <vector>
#include "gradient.h"
#include "probabilities.h"
#include "vectormath.h"

namespace multiple_regression {

    // assumes that the first element of each x_i is 1
    template<typename Numeric>
    Numeric predict(std::vector<Numeric> x_i, std::vector<Numeric> beta) {
        return vectormath::vector_dot_product(x_i, beta);
    }

    template<typename Numeric>
    Numeric error(std::vector<Numeric> x_i, Numeric y_i, std::vector<Numeric> beta) {
        return y_i - predict(x_i, beta);
    }

    template<typename Numeric>
    Numeric squared_error(std::vector<Numeric> x_i, Numeric y_i, std::vector<Numeric> beta) {
        double error_result = error(x_i, y_i, beta);
        return error_result * error_result;
    }

    template<typename Numeric>
    std::vector<Numeric> squared_error_gradient(std::vector<Numeric> x_i, Numeric y_i, std::vector<Numeric> beta) {
        std::vector<Numeric> result(x_i.size());

        for (Numeric x_ij : x_i) {
            result.push_back(-2.0 * x_ij * error(x_i, y_i, beta));
        }

        return result;
    }

    class SquaredError : public gradient::MinimizeStochasticTargetFn {
        double operator()(std::vector<double> x_i, std::vector<double> y_i, std::vector<double> theta) override {
            return squared_error(x_i, y_i[0], theta);
        }
    };

    class SquaredErrorGradient : public gradient::MinimizeStochasticGradientFn {
        std::vector<double>
        operator()(std::vector<double> x_i, std::vector<double> y_i, std::vector<double> theta) override {
            return squared_error_gradient(x_i, y_i[0], theta);
        }
    };

    std::vector<double> estimate_beta(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y) {
        SquaredError squaredError{};
        SquaredErrorGradient squaredErrorGradient{};

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_real_distribution<> distr(0, 1); // define the range

        std::vector<double> beta_initial;
        for (double x_i : x[0]) {
            beta_initial.push_back(distr(gen));
        }

        return gradient::minimize_stochastic(&squaredError, &squaredErrorGradient, x, std::move(y), beta_initial, 0.001);
    }

    double multiple_r_squared(std::vector<double> x, std::vector<double> y, std::vector<double> beta) {
        // TODO seems like y is a list, but that doesn't make sense when it's supposed to call error() on page 183...
        return 0;
    }

    // randomly samples len(data) elements with replacement
    std::vector<std::vector<double>> bootstrap_sample(std::vector<std::vector<double>> data) { // get a time-based seed
	    unsigned seed = std::chrono::system_clock::now()
           .time_since_epoch()
           .count();
	    std::vector<std::vector<double>> new_list(std::move(data));
        std::shuffle(new_list.begin(), new_list.end(), std::default_random_engine(seed));
        return new_list;
    }

    class BootstrapStatisticStatsFn {
    public:
        virtual double operator()(std::vector<std::vector<double>> data) = 0;
    };

    // evaluates stats_fn on num_samples bootstrap samples from data
    std::vector<double> bootstrap_statistic(const std::vector<std::vector<double>>& data, BootstrapStatisticStatsFn *stats_fn, int num_samples) {
        std::vector<double> result;

        for (int i = 0; i <= num_samples; i++) {
            result.push_back((*stats_fn)(bootstrap_sample(data)));
        }

        return result;
    }

    std::vector<double> estimate_sample_beta(const std::vector<std::vector<double>>& sample) {
        std::vector<std::vector<double>> x_sample;
        std::vector<std::vector<double>> y_sample;

        for (std::vector<double> item : sample) {
            std::vector<double> x;
            std::vector<double> y;
            x.push_back(item[0]);
            y.push_back(item[1]);
            x_sample.push_back(x);
            y_sample.push_back(y);
        }

        return estimate_beta(x_sample, y_sample);
    }

    double p_value(double beta_hat_j, double sigma_hat_j) {
        if (beta_hat_j > 0) {
            // if hte coefficient is positive, we need to compute twice the probability of seeing an even *larger* value
            return 2.0 * (1.0 - probabilities::normal_cdf(beta_hat_j / sigma_hat_j));
        } else {
            return 2.0 * probabilities::normal_cdf(beta_hat_j / sigma_hat_j);
        }
    }

}

#endif //CHAPTER_13_MULTIPLE_REGRESSION_H
