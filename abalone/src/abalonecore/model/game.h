#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.h"
#include "observer/subject.h"
#include "observer/observer.h"

/**
 * @brief The Game class Represents the model of the game.
 * Manages all the methods needed to play the game.
 */
class Game: public Subject
{
public:
    /**
     * @brief PROPERTY_INIT Allows to know when the game is initialized.
     */
    inline static const std::string PROPERTY_INIT = "Init";
    /**
     * @brief PROPERTY_SUCCESSFUL Allows to know when a move is successful.
     */
    inline static const std::string PROPERTY_SUCCESSFUL = "Successful";
    /**
     * @brief PROPERTY_FAILED Allows to know when a move is failed.
     */
    inline static const std::string PROPERTY_FAILED = "Failed";
    /**
     * @brief PROPERTY_OVER Allows to know when a game is over.
     */
    inline static const std::string PROPERTY_OVER = "Over";


    /**
     * @brief Game Constructor of Game.
     */
    inline Game()
    {}

    inline virtual ~Game();

    /**
     * @brief currentPLayer Getter of currentPlayer.
     * @return The current player.
     */
    const Player* currentPlayer() const;

    /**
     * @brief board Getter of board.
     * @return The board.
     */
    const Board board() const;

    /**
     * @brief isOver Checks if the game is over.
     * @return True if the game is over, false otherwise.
     */
    bool isOver() const;

    /**
     * @brief playTurn Manages a player's turn.
     * @param positions A board of length 2 or 3 that contains
     * the positions entered by the player.
     */
    void playTurn(std::vector<Position> positions);

    /**
     * @brief initGame Initializes the game.
     */
    void initGame();

    /**
     * @brief winner Gives the color of the winner of the game.
     * @return The player that won the game.
     */
    std::string winner();

private:
    Player* m_player1;
    Player* m_player2;
    Player* m_currentPlayer;
    Board* m_board;

    /**
     * @brief changeCurrentPlayer Change the current player.
     */
    void changeCurrentPlayer();

    /**
     * @brief makesMove Makes a move according to the number of positions.
     * @param positions The positions for the move.
     * @return True if the move succeeded, false otherwise.
     */
    bool makesMove(std::vector<Position> positions);    

};

Game::~Game()
{
    m_currentPlayer = nullptr;
    delete m_board;
    delete m_player1;
    delete m_player2;
}

#endif // GAME_H
