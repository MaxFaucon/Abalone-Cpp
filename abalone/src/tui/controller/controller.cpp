#include <iostream>
#include <vector>

#include "controller.h"

Controller::Controller(Game & game, Tui & tui) : m_game{ game }, m_tui { tui }
{}

void Controller::start()
{
    m_game.initGame();
    std::vector<Position> positions;

    do
    {
        positions.clear();
        positions = askMove(m_game.currentPlayer());
        m_game.playTurn(positions);
    } while (!m_game.isOver());
}

std::vector<Position> Controller::askMove(const Player* currentPlayer)
{
    std::string input;
    std::vector<Position> positions;

    std::cout << std::endl;

    if (currentPlayer->color() == Color::BLACK)
    {
        m_tui.displayEjectedMarblesCount(currentPlayer, 'B');
        std::cout << "Player B, enter a move : ";
    } else
    {
        m_tui.displayEjectedMarblesCount(currentPlayer, 'W');
        std::cout << "Player W, enter a move : ";
    }

    try {
        std::getline(std::cin, input);
        positions = processInput(input);
    }  catch (const std::out_of_range& exception) {
        positions.clear();
    }

    if (positions.size() == 0)
    {
        std::cout << "Invalid input." << std::endl <<
                     "Examples of valid inputs : [A1B2] or [C3C5D3]" << std::endl;
        return askMove(currentPlayer);
    }

    return positions;
}

std::vector<Position> Controller::processInput(std::string input)
{
    std::vector<Position> positions;
    char letter;
    int number;

    if (input.size() > 7 || input.size() < 4)
    {
        return positions;
    }

    for (size_t i = 0; i < input.size() - 1; i+=2) {
        letter = std::toupper(input.at(i));
        number = input.at(i + 1) - '0';
        if (letter < 65 || letter > 73 || number < 1 || number > 9)
        {
            positions.clear();
            return positions;
        }
        Position position(letter, number);
        positions.push_back(position);
    }

    return positions;
}
