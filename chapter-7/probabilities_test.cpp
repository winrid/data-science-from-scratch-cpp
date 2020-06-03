#include <iostream>
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
}
