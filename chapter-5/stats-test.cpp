#include <../common/statistics.h>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> num_friends = {100, 49, 41, 40, 25, 6, 6, 1, 1};
    std::cout << "Median: " << statistics::median(num_friends) << "\n";

    std::cout << "\n";

    std::cout << "Quantile 0.10: " << statistics::quantile(num_friends, 0.10) << "\n";
    std::cout << "Quantile 0.25: " << statistics::quantile(num_friends, 0.25) << "\n";
    std::cout << "Quantile 0.75: " << statistics::quantile(num_friends, 0.75) << "\n";
    std::cout << "Quantile 0.90: " << statistics::quantile(num_friends, 0.90) << "\n";

    std::cout << "\n";

    for (auto mode : statistics::mode(num_friends)) {
        std::cout << "Mode: " << mode << "\n";
    }

    std::cout << "\n";

    std::cout << "Data Range: " << statistics::data_range(num_friends) << "\n";

    std::cout << "\n";

    std::cout << "Variance: " << statistics::variance(num_friends) << "\n";

    std::cout << "\n";

    std::cout << "Standard Deviation: " << statistics::standard_deviation(num_friends) << "\n";

    std::cout << "\n";

    std::cout << "Interquantile Range: " << statistics::interquartile_range(num_friends) << "\n";

    std::cout << "\n";

    std::vector<int> daily_minutes{1000, 490, 410, 400, 250, 60, 60, 10, 10};
    std::cout << "Covariance: " << statistics::covariance(num_friends, daily_minutes) << "\n";

    std::cout << "\n";
    std::cout << "Correlation: " << statistics::correlation(num_friends, daily_minutes) << "\n";
}
