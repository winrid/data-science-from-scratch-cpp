#include <iostream>
#include "../common/knn.h"

struct city_favorite_language {
    std::string city;
    double longitude;
    double latitude;
    std::string language;
};

int main() {

    std::vector<city_favorite_language> cities = {};
    cities.push_back((struct city_favorite_language){.city = "Seattle", .longitude = -122.3, .latitude = 47.53, .language = "Python"});
    cities.push_back((struct city_favorite_language){.city = "Austin", .longitude = -96.85, .latitude = 32.85, .language = "Java"});
    cities.push_back((struct city_favorite_language){.city = "Madison", .longitude = -89.33, .latitude = 43.13, .language = "R"});

    std::unordered_map<std::string, std::string> markers = {
            { "Java", "o" },
            { "Python", "s" },
            { "R", "^" }
    };

    std::unordered_map<std::string, std::string> colors = {
            { "Java", "r" },
            { "Python", "b" },
            { "R", "g" }
    };

}
