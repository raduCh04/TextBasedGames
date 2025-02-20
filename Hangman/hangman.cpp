#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <vector>

static bool is_number(const std::string &s)
{
    return std::all_of(s.begin(), s.end(), isdigit);
}

static char toLower(char c)
{
    return (char)std::tolower((unsigned char)c); // Prevent errors with no ASCII characters
}

static std::string getWord()
{

    std::vector<std::string> easyWords = {"apple", "dog", "fish", "house", "tree"};
    std::vector<std::string> mediumWords = {"elephant", "giraffe", "mountain", "computer", "sunflower"};
    std::vector<std::string> hardWords = {"encyclopedia", "philosophy", "sophisticated", "astronaut", "chrysanthemum"};

    int choice = -1;
    std::cout << "Choose difficulty level:\n1 - Easy\n2 - Medium\n3 - Hard\nEnter choice: ";
    while (!(std::cin >> choice) || choice < 1 || choice > 3)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice! Enter 1, 2, or 3: ";
    }

    std::vector<std::string> words;
    switch (choice)
    {
    case 1:
        words = easyWords;
        break;
    case 2:
        words = mediumWords;
        break;
    case 3:
        words = hardWords;
        break;
    }

    std::srand((unsigned int)time(nullptr));
    return words[std::rand() % words.size()];
}

static void playGame(const std::string &word, int maxTries)
{
    int guessed = 0;
    std::string final_word = "";
    for (int i = 0; i < word.length(); i++)
    {
        final_word += "_ ";
    }
    std::cout << final_word << std::endl;

    std::unordered_set<char> guessedLetters;
    while (true)
    {
        if (maxTries <= 0)
        {
            std::cout << "You lost!" << std::endl;
            break;
        }
        if (guessed >= word.length())
        {
            std::cout << "You won!" << std::endl;
            break;
        }

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
        if (guessedLetters.find(letter) == guessedLetters.end())
        {
            for (int i = 0; i < word.length(); i += 1)
            {
                if (word[i] == letter)
                {
                    final_word[i * 2] = letter;
                    encounters++;
                    isInWord = true;
                }
            }
        }
        else
        {
            std::cout << "You already guessed this letter! Try Again!" << std::endl;
            continue;
        }

        guessedLetters.insert(letter);

        if (isInWord)
        {
            guessed += encounters;
            std::cout << "Right!" << std::endl;
        }
        else
        {
            maxTries--;
            std::cout << "False!" << std::endl;
        }

        std::cout << final_word << std::endl;
    }
}

int main()
{
    int tries = 0;
    std::cout << "Enter maximum number of tries: ";
    while (!(std::cin >> tries))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Not a number! Try again." << std::endl;
        std::cout << "Enter maximum number of tries: ";
    }

    std::string word = getWord();
    playGame(word, tries);
}