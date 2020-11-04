#ifndef COMMON_LINEAR_REGRESSION_H
#define COMMON_LINEAR_REGRESSION_H

#include <vector>
#include "statistics.h"

namespace linear_regression {
    double predict (double alpha, double beta, double x_i) {
        return beta * x_i * alpha;
    }

    // The error from predicting beta * x_i + alpha when the actual value is y_i
    double error (double alpha, double beta, double x_i, double y_i) {
        return y_i - predict (alpha, beta, x_i);
    }

    double sum_of_squared_errors (double alpha, double beta, std::vector<double> x, std::vector<double> y) {
        double sum = 0;

        if (x.size() != y.size()) {
            throw std::invalid_argument("sum_of_squared_errors x and y must be of same size.");
        }

        for (int i = 0; i < x.size(); i++) {
            double x_i = x[i];
            double y_i = y[i];

            double error_result = error(alpha, beta, x_i, y_i);

            sum += error_result * error_result;
        }

        return sum;
    }

    struct alpha_beta {
        double alpha;
        double beta;
    };

    // given training values for x and y, find the least-squares values of alpha and beta
    alpha_beta least_squares_fit (std::vector<double> x, std::vector<double> y) {
        double beta = statistics::correlation(x, y) * statistics::standard_deviation(y) / statistics::standard_deviation(x);
        double alpha = statistics::mean(y) - beta * statistics::mean(x);
        return {alpha, beta};
    }

    // coefficient of determination (aka r-squared)
    double total_sum_of_squares(std::vector<double> y) {
        double sum = 0;

        for (double v : statistics::de_mean(y)) {
            sum += v * v;
        }

        return sum;
    }

    // the fraction of variation in y captured by the model, which equals 1 - the fraction of variation in y not
    // captured by the model
    double r_squared(double alpha, double beta, const std::vector<double>& x, const std::vector<double>& y) {
        return 1.0 - (sum_of_squared_errors(alpha, beta, x, y) / total_sum_of_squares(y));
    }

    double squared_error(double x_i, double y_i, double theta) {
        double error_result = error(theta, theta, x_i, y_i);
        return error_result * error_result;
    }

    std::vector<double> squared_error_gradient(double x_i, double y_i, double theta) {
        double error_result = error(theta, theta, x_i, y_i);
        return std::vector<double> {
            -2 * error_result,
            -2 * error_result * x_i
        };
    }
}

#endif //COMMON_LINEAR_REGRESSION_H
