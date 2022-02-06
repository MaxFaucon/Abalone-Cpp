#include <vector>

#include "controller.h"

void Controller::playTurn(std::vector<Position> positions)
{    
     m_game.playTurn(positions);
}

void Controller::checkIfOver()
{
    m_game.isOver();
}

void Controller::initGame()
{
    m_game.initGame();
}
