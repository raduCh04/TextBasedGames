#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <vector>

const std::vector<std::string> HANGMAN_STAGES = {
    "  +---+\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " /    |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " / \\  |\n"
    "      |\n"
    "=========\nGAME OVER!"};

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
    std::vector<std::string> easy_words = {"apple", "dog", "fish", "house", "tree"};
    std::vector<std::string> medium_words = {"elephant", "giraffe", "mountain", "computer", "sunflower"};
    std::vector<std::string> hard_words = {"encyclopedia", "philosophy", "sophisticated", "astronaut", "chrysanthemum"};

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
        words = easy_words;
        break;
    case 2:
        words = medium_words;
        break;
    case 3:
        words = hard_words;
        break;
    }

    std::srand((unsigned int)time(nullptr));
    return words[std::rand() % words.size()];
}

static void displayHangman(int max_tries, int remaining_tries)
{
    int total_stages = HANGMAN_STAGES.size();

    int stage_index = (max_tries - remaining_tries) * (total_stages - 1) / max_tries;

    stage_index = std::min(stage_index, total_stages - 1);

    std::cout << HANGMAN_STAGES[stage_index] << std::endl;
}

static void playGame(const std::string &word, int max_tries)
{
    int guessed = 0;
    int remaining_tries = max_tries;
    std::string final_word = "";
    for (int i = 0; i < word.length(); i++)
    {
        final_word += "_ ";
    }

    std::unordered_set<char> guessed_letters;
    while (true)
    {
        std::cout << final_word << std::endl;
        displayHangman(max_tries, remaining_tries);
        if (max_tries <= 0)
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
        bool is_in_word = false;
        if (guessed_letters.find(letter) == guessed_letters.end())
        {
            for (int i = 0; i < word.length(); i += 1)
            {
                if (word[i] == letter)
                {
                    final_word[i * 2] = letter;
                    encounters++;
                    is_in_word = true;
                }
            }
        }
        else
        {
            std::cout << "You already guessed this letter! Try Again!" << std::endl;
            continue;
        }

        guessed_letters.insert(letter);

        if (is_in_word)
        {
            guessed += encounters;
            std::cout << "Right!" << std::endl;
        }
        else
        {
            remaining_tries--;
            std::cout << "False!" << std::endl;
        }
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