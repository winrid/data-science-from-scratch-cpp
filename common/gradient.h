#ifndef COMMON_GRADIENT_H
#define COMMON_GRADIENT_H

#include <vector>

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

}

#endif //COMMON_GRADIENT_H
