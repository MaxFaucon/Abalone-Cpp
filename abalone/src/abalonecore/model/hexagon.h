#ifndef HEXAGON_H
#define HEXAGON_H

#include "color.h"

/**
 * @brief The Hexagon class Represents an hexagon on the game board.
 */
class Hexagon
{
public:
    /**
     * @brief Hexagon Constructor of Hexagon.
     * @param color The color of the square.
     */
    inline Hexagon(Color color) : m_color{color}
    {}

    /**
     * @brief color Getter of the hexagon color.
     * @return The color of the square.
     */
    Color color() const;

    /**
     * @brief color Setter of the hexagon color.
     * @param color The color of the square.
     */
    void color(Color color);

    /**
     * @brief Hexagon Destructor of Hexagon.
    */
    ~Hexagon() = default;

private:
    enum Color m_color;
};

inline Color Hexagon::color() const{
    return m_color;
}

inline void Hexagon::color(Color color) {
    m_color = color;
}

#endif // HEXAGON_H
