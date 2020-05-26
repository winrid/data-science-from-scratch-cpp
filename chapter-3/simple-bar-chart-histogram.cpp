#include <iostream>
#include <string>
#include <unordered_map>

#define WITHOUT_NUMPY 1
#include "../common/matplotlib.h"
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    std::vector<int> grades{83, 95, 91, 87, 70, 0, 85, 82, 100, 67, 73, 77, 0};
    std::vector<int> xAxis;
    std::unordered_map<int, int> countByGradeLevel = {};
    for (int i = 0; i < grades.size(); i++) {
        int normalizedGradeLevel = (int) (std::floor(grades[i] / 10) * 10);
        countByGradeLevel[normalizedGradeLevel]++;
    }

    std::vector<int> yAxis;
    for (const auto & [key, value] : countByGradeLevel) {
        xAxis.push_back(key);
        yAxis.push_back(value);
    }

    plt::bar(xAxis, yAxis, "black", "-", 16.0, {});

    std::vector<int> ticks;
    for (int i = 0; i < 11; i++) {
        ticks.push_back(i * 10);
    }
    plt::xticks(ticks);

    plt::xlabel("Decile");
    plt::ylabel("# of Students");
    plt::title("Distribution of Exam 1 Grades");

    plt::xkcd();
    plt::show();
}
