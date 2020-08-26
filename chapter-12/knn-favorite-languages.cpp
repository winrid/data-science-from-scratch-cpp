#include <iostream>
#include "../common/knn.h"

#define WITHOUT_NUMPY 1

#include "../common/matplotlib.h"

namespace plt = matplotlibcpp;

struct city_favorite_language {
    std::string city;
    double longitude;
    double latitude;
    std::string language;
};

int main() {

    std::vector<city_favorite_language> cities = {};
    cities.push_back({"Seattle", -122.3, 47.53, "Python"});
    cities.push_back({"Austin", -96.85, 32.85, "Java"});
    cities.push_back({"Madison", -89.33, 43.13, "R"});

    std::unordered_map<std::string, std::string> markers = {
            {"Java",   "o"},
            {"Python", "s"},
            {"R",      "^"}
    };

    std::unordered_map<std::string, std::string> colors = {
            {"Java",   "r"},
            {"Python", "b"},
            {"R",      "g"}
    };

    plt::title("Favorite Programming Languages");
    plt::xlim(-130, -60);
    plt::ylim(20, 55);
    plt::legend();
    plt::show();
}
