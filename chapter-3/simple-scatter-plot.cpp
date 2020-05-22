#include <iostream>
#include <string>
#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    std::vector<int> friends{70, 65, 72, 63, 71, 64, 60, 64, 67};
    std::vector<int> minutes{175, 170, 205, 120, 220, 130, 105, 145, 190};
    std::vector<std::string> labels{"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    plt::scatter(friends, minutes);

    for (int i = 0; i < friends.size(); i++) {
        plt::annotate(labels[i], friends[i], minutes[i]);
    }

    plt::xlabel("model complexity");
    plt::title("Daily Minutes vs. Number of Friends");

    plt::xkcd();
    plt::show();
}
