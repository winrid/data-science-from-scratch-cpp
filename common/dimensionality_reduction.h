#ifndef COMMON_DIM_REDUX
#define COMMON_DIM_REDUX

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include "gradient.h"
#include "vectormath.h"

namespace dimensionality_reduction {

    // what is the direction that captures the greatest variance in a set of data?
    template<typename Numeric>
    std::vector<Numeric> direction(std::vector<Numeric> w) {
        double mag = vectormath::vector_magnitude(w);
        std::vector<Numeric> result;
        for (Numeric value : w) {
            result.push_back(value / mag);
        }
        return result;
    }

    // the variance of the row x_i in the direction determined by w
    template<typename Numeric>
    Numeric directional_variance_i(std::vector<Numeric> x_i, std::vector<Numeric> w) {
        return std::pow(vectormath::vector_dot_product(x_i, direction(w)), 2);
    }

    // the variance of the data in the direction determined by w
    template<typename Numeric>
    std::vector<Numeric> directional_variance(std::vector<std::vector<Numeric>> X, std::vector<Numeric> w) {
        Numeric result = 0;
        for (auto x_i : X) {
            result += directional_variance_i(x_i, w);
        }
        return result;
    }

    // the contribution of row x_i to the gradient of the direction-w variance
    template<typename Numeric>
    std::vector<Numeric> directional_variance_gradient_i(std::vector<Numeric> x_i, std::vector<Numeric> w) {
        float projection_length = vectormath::vector_dot_product(x_i, direction(w));
        std::vector<Numeric> result;
        for (Numeric x_ij : x_i) {
            result.push_back(2 * projection_length * x_ij);
        }
        return result;
    }

    template<typename Numeric>
    Numeric directional_variance_gradient(std::vector<std::vector<Numeric>> X, std::vector<Numeric> w) {
        Numeric result = 0;
        for (auto x_i : X) {
            result += directional_variance_gradient_i(x_i, w);
        }
        return result;
    }

    // maximize the directional_variance function

    template<typename Numeric>
    std::vector<Numeric> first_principal_component(std::vector<std::vector<Numeric>> X) {
        // TODO finish gradient::partial_difference_quotient
    }

    class DirectionalVarianceINegated : public gradient::MinimizeStochasticTargetFn {
        double operator()(std::vector<double> x_i, std::vector<double> y_i, std::vector<double> theta) override {
            return -directional_variance_i(x_i, theta);
        }
    };

    class DirectionalVarianceGradientINegated : public gradient::MinimizeStochasticGradientFn {
        std::vector<double>
        operator()(std::vector<double> x_i, std::vector<double> y_i, std::vector<double> theta) override {
            std::vector<double> result = directional_variance_gradient_i(x_i, theta);
            for (int i = 0; i < result.size(); i++) {
                result[i] = -result[i];
            }
            return result;
        }
    };

    template<typename Numeric>
    std::vector<Numeric> first_principal_component_sgd(std::vector<std::vector<Numeric>> X) {
        std::vector<double> guess;
        std::vector<std::vector<double>> fakeY;
        for (auto _ : X) {
            guess.push_back(1);
            fakeY.push_back(nullptr);
        }
        DirectionalVarianceINegated directionalVarianceINegated{};
        DirectionalVarianceGradientINegated directionalVarianceGradientINegated{};
        std::vector<double> unscaled_maximized = gradient::minimize_stochastic(&directionalVarianceINegated,
                                                                               &directionalVarianceGradientINegated, X, fakeY,
                                                                               guess);
        return direction(unscaled_maximized);
    }

    template<typename Numeric>
    std::vector<Numeric> project(std::vector<Numeric> v, std::vector<Numeric> w) {
        // return the projection of v onto the direction w
        return vectormath::vector_scalar_multiply(vectormath::vector_dot_product(v, w), w);
    }

    template<typename Numeric>
    std::vector<Numeric> remove_projection_from_vector(std::vector<Numeric> v, std::vector<Numeric> w) {
        // projects v onto w and subtracts the result from v
        return vectormath::vector_subtract(v, project(v, w));
    }

    template<typename Numeric>
    std::vector<Numeric> remove_projection(std::vector<std::vector<Numeric>> X, std::vector<Numeric> w) {
        // for each row of X projects the row into w, and subtracts the result from the row
        std::vector<std::vector<Numeric>> result;
        for (std::vector<Numeric> x_i : X) {
            result.push_back(remove_projection_from_vector(x_i, w));
        }
        return result;
    }

    template<typename Numeric>
    std::vector<std::vector<Numeric>> principal_component_analysis(std::vector<std::vector<Numeric>> X, int num_components) {
        std::vector<std::vector<Numeric>> components;
        for (int i = 0; i < num_components; i++) {
            auto component = first_principal_component(X);
            components.push_back(component);
            X = remove_projection(x, component);
        }
        return components;
    }

    template<typename Numeric>
    std::vector<Numeric> transform_vector(std::vector<Numeric> v, std::vector<std::vector<Numeric>> components) {
        std::vector<Numeric> result;
        for (std::vector<Numeric> w : components) {
            result.push_back(vectormath::vector_dot_product(v, w));
        }
        return result;
    }

    template<typename Numeric>
    std::vector<std::vector<Numeric>> transform(std::vector<std::vector<Numeric>> X, std::vector<std::vector<Numeric>> components) {
        std::vector<std::vector<Numeric>> result;
        for (std::vector<Numeric> x_i : X) {
            result.push_back(transform_vector(x_i, components));
        }
        return result;
    }

}

#endif //COMMON_DIM_REDUX
