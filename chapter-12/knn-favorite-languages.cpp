#include <iostream>
#include <fstream>
#include <string>
#include "../common/knn.h"

#define WITHOUT_NUMPY 1

#include "../common/matplotlib.h"

namespace plt = matplotlibcpp;

struct language_config {
    std::string language;
    std::string color;
    std::string marker;
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

bool RENDER_TEST = false;
int NEIGHBORS = 1;

int main() {

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

    std::cout << "Setup chart outlines...\n";

    std::vector<knn::point> markers = {};
    std::vector<knn::point> cities = {};
    cities.push_back({-122.3, 47.53, "Python"}); // "Seattle"
    cities.push_back({-96.85, 32.85, "Java"}); // "Austin"
    cities.push_back({-89.33, 43.13, "R"}); // "Madison"

    std::vector<language_config> languages{
            {"Python", "b", "s"},
            {"Java",   "r", "o"},
            {"R",      "g", "^"},
    };

    if (RENDER_TEST) {
        for (const knn::point& city : cities) {
            markers.push_back({city.longitude, city.latitude, city.label});
        }
    } else {
        std::cout << "Doing prediction...\n";
        for (int longitude = -130; longitude <= -60; longitude++) {
            for (int latitude = 20; latitude <= 55; latitude++) {
                std::string predicted_language = knn::classify(NEIGHBORS, cities, {
                        (double) longitude, (double) latitude, ""
                });
//                std::cout << "Predicted " << predicted_language << " at " << longitude << " " << latitude << "\n";
                markers.push_back({(double) longitude, (double) latitude, predicted_language});
            }
        }
        std::cout << "Prediction done...\n";
    }

    for (const language_config &languageConfig : languages) {
        std::vector<double> x{};
        std::vector<double> y{};
        for (const knn::point &cityFavoriteLanguage : cities) {
            if (languageConfig.language == cityFavoriteLanguage.label) {
                x.push_back(cityFavoriteLanguage.longitude);
                y.push_back(cityFavoriteLanguage.latitude);
            }
        }
        for (const knn::point &marker : markers) {
            if (languageConfig.language == marker.label) {
                x.push_back(marker.longitude);
                y.push_back(marker.latitude);
            }
        }
        plt::named_plot(languageConfig.language, x, y, languageConfig.color + languageConfig.marker);

    }
    std::cout << "Done with plots...";

    plt::title("Favorite Programming Languages");
    plt::xlim(-130, -60);
    plt::ylim(20, 55);
    plt::legend();
    plt::show();
}
