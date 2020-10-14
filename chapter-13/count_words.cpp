#include <iostream>

#include "../common/naive_bayes.h"

int main() {
    std::vector<naive_bays::training_item> training_items {
            {"some good words", naive_bays::classification::GOOD},
            {"some bad words", naive_bays::classification::BAD},
            {"very bad!", naive_bays::classification::BAD}
    };
    std::map<std::string, std::map<naive_bays::classification, int>> words_counted = naive_bays::count_words(training_items);
    for (std::pair<std::string, std::map<naive_bays::classification, int>> word_pair : words_counted) {
        for (std::pair<naive_bays::classification, int> classification_pair : word_pair.second) {
            std::cout
            << word_pair.first
            << " is "
            << (classification_pair.first == naive_bays::classification::GOOD ? "good" : "bad") << " "
            << classification_pair.second
            << " times.\n";
        }
    }
}
