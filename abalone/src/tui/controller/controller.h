#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/game.h"
#include "view/tui.h"

/**
 * @brief The Controller class Manages the model and the view.
 */
class Controller
{
public:
    /**
     * @brief Controller Constructor of controller.
     * @param game The model.
     * @param tui The view.
     */
    Controller(Game & game, Tui & tui);

    /**
     * @brief start Starts the game.
     */
    void start();    

private:
    Game & m_game;
    Tui & m_tui;

    /**
     * @brief askMove Asks a move to the user.
     * @param currentPlayer The current player.
     * @return A vector with the positions entered by the user.
     */
    std::vector<Position> askMove(const Player* currentPlayer);

    /**
     * @brief processInput Creates positions for the move according to the user
     * inputs.
     * @param input The user input.
     * @return A vector with the positions entered by the user.
     */
    std::vector<Position> processInput(std::string input);
};

#endif // CONTROLLER_H
