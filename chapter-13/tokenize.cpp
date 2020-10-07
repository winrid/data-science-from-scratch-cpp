#include <set>
#include <iostream>

#include "../common/naive_bayes.h"

int main() {
    std::string message = "this is some gr3t 123456 message, yep. totally is.";
    std::set<std::string> words = naive_bays::tokenize(message);
    for (const std::string& word : words) {
        std::cout << "Match: " << word << "\n";
    }
}
