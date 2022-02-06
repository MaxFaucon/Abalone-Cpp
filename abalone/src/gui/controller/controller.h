#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/game.h"

/**
 * @brief The Controller class Manages the model and the view.
 */
class Controller
{
public:
    /**
     * @brief Controller Constructor of controller.
     * @param game The model.
     */
    inline Controller(Game & game) : m_game { game }
    {
        game.initGame();
    }

    /**
     * @brief playTurn Makes a player's turn.
     * @param positions The positions for the move.
     */
    void playTurn(std::vector<Position> positions);

    /**
     * @brief initGame Initializes the game.
     */
    void initGame();

    /**
     * @brief checkIfOver Checks if the game is over.
     */
    void checkIfOver();

private:
    Game & m_game;
};

#endif // CONTROLLER_H
