#ifndef COMMON_NAIVE_BAYES_H
#define COMMON_NAIVE_BAYES_H

#include <set>
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>

namespace naive_bays {

    struct training_item {
        std::string value;
        bool is_bad;
    };

    std::set<std::string> tokenize(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        std::set<std::string> result;
        std::regex word_regex("[a-z0-9]+");
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            result.insert(match.str());
        }
        return result;
    }

}

#endif //COMMON_NAIVE_BAYES_H
