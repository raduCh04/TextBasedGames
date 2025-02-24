#include <iostream>

static char board[3][3] = {
    {' ', ' ', ' ', },
    {' ', ' ', ' ', },
    {' ', ' ', ' ', },
};

char changePlayer(char current)
{
    return current == 'X' ? 'O' : 'X';
}

static void enterPosition(int i, int j, char player)
{
    player == 'O' ? board[i][j] = 'O' : board[i][j] = 'X';
}

static bool checkBound(int i, int j)
{
    return (i < 3 && i >= 0 && j < 3 && j >= 0 && board[i][j] == ' ');
}

static void displayBoard()
{
    std::cout << "-------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << '|';
        for (int j = 0; j < 3; j++)
        {
            std::cout << ' ' << board[i][j] << " |";
        }
        std:: cout << "\n-------------\n";
    }
}

static bool checkWin(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

int main()
{
    char current_player = 'X';
    int turn;
    for (turn = 0; turn < 9; turn++)
    {
        displayBoard();
        int x = -1, y = -1;
        while (true)
        {
            std::cout << "Player " << (current_player == 'O' ? 'O' : 'X') << " enter your position (row column): ";
            if (checkBound(--x, --y))
            {
                enterPosition(x, y, current_player);
                break;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input/position! Try again.\n";
                displayBoard();
            }
        }
        
        if (checkWin(current_player))
        {
            displayBoard();
            std::cout << "Player " << current_player << " wins!\n";
            break;
        }
        current_player = changePlayer(current_player);
    }

    displayBoard();
    if (turn == 9 && checkWin('X') == false && checkWin('O') == false)
        std::cout << "It's a draw!\n";
    return 0;
}
