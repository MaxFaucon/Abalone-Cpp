#include "game.h"
#include <iostream>

const Player* Game::currentPlayer() const
{
    return m_currentPlayer;
}

const Board Game::board() const
{
    const Board board(*m_board);
    return board;
}

bool Game::isOver() const
{
    bool isOver = m_player1->ejectedOpponentMarbles() == 6 ||
            m_player2->ejectedOpponentMarbles() == 6;
    if (isOver)
    {
        notifyObservers(PROPERTY_OVER);
    }

    return isOver;
}

void Game::playTurn(std::vector<Position> positions)
{
    if (makesMove(positions))
    {                
        notifyObservers(PROPERTY_SUCCESSFUL);        
        changeCurrentPlayer();
    } else
    {
        notifyObservers(PROPERTY_FAILED);
    }
}

void Game::initGame()
{
    m_player1 = new Player(Color::BLACK);
    m_player2 = new Player(Color::WHITE);
    m_currentPlayer = m_player1;
    m_board = new Board();

    notifyObservers(PROPERTY_INIT);
}

std::string Game::winner()
{
    std::string winnerColor;
    if (m_player1->ejectedOpponentMarbles() == 6)
    {
        winnerColor = "Black";
    } else
    {
        winnerColor = "White";
    }

    return winnerColor;
}

void Game::changeCurrentPlayer()
{
    if (m_currentPlayer->color() == m_player1->color())
    {
        m_currentPlayer = m_player2;
    } else
    {
        m_currentPlayer = m_player1;
    }
}

bool Game::makesMove(std::vector<Position> positions)
{
    if (positions.size() == 2)
    {
        return m_board->move(positions.at(0), positions.at(1), m_currentPlayer);
    } else
    {
        return m_board->move(positions.at(0), positions.at(1), positions.at(2),
                            m_currentPlayer);
    }
}
