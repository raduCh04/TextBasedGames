#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string word = "";
    std::string final_word = "";
    int tries = 0;
    int guessed = 0;
    bool won = false;

    if (argc > 2)
    {
        tries = atoi(argv[1]);
        word = argv[2];
    }
    else
    {
        std::cout << "Enter maximum number of tries: ";
        std::cin >> tries;
        std::cout << "Enter word to guess: ";
        std::cin >> word;
    }

    for (int i = 0; i < word.length(); i++)
    {
        final_word += "_ ";
    }
    std::cout << final_word << std::endl;

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

        char letter = 0;
        std::cout << "Enter letter: ";
        std::cin >> letter;

        int index = 0;
        bool isInWord = false;
        for (int i = 0; i < word.length(); i += 1)
        {
            if (word[i] == letter)
            {
                final_word[i * 2] = letter;
                isInWord = true;
            }
        }

        if (isInWord)
        {
            guessed++;
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
