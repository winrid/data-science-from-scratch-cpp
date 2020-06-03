#ifndef COMMON_PROPABILITIES_H
#define COMMON_PROPABILITIES_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

namespace probabilities {

    double normal_pdf(int x, int mu, float sigma) {
        double sqrt_two_pi_sigma = sqrt(2 * M_PI) * sigma;
        double sigma_squared = sigma * sigma;
        int x_minus_mu = x - mu;
        int x_minus_mu_squared = (x_minus_mu * x_minus_mu) * -1;
        return exp((float) x_minus_mu_squared / 2 / sigma_squared) / sqrt_two_pi_sigma;
    }

    double normal_cdf(int x, int mu, float sigma) {
        return (1.0 + erf((x - mu) / sqrt(2) / sigma)) / 2.0;
    }

    double inverse_normal_cdf(float p, int mu, float sigma, double tolerance=0.00001) {
        // if not standard, compute standard and rescale
        if (mu != 0 || sigma != 1) {
            return mu + sigma * inverse_normal_cdf(p, 0, 1, tolerance);
        }

        double low_z = -10.0;
        double hi_z = 10.0;
        double mid_z;
        while (hi_z - low_z > tolerance) {
            mid_z = (low_z + hi_z) / 2;
            double mid_p = normal_cdf((int) mid_z, 0, 1);
            if (mid_p < p) {
                low_z = mid_z;
            }
            else if (mid_p > p) {
                hi_z = mid_z;
            }
            else {
                break;
            }
        }
        return mid_z;
    }

    struct mu_sigma {
        double mu;
        double sigma;
    };

    // Finds mu and sigma corresponding to a Binomial (n, p)
    mu_sigma normal_approximation_to_binomial(int n, double p) {
        double mu = p * n;
        double sigma = std::sqrt(p * (1 - p) * n);
        mu_sigma result{};
        result.mu = mu;
        result.sigma = sigma;
        return result;
    }

    double normal_probability_below(int x, int mu, float sigma) {
        return normal_cdf(x, mu, sigma); // this is just an alias for normal_cdf
    }

    double normal_probability_above(int lo, int mu=0, float sigma = 1) {
        return 1 - normal_cdf(lo, mu, sigma);
    }

    double normal_probability_between(int lo, int hi, int mu = 0, float sigma = 1) {
        return normal_cdf(hi, mu, sigma) - normal_cdf(lo, mu, sigma);
    }

    double normal_probability_outside(int lo, int hi, int mu = 0, float sigma = 1) {
        return 1 - normal_probability_between(lo, hi, mu, sigma);
    }

    // returns the z for which P(Z <= z) = probability
    double normal_upper_bound(float probability, int mu = 0, float sigma = 1) {
        return inverse_normal_cdf(probability, mu, sigma);
    }

    // returns the z for which P(Z >= z) = probability
    double normal_lower_bound(float probability, int mu = 0, float sigma = 1) {
        return inverse_normal_cdf(1.0f - probability, mu, sigma);
    }

    struct upper_lower_bounds {
        double upper_bound;
        double lower_bound;
    };

    // returns the symmetric (about the mean) bounds that contain the specified probability
    upper_lower_bounds normal_two_sided_bounds(float probability, int mu = 0, float sigma = 1) {
        float tail_probability = (1.0f - (float) probability) / 2.0f;
        // Why does the book call normal_lower_bound and call it upper?
        double upper_bound = normal_lower_bound(tail_probability, mu, sigma);
        double lower_bound = normal_upper_bound(tail_probability, mu, sigma);
        upper_lower_bounds result{};
        result.upper_bound = upper_bound;
        result.lower_bound = lower_bound;
        return result;
    }

}

#endif //COMMON_PROPABILITIES_H
