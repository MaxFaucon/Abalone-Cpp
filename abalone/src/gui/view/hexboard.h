#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <vector>

#include "view/ghexacell.h"
#include "model/board.h"

class HexBoard
{

protected:
    std::vector<GHexaCell *> m_gHexaCells;

public:
    /**
     * @brief HexBoard Constructor of Hexboard.
     * @param board The game board.
     */
    explicit HexBoard(Board board);

    /**
     * @brief gHexaCells Getter of gHexaCells.
     * @return The hexacells that form the board.
     */
    inline std::vector<GHexaCell *> gHexaCells() const;

    /**
     * @brief updateColors Updates the colors of the hexacells.
     * @param board The board vector.
     */
    void updateColors(Board board);

private:
    Board m_board;
    void createLabels();
};

std::vector<GHexaCell *> HexBoard::gHexaCells() const
{
    return m_gHexaCells;
}

#endif // HEXBOARD_H
