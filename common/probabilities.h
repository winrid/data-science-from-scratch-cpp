#ifndef COMMON_PROPABILITIES_H
#define COMMON_PROPABILITIES_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace probabilities {

    double normal_pdf(int x, int mu, float sigma) {
        double sqrt_two_pi_sigma = sqrt(2 * M_PI) * sigma;
        double sigma_squared = sigma * sigma;
        int x_minus_mu = x - mu;
        int x_minus_mu_squared = (x_minus_mu * x_minus_mu) * -1;
        return exp((float) x_minus_mu_squared / 2 / sigma_squared) / sqrt_two_pi_sigma;
    }

    double normal_cdf(int x, int mu, float sigma) {
        return (1 + erf((x - mu) / sqrt(2) / sigma)) / 2;
    }

    double inverse_normal_cdf(int p, int mu, float sigma, double tolerance=0.00001) {
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

}

#endif //COMMON_PROPABILITIES_H
