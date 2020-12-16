#ifndef CHAPTER_16_LOGISTIC_REGRESSION_H
#define CHAPTER_16_LOGISTIC_REGRESSION_H

#include "vectormath.h"

namespace logistic_regression {

    double logistic(double x) {
        return 1.0 / (1 + std::exp(-x));
    }

    double logistic_prime(double x) {
        return logistic(x) * (1 - logistic(x));
    }

    double logistic_log_likelihood_i(const std::vector<double> &x_i, y_i, double beta) {
        if (y_i == 1) {
            return std::log(logistic(vectormath::vector_dot_product(x_i, beta)));
        } else {
            return std::log(1 - logistic(vectormath::vector_dot_product(x_i, beta)));
        }
    }

    double logistic_log_likelihood(std::vector<double> x, std::vector<double> y, double beta) {
        double sum = 0;

        for (int i = 0; i < std::min(x.size(), y.size()); i++) {
            sum += logistic_log_likelihood_i(x[i], y[i], beta);
        }

        return sum;
    }

    double logistic_log_partial_ij(std::vector<double> x_i, double y_i, double beta, double derivativeIndex) {
        return (y_i - logistic(vectormath::vector_dot_product(x_i, beta))) * x_i[derivativeIndex];
    }

    // the gradient of the log likelihood corresponding to the ith data point
    std::vector<double> logistic_log_gradient_i(std::vector<double> x_i, double y_i, std::vector<double> beta) {
        std::vector<double> result;

        for (int i = 0; i < beta.size(); i++) {
            result.push_back(logistic_log_partial_ij(x_i, y_i, beta, j));
        }

        return result;
    }

    std::vector<double> logistic_log_gradient(std::vector<double> x, std::vector<double> y, std::vector<double> beta) {
        std::vector<double> result;

        for (int i = 0; i < std::min(x_i.size(), y_i.size()); i++) {
            auto gradient_vector = logistic_log_gradient_i(x[i], y[i], beta);
            if (result.empty()) {
                result = gradient_vector;
            } else {
                result = vectormath::vector_add(result, gradient_vector);
            }
        }

        return result;
    }

}

#endif //CHAPTER_16_LOGISTIC_REGRESSION_H
