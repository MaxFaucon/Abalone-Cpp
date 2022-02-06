#include <iostream>
#include <string>
#include <cctype>

#include "tui.h"
#include "model/game.h"

void Tui::update(const std::string & propertyName)
{    
    if (propertyName == "Successful")
    {
        displayBoard(m_game.board());
    } else if (propertyName == "Failed")
    {
        std::cout << "This move is impossible" << std::endl;
    } else if (propertyName == "Init")
    {
        std::cout << "Welcome in the abalone game !" << std::endl << std::endl;
        displayBoard(m_game.board());
    } else if (propertyName == "Over")
    {
        std::cout << "The game is over, the winner is " << m_game.winner() <<
                     " ! " << std::endl;
    }
}

void Tui::displayBoard(Board board)
{
    std::cout << "              _ _ _ _ _" << std::endl;
    std::cout << "      I - - / " << displayLineElements(0, board) << "\\"
        << std::endl;
    std::cout << "     H - - / " << displayLineElements(1, board) << "\\"
        << std::endl;
    std::cout << "    G - - / " << displayLineElements(2, board) << "\\"
        << std::endl;
    std::cout << "   F - - / " << displayLineElements(3, board) << "\\"
        << std::endl;
    std::cout << "  E - - ( " << displayLineElements(4, board) << ")"
        << std::endl;
    std::cout << "   D - - \\ " << displayLineElements(5, board) << "/\\"
        << std::endl;
    std::cout << "    C - - \\ " << displayLineElements(6, board) << "/\\ 9"
        << std::endl;
    std::cout << "     B - - \\ " << displayLineElements(7, board) << "/\\ 8"
        << std::endl;
    std::cout << "      A - - \\" << displayLineElements(8, board) << "/\\ 7"
        << std::endl;
    std::cout << "               \\ \\ \\ \\ \\  6" << std::endl;
    std::cout << "                1 2 3 4 5" << std::endl << std::endl;
}

std::string Tui::displayLineElements(int line, Board board)
{
    char escape = ' ';
    std::string str;

    if (line == 8)
    {
        escape = '_';
        str += escape;
    }

    for (int j = 0; j < 9; j++)
    {
        if (board.hexagonColor({line, j}) == Color::NONE)
        {
            str += '.';
            str += escape;
        } else if (board.hexagonColor({line, j}) == Color::WHITE)
        {
            str += 'W';
            str += escape;
        } else if (board.hexagonColor({line, j}) == Color::BLACK)
        {
            str += 'B';
            str += escape;
        }
    }

    return str;
}

void Tui::displayEjectedMarblesCount(const Player* currentPlayer, char color)
{
    std::cout << "Player " << color << ", you have ejected " << currentPlayer->
                 ejectedOpponentMarbles() << " marbles." <<
                 std::endl;
}
