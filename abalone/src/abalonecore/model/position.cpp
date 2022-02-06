#include <iostream>

#include "position.h"


Position::Position(int x, int y) : m_x{x}, m_y{y}
{}

Position::Position(char x, int y)
    : m_x{x - 57 - (2 * (x - 'A'))}, m_y{y - 1}
{}

bool Position::operator!= (const Position &p2)
{
    return m_x != p2.x() || m_y != p2.y();
}
