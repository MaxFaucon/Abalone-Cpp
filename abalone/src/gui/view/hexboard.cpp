#include <cmath>
#include <string>
#include <iostream>

#include "hexboard.h"

HexBoard::HexBoard(Board board) : m_board { board }
{
    int k = -4;
    int l;
    int m;
    Position position(0, 0);
    Color color;

    createLabels();

    for (int i = 0; i < 9; i++)
    {
        l = std::abs(2 - (i / 2));
        m = std::abs(i - 4);
        for (int j = 0; j < 9; j++)
        {
            color = board.hexagonColor({i, j});
            if (color != 0)
            {
                position.x(i);
                position.y(j);
                if (i % 2 == 0)
                {
                    m_gHexaCells.push_back(new GHexaCell(
                                              2 * k * 40 * 3 / 4,
                                              l * sqrt(3) * 40, position,
                                              color, ' ', nullptr));
                    l++;
                } else
                {
                    m_gHexaCells.push_back(new GHexaCell(
                                              2 * k * 40 * 3 / 4,
                                              m * sqrt(3) * 40 / 2, position,
                                              color, ' ', nullptr));
                    m+=2;
                }

            }
        }
        k++;
    }
}

void HexBoard::updateColors(Board board)
{
    int k = 18;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Color color = board.hexagonColor({i, j});
            if (color != 0)
            {
                if (m_gHexaCells.at(k)->selected())
                    m_gHexaCells.at(k)->selected(false);
                m_gHexaCells.at(k)->color(color);
                m_gHexaCells.at(k)->update();
                k++;
            }
        }
    }
}

void HexBoard::createLabels()
{
    Position position(0, 0);
    Color color = m_board.hexagonColor(position);

    m_gHexaCells.push_back(new GHexaCell(
                              2 * -4 * 40 * 3 / 4,
                              sqrt(3) * 40, position, color, 'I', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * -3 * 40 * 3 / 4,
                              sqrt(3) * 40 / 2, position, color, 'H', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * -2 * 40 * 3 / 4,
                              0, position, color, 'G', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * -1 * 40 * 3 / 4,
                              -1 * sqrt(3) * 40 / 2, position, color, 'F', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              0,
                              -1 * sqrt(3) * 40, position, color, 'E', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 1 * 40 * 3 / 4,
                              -1 * sqrt(3) * 40 / 2, position, color, 'D', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 1 * 40 * 3 / 4,
                              17 * sqrt(3) * 40 / 2, position, color, '9', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 2 * 40 * 3 / 4,
                              0, position, color, 'C', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 2 * 40 * 3 / 4,
                               8 * sqrt(3) * 40, position, color, '8', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 3 * 40 * 3 / 4,
                              sqrt(3) * 40 / 2, position, color, 'B', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 3 * 40 * 3 / 4,
                              15 * sqrt(3) * 40 / 2, position, color, '7', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 4 * 40 * 3 / 4,
                              sqrt(3) * 40, position, color, 'A', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 4 * 40 * 3 / 4,
                              7 * sqrt(3) * 40, position, color, '6', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 5 * 40 * 3 / 4,
                              5 * sqrt(3) * 40 / 2, position, color, '1', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 5 * 40 * 3 / 4,
                              7 * sqrt(3) * 40 / 2, position, color, '2', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 5 * 40 * 3 / 4,
                              9 * sqrt(3) * 40 / 2, position, color, '3', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 5 * 40 * 3 / 4,
                              11 * sqrt(3) * 40 / 2, position, color, '4', nullptr));
    m_gHexaCells.push_back(new GHexaCell(
                              2 * 5 * 40 * 3 / 4,
                              13 * sqrt(3) * 40 / 2, position, color, '5', nullptr));
}
