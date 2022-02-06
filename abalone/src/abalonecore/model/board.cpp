#include <optional>
#include <array>
#include <iostream>

#include "board.h"

Board::Board() :
    m_hexagons{
{{std::nullopt, std::nullopt, std::nullopt, std::nullopt, Hexagon(Color::WHITE),
        Hexagon(Color::WHITE), Hexagon(Color::WHITE), Hexagon(Color::WHITE), Hexagon(Color::WHITE) },
{ std::nullopt, std::nullopt, std::nullopt, Hexagon(Color::WHITE), Hexagon(Color::WHITE), Hexagon(Color::WHITE),
        Hexagon(Color::WHITE), Hexagon(Color::WHITE), Hexagon(Color::WHITE) },
{ std::nullopt, std::nullopt, Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::WHITE), Hexagon(Color::WHITE),
        Hexagon(Color::WHITE), Hexagon(Color::NONE), Hexagon(Color::NONE) },
{ std::nullopt, Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE),
        Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE) },
{ Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE),
        Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE) },
{ Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::NONE),
        Hexagon(Color::NONE), Hexagon(Color::NONE), std::nullopt },
{ Hexagon(Color::NONE), Hexagon(Color::NONE), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::NONE),
        Hexagon(Color::NONE), std::nullopt, std::nullopt },
{ Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK),
        std::nullopt, std::nullopt, std::nullopt },
{ Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), Hexagon(Color::BLACK), std::nullopt,
        std::nullopt, std::nullopt, std::nullopt}}
        }
{}

Color Board::hexagonColor(Position position) const
{
    return m_hexagons.at(position.x()).at(position.y())->color();
}

bool Board::move(Position from, Position to,
                 Player* currentPlayer)
{
    if (possibleLinearMove(from, to, currentPlayer))
    {
        linearMove(from, to, currentPlayer);

        return true;
    }

    return false;
}

bool Board::move(Position fromFirst, Position fromLast, Position to,
                 Player* currentPlayer)
{
    if (possibleLateralMove(fromFirst, fromLast, to, currentPlayer))
    {
        lateralMove(fromFirst, fromLast, to, currentPlayer);

        return true;
    }

    return false;
}

bool Board::possibleLinearMove(Position from, Position to,
                               Player* currentPlayer)
{
    if (!correctPositions(from, to, currentPlayer))
    {
        return false;
    }

    int xMarbleMove = to.x() - from.x();
    int yMarbleMove = to.y() - from.y();
    int countCurrentPlayerMarbles = 0;
    int countOpponentPlayerMarbles = 0;
    Color currentColor = currentPlayer->color();
    Position currentPosition = from;

    // Count current player marbles
    while (positionIsInside(currentPosition) &&
           m_hexagons.at(currentPosition.x()).at(currentPosition.y())->color() ==
           currentColor)
    {
        countCurrentPlayerMarbles++;
        changePosition(currentPosition, xMarbleMove, yMarbleMove);
    }

    // Doesn't allow an out of bounds movement.
    if (!positionIsInside(currentPosition)
            || countCurrentPlayerMarbles > 3)
    {
        return false;
    }

    // Count the possible opposing marbles
    while (positionIsInside(currentPosition) &&
           hexagonColor(currentPosition) != Color::NONE &&
           countCurrentPlayerMarbles > countOpponentPlayerMarbles)
    {
        countOpponentPlayerMarbles++;
        changePosition(currentPosition, xMarbleMove, yMarbleMove);
    }

    // Returns true if the opposing marbles aren't blocking.
    return countCurrentPlayerMarbles > countOpponentPlayerMarbles;
}

void Board::linearMove(Position from, Position to,
                       Player* currentPlayer)
{
    int xMarbleMove = to.x() - from.x();
    int yMarbleMove = to.y() - from.y();
    Position currentPosition = from;

    // Goes through the adjacent marbles on the line
    while (positionIsInside(currentPosition) &&
           hexagonColor(currentPosition) != Color::NONE)
    {
        changePosition(currentPosition, xMarbleMove, yMarbleMove);
    }

    // If last position not inside the board -> A marble will be ejected
    if (!positionIsInside(currentPosition))
    {
        currentPlayer->ejectedOpponentMarbles(
                    currentPlayer->ejectedOpponentMarbles() + 1);
        changePosition(currentPosition, -xMarbleMove, -yMarbleMove);
    }

    // Go back to first position and move the marbles one square forward
    while (currentPosition != from)
    {
        changePosition(currentPosition, -xMarbleMove, -yMarbleMove);
        changeColor(nextPosition(currentPosition, xMarbleMove, yMarbleMove),
                    hexagonColor(currentPosition));
    }

    m_hexagons.at(from.x()).at(from.y())
            ->color(Color::NONE);
}

bool Board::possibleLateralMove(Position fromFirst, Position fromLast,
                                Position to, Player* currentPlayer)
{
    if (!correctLateralPositions(fromFirst, fromLast, to, currentPlayer)
            || !(fromFirst != fromLast))
    {
        return false;
    }

    int xMarbleMove = to.x() - fromFirst.x();
    int yMarbleMove = to.y() - fromFirst.y();
    int xNextMarble = fromLast.x() - fromFirst.x();
    int yNextMarble = fromLast.y() - fromFirst.y();
    Position currentPosition = fromFirst;

    if (xNextMarble == 2 || xNextMarble == -2)
    {
        xNextMarble /= 2;
    }
    if (yNextMarble == 2 || yNextMarble == -2)
    {
        yNextMarble /= 2;
    }


    while (currentPosition != nextPosition(fromLast, xNextMarble, yNextMarble))
    {
        // Checks if no obstacle for the move
        if (!positionIsInside(nextPosition(currentPosition, xMarbleMove,
                                           yMarbleMove)) ||
                hexagonColor(nextPosition(currentPosition, xMarbleMove,
                                          yMarbleMove)) != Color::NONE)
        {
            return false;
        }
        else if (hexagonColor(currentPosition) != currentPlayer->color())
        {
            return false;
        }

        changePosition(currentPosition, xNextMarble, yNextMarble);
    }

    return true;
}

bool Board::correctLateralPositions(Position fromFirst, Position fromLast,
                                    Position to, Player* currentPlayer)
{
    int xNextMarble = fromLast.x() - fromFirst.x();
    int yNextMarble = fromLast.y() - fromFirst.y();

    if (!correctPositions(fromFirst, to, currentPlayer))
    {
        return false;
    } else if (!positionIsInside(fromLast) || xNextMarble > 2 ||
               xNextMarble < -2 || yNextMarble > 2 || yNextMarble < -2)
    {
        return false;
    }

    return true;
}

void Board::lateralMove(Position fromFirst, Position fromLast, Position to,
                        Player* currentPlayer)
{        
    int xMarbleMove = to.x() - fromFirst.x();
    int yMarbleMove = to.y() - fromFirst.y();
    int xNextMarble = fromLast.x() - fromFirst.x();
    int yNextMarble = fromLast.y() - fromFirst.y();
    Position currentPosition = fromFirst;
    Position newPosition = to;

    if (xNextMarble == 2 || xNextMarble == -2)
    {
        xNextMarble /= 2;
    }
    if (yNextMarble == 2 || yNextMarble == -2)
    {
        yNextMarble /= 2;
    }

    // Moves the marbles
    while (currentPosition != nextPosition(fromLast, xNextMarble, yNextMarble))
    {
        newPosition = nextPosition(currentPosition, xMarbleMove, yMarbleMove);
        changeColor(currentPosition, Color::NONE);
        changeColor(newPosition, currentPlayer->color());
        changePosition(currentPosition, xNextMarble, yNextMarble);
    }
}

bool Board::correctPositions(Position from, Position to,
                             Player* currentPlayer)
{
    int xMarbleMove = to.x() - from.x();
    int yMarbleMove = to.y() - from.y();

    if (!positionIsInside(from) || !positionIsInside(to))
    {
        return false;
    }
    else if ((xMarbleMove == 1 && yMarbleMove == 1) ||
             (xMarbleMove == -1 && yMarbleMove == -1))
    {
        return false;
    }
    else if (xMarbleMove > 1 || xMarbleMove < -1 || yMarbleMove > 1 ||
             yMarbleMove < -1)
    {
        return false;
    }
    else if (hexagonColor(from) != currentPlayer->color())
    {
        return false;
    } else if (!(from != to))
    {
        return false;
    }

    return true;
}

bool Board::positionIsInside(Position position)
{
    return (position.x() < static_cast<int>(m_hexagons.size()) && position.x() >= 0) &&
            (position.y() < static_cast<int>(m_hexagons.size()) && position.y() >= 0) &&
            m_hexagons.at(position.x()).at(position.y()) != std::nullopt;
}

void Board::changePosition(Position &position, int xMove, int yMove)
{
    position.x(position.x() + xMove);
    position.y(position.y() + yMove);
}

Position Board::nextPosition(Position position, int xMove, int yMove)
{
    Position nextPosition(position.x() + xMove, position.y() + yMove);

    return nextPosition;
}

void Board::changeColor(Position position, Color color)
{
    m_hexagons.at(position.x()).at(position.y())
            ->color(color);
}
