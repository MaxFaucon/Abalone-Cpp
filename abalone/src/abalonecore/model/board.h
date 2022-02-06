#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <optional>
#include "hexagon.h"
#include "position.h"
#include "player.h"

class Position;
class Player;

/**
 * @brief The Board class Represents the game board.
 */
class Board
{
public:
    /**
     * @brief Board Constructor of Board. Creates all the hexagons of the Board.
     */
    Board();

    /**
     * @brief move Manages a marble move if the user enter 2 positions (linear
     * move).
     * @param from The starting position of a marble.
     * @param to The arrival position of a marble.
     * @param currentPlayer The current player.
     * @return True if the move was successfull, false otherwise.
     */
    bool move(Position from, Position to, Player* currentPlayer);

    /**
     * @brief move Manages a marble move if the user enter 3 positions (lateral
     * move).
     * @param fromFirst The position of the first marble of the starting line.
     * @param fromLast The position of the last marble of the starting line.
     * @param to The arrival position of the first marble of the starting
     * line.
     * @param currentPlayer The current player.
     * @return True if the move was successfull, false otherwise.
     */
    bool move(Position fromFirst, Position fromLast, Position to,
              Player* currentPlayer);

    /**
     * @brief hexagonColor Gives the color of a hexagon at a certain position.
     * @param position A position in the board.
     * @return The color of the square.
     */
    Color hexagonColor(Position position) const;    

    /**
     * @brief changeColor Changes the color of a certain hexagon of the board.
     * @param position The position of the hexagon.
     * @param color The new color.
     */
    void changeColor(Position position, Color color);

    /**
     * Destructor of Board.
     */
    ~Board() = default;

private:
    int static const arrayLength = 9;
    std::array<std::array<std::optional<Hexagon>, arrayLength>, arrayLength>
            m_hexagons;

    /**
     * @brief possibleLinearMove Checks if a linear move is possible.
     * @param from The starting position of a marble.
     * @param to The arrival position of a marble.
     * @param currentPlayer The current player.
     * @return True if the move is possible, false otherwise.
     */
    bool possibleLinearMove(Position from, Position to,
                            Player* currentPlayer);

    /**
     * @brief linearMove Makes a linear move.
     * @param from The starting position of a marble.
     * @param to The arrival position of a marble.
     * @param currentPlayer The current player.
     */
    void linearMove(Position from, Position to, Player* currentPlayer);

    /**
     * @brief possibleLateralMove Checks if a lateral move is possible.
     * @param fromFirst The position of the first marble of the starting line.
     * @param fromLast The position of the last marble of the starting line.
     * @param to The arrival position of the first marble of the starting
     * line.
     * @param currentPlayer The current player.
     * @return True if the move is possible, false otherwise.
     */
    bool possibleLateralMove(Position fromFirst, Position fromLast,
                             Position to, Player* currentPlayer);

    /**
     * @brief correctLateralPositions Checks if the positions entered are
     * correct for a possible lateral move.
     * @param fromFirst The position of the first marble of the starting line.
     * @param fromLast The position of the last marble of the starting line.
     * @param to The arrival position of the first marble of the starting
     * line.
     * @param currentPlayer The current player.
     * @return True if the positions are correct, false otherwise.
     */
    bool correctLateralPositions(Position fromFirst, Position fromLast,
                                Position to, Player* currentPlayer);

    /**
     * @brief lateralMove Makes a lateral move.
     * @param fromFirst The position of the first marble of the starting line.
     * @param fromLast The position of the last marble of the starting line.
     * @param to The arrival position of the first marble of the starting
     * line.
     * @param currentPlayer The current player.
     */
    void lateralMove(Position fromFirst, Position fromLast, Position to,
                     Player* currentPlayer);

    /**
     * @brief correctPositions Checks if the positions entered are correct for
     * a possible move.
     * @param from The starting position.
     * @param to The arrival position.
     * @param currentPlayer The current player.
     * @return True if the positions are correct, false otherwise.
     */
    bool correctPositions(Position from, Position to,
                          Player* currentPlayer);

    /**
     * @brief positionIsInside Checks if a position is inside the board.
     * @param position A position.
     * @return True if the position is inside the board, false otherwise.
     */
    bool positionIsInside(Position position);

    /**
     * @brief changePosition Changes a given position into another
     * position in a certain direction.
     * @param position The position to change.
     * @param xMove The move on the x-axis.
     * @param yMove The move on the y-axis.
     */
    void changePosition(Position &position, int xMove, int yMove);

    /**
     * @brief nextPosition Gives the next position of a position
     * in a certain direction.
     * @param position The starting position.
     * @param xMove The move on the x-axis.
     * @param yMove The move on the y-axis.
     * @return The next position.
     */
    Position nextPosition(Position position, int xMove, int yMove);    
};

#endif // BOARD_H
