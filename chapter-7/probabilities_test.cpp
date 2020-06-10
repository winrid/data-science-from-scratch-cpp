#include <iostream>
#include <ctime>
#include "../common/probabilities.h"

int main() {
    probabilities::mu_sigma approximation = probabilities::normal_approximation_to_binomial(1000, 0.5);
    std::cout << "Mu (p=0.5): " << approximation.mu << " Sigma (p=0.5): " << approximation.sigma;

    probabilities::upper_lower_bounds bounds = probabilities::normal_two_sided_bounds(0.95, approximation.mu, approximation.sigma);

    std::cout << "\n";
    std::cout << "Lower bound: " << bounds.lower_bound << " Upper bound: " << bounds.upper_bound;

    // 95% bounds based on assumption p is 0.5
    // bounds_95, like windows 95 except data science
    probabilities::upper_lower_bounds bounds_95 = probabilities::normal_two_sided_bounds(0.95, approximation.mu, approximation.sigma);

    std::cout << "\n";
    std::cout << "Lower bound (95%): " << bounds_95.lower_bound << " Upper Bound (95%) " << bounds_95.upper_bound;

    // actual mu and sigma based on p = 0.55
    probabilities::mu_sigma approx_55 = probabilities::normal_approximation_to_binomial(1000, 0.55);

    std::cout << "\n";
    std::cout << "Mu (p=0.55): " << approx_55.mu << " Sigma (p=0.55): " << approx_55.sigma;

    double type_2_probability = probabilities::normal_probability_between(bounds_95.lower_bound, bounds_95.upper_bound, approx_55.mu, approx_55.sigma);
    double power = 1 - type_2_probability;

    std::cout << "\n";
    std::cout << "Power: " << power;

    double hi = probabilities::normal_upper_bound(0.95, approximation.mu, approximation.sigma);

    std::cout << "\n";
    std::cout << "Upper bound (hi): " << hi; // should be 526

    double type_2_probability_below = probabilities::normal_probability_below(hi, approx_55.mu, approx_55.sigma);
    double power2 = 1 - type_2_probability_below;

    std::cout << "\n";
    std::cout << "Power: " << power2; // TODO BUG should be 0.936. is 0.886

    std::cout << "\n";
    std::cout << " _value for 529.5: " << probabilities::two_sided_p_value(529.5, approximation.mu, approximation.sigma); // 0.06
    std::cout << "\n";
    std::cout << "two_sided_p_value for 531.5: " << probabilities::two_sided_p_value(531.5, approximation.mu, approximation.sigma); // TODO WRONG, SHOULD BE 0.0463
    std::cout << "\n";
    std::cout << "two_sided_p_value for 524.5: " << probabilities::two_sided_p_value(524.5, approximation.mu, approximation.sigma); // TODO WRONG, SHOULD BE0.061
    std::cout << "\n";
    std::cout << "two_sided_p_value for 526.5: " << probabilities::two_sided_p_value(526.5, approximation.mu, approximation.sigma); // TODO WRONG, SHOULD BE 0.047

    int extreme_value_count = 0;
    srand((unsigned) time(0));
    for (int i = 0; i <= 100000; i++) {
        int num_heads = 0;
        for (int flip = 0; flip <= 1000; flip++) {
            if (((float) std::rand()) / ((float) RAND_MAX) < 0.5) {
                num_heads++;
            }
        }
        if (num_heads >= 530 || num_heads <= 470) {
            extreme_value_count++;
        }
    }

    std::cout << "\n";
    std::cout << "Extreme Value Ratio: " << (float) ((float) extreme_value_count / 100000.0f); // should be ~0.062

    /*
     * for example, if "tastes great" gets 200 clicks out of 1000 views and "less bias" gets 180 clicks out of 1000
     * views, the statistic equals -1.14.
     */
    float a_b_test = probabilities::a_b_test_statistic(1000, 200, 1000, 180);
    std::cout << "\n";
    std::cout << "a_b_test_statistic: " << a_b_test; // should be -1.14

    // The probability of seeing such a large difference if the means were actually equal would be 0.254.
    std::cout << "\n";
    std::cout << "two_sided_p_value: " << probabilities::two_sided_p_value(a_b_test); // should be ~0.254

    /*
     * and 0.254 is large enough that we can't conclude there's much of a difference. On the other hand, if "less bias".
     * On the other hand, if "less bias" only got 150 clicks we'd have -2.94 and 0.003.
     */
    a_b_test = probabilities::a_b_test_statistic(1000, 200, 1000, 150);
    std::cout << "\n";
    std::cout << "a_b_test_statistic: " << a_b_test; // should be -2.94

    // The probability of seeing such a large difference if the means were actually equal would be 0.003.
    std::cout << "\n";
    std::cout << "two_sided_p_value: " << probabilities::two_sided_p_value(a_b_test); // should be ~0.003. TODO why getting 0.045?

    // which means there's only a 0.003 probability you'd see such a large difference if the ads were equally effective.
}
