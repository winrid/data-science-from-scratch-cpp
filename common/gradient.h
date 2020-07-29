#ifndef COMMON_GRADIENT_H
#define COMMON_GRADIENT_H

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include "vectormath.h"

namespace gradient {

    class DoubleCallback {
    public:
        virtual double operator()(double f) = 0;
    };

    class DoubleVectorCallbackSingleResult {
    public:
        virtual double operator()(std::vector<double> f) = 0;
    };

    class DoubleVectorCallback {
    public:
        virtual std::vector<double> operator()(std::vector<double> f) = 0;
    };

    double difference_quotient(DoubleCallback *differenceQuotientCallback, double x, double h) {
        return ((*differenceQuotientCallback)(x + h) - (*differenceQuotientCallback)(x)) / h;
    }

    double square(double x) {
        return x * x;
    }

    double derivative(double x) {
        return 2 * x;
    }

//    double partial_difference_quotient(DoubleCallback *f, DoubleCallback *v, double i, double h) {
        // TODO the book doesn't really document what f and v should take or return, and it doesn't
        //  seem this function is used, so I'm not going to finish it until I see an example...
//    }

    template<typename Numeric>
    std::vector<Numeric> step(std::vector<Numeric> v, std::vector<Numeric> direction, Numeric step_size) {
        std::vector<Numeric> result{};
        for (int i = 0; i < v.size(); i++) {
            result.push_back(v[i] + step_size * direction[i]);
        }
        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> sum_of_squares_gradient(std::vector<Numeric> v) {
        std::vector<Numeric> result{};
        for (Numeric v_i : v) {
            result.push_back(2 * v_i);
        }
        return result;
    }

    // use gradient descent to find theta that minimizes target function
    std::vector<double> minimize_batch(DoubleVectorCallbackSingleResult *target_fn, DoubleVectorCallback *gradient_fn, std::vector<double> theta, double tolerance=0.000001) {
        std::vector<double> step_sizes {100, 10, 1, 0.1, 0.01, 0.001, 0.0001, 0.00001};

        // the book wraps the callbacks in a method to check for exceptions and return Infinity, however not sure
        // that is needed.

        double value = (*target_fn)(theta);
        while (true) {
            std::vector<double> gradient = (*gradient_fn)(theta);
            std::vector<double> next_theta_list;
            double lowest = 0;
            bool first = true;
            for (double step_size : step_sizes) {
                std::vector<double> next_thetas = step(theta, gradient, step_size * -1);
                double candidate_target = (*target_fn)(next_thetas);
                if (first || candidate_target < lowest) {
                    first = false;
                    next_theta_list = next_thetas;
                }
            }
            double next_value = (*target_fn)(next_theta_list);

            // stop if we're "converging"
            if (std::abs(value - next_value) < tolerance) {
                return theta;
            } else {
                theta = next_theta_list;
                value = next_value;
            }
        }
    }

    class MinimizeStochasticTargetFn {
    public:
        virtual double operator()(double x_i, double y_i, std::vector<double> theta) = 0;
    };

    class MinimizeStochasticGradientFn {
    public:
        virtual std::vector<double> operator()(double x_i, double y_i, std::vector<double> theta) = 0;
    };

    struct minimize_stochastic_data {
        double x;
        double y;
    };

    // x and y should be the same size vector
    // if you want to "maximize stochastic", just use this and in your callbacks do the negation.
    std::vector<double> minimize_stochastic(MinimizeStochasticTargetFn *target_fn, MinimizeStochasticGradientFn *gradient_fn, std::vector<double> x, std::vector<double> y, std::vector<double> theta_0, double alpha_0=0.01) {
        if (x.size() != y.size()) {
            throw "x and y passed to minimize_stochastic should have the same size";
        }

        short iterations_with_no_improvement = 0;
        double alpha = alpha_0;
        std::vector<double> theta = theta_0;
        std::vector<double> min_theta;
        double min_value = std::numeric_limits<double>::infinity();

        std::vector<minimize_stochastic_data> data;
        for (int i = 0; i < x.size(); i++) {
            minimize_stochastic_data datum{};
            datum.x = x[i];
            datum.y = y[i];
            data.push_back(datum);
        }


	    // get a time-based seed
	    unsigned seed = std::chrono::system_clock::now()
           .time_since_epoch()
           .count();

        while (iterations_with_no_improvement < 100) {
            double value = 0;
            for (int i = 0; i < x.size(); i++) {
                double x_i = x[i];
                double y_i = y[i];
                value += (*target_fn)(x_i, y_i, theta);
            }

            if (value < min_value) {
                // if we've found a new minimum, remember it
                // and go back to the original step size
                min_theta = theta;
                min_value = value;
                iterations_with_no_improvement = 0;
                alpha = alpha_0;
            } else {
                iterations_with_no_improvement++;
                alpha *= 0.9;
            }

            std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));
            for (minimize_stochastic_data datum : data) {
                std::vector<double> gradient_i = (*gradient_fn)(datum.x, datum.y, theta);
                theta = vectormath::vector_subtract(theta, vectormath::vector_scalar_multiply(gradient_i, alpha));
            }
        }

        return min_theta;
    }

}

#endif //COMMON_GRADIENT_H
