#include <iostream>
#include <stdlib.h>

void printField(char field[][3])
{
    std::cout << "   | A | B | C |\n";
    std::cout << "---|---|---|---|\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << " " << i + 1 << " |";
        for (int j = 0; j < 3; j++)
        {
            std::cout << " " << field[i][j] << " |";
        }
        std::cout << "\n";
        std::cout << "---|---|---|---|\n";
    }
}

void startGame(char field[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            field[i][j] = ' ';
        }
    }
}

void makeTurn(char field[][3], std::string input, char playerSymbol)
{
    int x = input[0] - 'A';
    int y = input[1] - '1';
    if (playerSymbol == 'X' || playerSymbol == 'O')
    {
        field[y][x] = playerSymbol;
    }
    else
    {
        std::cerr << "Bad symbol\n";
    }
}

std::string getCoords(char field[][3], int player)
{
    std::string input;
    bool badInput = false;
    do {
        std::cout << "Player " << player
        << ": please make turn in format (XN, where X: A,B,C; N:1,2,3):\n";

        std::cin >> input;

        if (input != "exit" && (input[0] < 'A' || input[0] > 'C' || input[1] < '1' || input[1] > '3' ))
        {
            badInput = true;
            std::cout << "Bad input, please repeat, or type \'exit\'.\n";
        }
        else if (input != "exit" && field[input[1] - '1'][input[0] - 'A'] != ' ')
        {
            badInput = true;
            std::cout << "Field is busy, please repeat turn.\n";
        }
        else
        {
            badInput = false;
        }
    } while (badInput);

    return input;
}

bool checkGameStatus(char field[][3], int player)
{
    char c = player == 1 ? 'X' : 'O';
    for (int i = 0; i < 3; i++)
    {
        int horCount = 0;
        int vertCount = 0;

        for (int j = 0; j < 3; j++)
       {
           horCount += field[j][i];
           vertCount += field[i][j];
       }

        if ((int) horCount == (int)c * 3 || (int) vertCount == (int)c * 3)
        {
            std::cout << "Victory!\n";
            std::cout << "Player " << player << " is the winner!\n";
            return true;
        }
    }
    return false;
}

int main() {

    char field[3][3];
    startGame(field);
    bool end = false;

    int player = 1;
    int turnsCount = 0;

    while (!end)
    {
        system("CLEAR");

        turnsCount++;
        printField(field);
        if (player == 3) player = 1;
        std::string turn = getCoords(field, player);
        if (turn == "exit") break;
        makeTurn(field, turn, player == 1?'X':'O');
        //end = checkWinners();
        end = checkGameStatus(field, player);
        if (turnsCount == 9 && !end)
        {
            end = true;
            std::cout << "No winners!\n";
        }
        player++;
    }
    printField(field);
    std::cout << "Turns made: " << turnsCount / 2 + turnsCount % 2 << "\n";

    return 0;
}
