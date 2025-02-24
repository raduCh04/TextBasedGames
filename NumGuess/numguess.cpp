#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <limits>

static inline void toLower(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
}

int main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL));
    std::unordered_map<std::string, int> difficulties = { {"easy", 10}, {"medium", 100}, {"hard", 1000}, {"evil", 100000} };
    std::string difficulty = "";
    while (true)
    {
        //NOTE: Could use numbers, however for practice purposes I used strings and a map
        std::cout << "What difficulty would you like to play?\nEnter easy (1 to 10), "
            "medium (1 to 100), hard (1 to 1000), evil (1 to 100000): "; 
        std::cin >> difficulty;
        toLower(difficulty);
        if (difficulties.find(difficulty) == difficulties.end())
            std::cout << "Invalid difficulty! Try again!\n";
        else
            break;
    }
        
    int guesses = 0;
    int guess = -1;
    int number = rand() % difficulties[difficulty];
    
    while (guess != number)
    {
        guesses++;
        std::cout << "Your guess: ";
        while (!(std::cin >> guess))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Try again!\n";
        }

        if (guess < number)
            std::cout << "Too low\n";
        else if (guess > number)
            std::cout << "Too high.\n";
    }
    std::cout << "Right! The number was: " << number << '\n';
    std::cout << "You needed " << guesses << " guesses.\n";

}
