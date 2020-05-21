#include <iostream>
#include <string>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    std::vector<std::string> movies{"Annie Hall", "Ben-Hur", "Casablanca", "Gandhi", "West Side Story"};
    std::vector<float> num_oscars{5, 11, 3, 8, 10};

    std::vector<float> xs;
    for (int i = 0; i < movies.size(); i++) {
        xs.push_back(i + 0.1);
    }
    plt::bar(xs, num_oscars, "black", "-", 1.0, {});
    plt::xticks(xs, movies);

    plt::ylabel("# of Academy Awards");
    plt::title("My Favorite Movies");
    
    plt::xkcd();
    plt::show();
}
