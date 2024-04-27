#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

std::string getRandomElement(const std::vector<std::string>& strings) {
    if (strings.empty()) {
        return ""; // Return empty string if the input vector is empty
    }

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    int randomIndex = rand() % strings.size(); // Generate a random index within the vector size

    return strings[randomIndex];
}

int main() {
    std::vector<std::string> words = {"apple", "banana", "cherry", "orange", "pear"};

    std::string randomWord = getRandomElement(words);

    if (!randomWord.empty()) {
        std::cout << "Random word: " << randomWord << std::endl;
    } else {
        std::cout << "Vector is empty!" << std::endl;
    }

    return 0;
}