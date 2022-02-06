#ifndef POSITION_H
#define POSITION_H

/**
 * @brief The Position class Represents the position of an hexagon on the Board.
 */
class Position
{
public:

    /**
     * @brief Position : Basic constructor of Position.
     * @param x The position on the x-axis (rows).
     * @param y The position on the y-axis (columns).
     */
    Position(int x, int y);

    /**
     * @brief Position Second constructor of Position but used for the user input.
     * @param x The position on the x-axis (rows).
     * @param y The position on the y-axis (columns).
     */
    Position(char x, int y);

    /**
     * @brief x Getter of x.
     * @return The position on the x-axis (rows).
     */
    int x() const;

    /**
     * @brief x Setter of x.
     * @param x The position on the x-axis (rows).
     */
    void x(int x);

    /**
     * @brief y Getter of y.
     * @return The position on the y-axis (columns).
     */
    int y() const;    

    /**
     * @brief y Setter of y.
     * @param y The position on the y-axis (columns).
     */
    void y(int y);

    /**
     * @brief operator != Checks if the current position is
     * different to another position.
     * @param p2 The other position.
     * @return True if the positions are different, false otherwise.
     */
    bool operator!= (const Position &p2);

    /**
     * @brief Position Destructor of Position.
     */
    ~Position() = default;

private:
    int m_x;
    int m_y;
};

inline int Position::x() const
{
    return m_x;
}

inline void Position::x(int x)
{
    m_x = x;
}

inline int Position::y() const
{
    return m_y;
}

inline void Position::y(int y)
{
    m_y = y;
}

#endif // POSITION_H
