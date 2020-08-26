#include <iostream>
#include <fstream>
#include <string>
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

std::vector<std::string> split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

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

    // Draw state outlines.
    std::fstream coordsFile;
    coordsFile.open(R"(C:\Users\winri\Documents\GitHub\data-science-from-scratch-cpp\chapter-11\state-coords.txt)",
                    std::ios::in);
    if (coordsFile.is_open()) {
        std::string line;
        std::vector<double> xa{};
        std::vector<double> ya{};
        std::vector<std::string> lastPoints{};
        while (std::getline(coordsFile, line)) {
            if (line == "NEXTSTATE") {
                plt::plot(xa, ya, "b");
                xa.clear();
                ya.clear();
                lastPoints.clear();
            }
            std::vector<std::string> tokens = split(line, ",");
            if (!lastPoints.empty()) {
                if (lastPoints.size() != tokens.size()) {
                    std::cout << "Skipping: " << line << "\n";
                } else {
                    double lastLat = std::atof(lastPoints[0].c_str());
                    double lastLon = std::atof(lastPoints[1].c_str());
                    double nextLat = std::atof(tokens[0].c_str());
                    double nextLon = std::atof(tokens[1].c_str());
                    ya.push_back(lastLat);
                    ya.push_back(nextLat);
                    xa.push_back(lastLon);
                    xa.push_back(nextLon);
                }
            }
            lastPoints = tokens;
        }
        plt::plot(xa, ya, "b");
    } else {
        std::cout << "Could not open state coords file!";
    }

    plt::title("Favorite Programming Languages");
    plt::xlim(-130, -60);
    plt::ylim(20, 55);
    plt::legend();
    plt::show();
}
