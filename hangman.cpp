#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <unordered_set>

static bool is_number(const std::string &s)
{
    for (char c : s)
    {
        if (std::isdigit(c) == false)
            return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int tries = 0;
    std::cout << "Enter maximum number of tries: ";
    std::cin >> tries;
    while (!(std::cin >> tries))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Not a number! Try again." << std::endl;
        std::cout << "Enter maximum number of tries: ";
        std::cin >> tries;
    }

    std::string word = "";
    std::cout << "Enter word to guess: ";
    std::cin >> word;
    while (is_number(word))
    {
        std::cout << "Word cannot include numbers! Try again.";
        std::cout << "Enter word to guess: ";
        std::cin >> word;
    }

    for (char &c : word)
        c = tolower(c);

    std::string final_word = "";
    for (int i = 0; i < word.length(); i++)
    {
        final_word += "_ ";
    }
    std::cout << final_word << std::endl;

    int guessed = 0;
    while (true)
    {
        if (tries <= 0)
        {
            std::cout << "You lost!" << std::endl;
            break;
        }
        if (guessed >= word.length())
        {
            std::cout << "You won!" << std::endl;
            break;
        }

        {
            char letter = 0;
            std::cout << "Enter letter: ";
            std::cin >> letter;
            while (std::isdigit(letter))
            {
                std::cout << "No number allowed! Try again." << std::endl;
                std::cout << "Enter letter: ";
                std::cin >> letter;
            }

            int encounters = 0;
            bool isInWord = false;
            for (int i = 0; i < word.length(); i += 1)
            {
                if (word[i] == letter)
                {
                    final_word[i * 2] = letter;
                    encounters++;
                    isInWord = true;
                }
            }

            if (isInWord)
            {
                guessed += encounters;
                std::cout << "Right!" << std::endl;
            }
            else
            {
                tries--;
                std::cout << "False!" << std::endl;
            }
            std::cout << "Tries left: " << tries << std::endl;
            std::cout << final_word << std::endl;
        }
    }
}