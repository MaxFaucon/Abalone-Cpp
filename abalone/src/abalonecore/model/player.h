#ifndef PLAYER_H
#define PLAYER_H

#include "color.h"

/**
 * @brief The Player class Represents a player in the game.
 */
class Player
{
public:
    /**
     * @brief Player Constructor of Player.
     * @param color The player's color.
     *
     */
    Player(Color color);

    /**
     * @brief color Getter of color.
     * @return The player's color.
     */
    Color color() const;

    /**
     * @brief color Setter of color.
     * @param color The new color of the player.
     */
    void color(Color color);

    /**
     * @brief ejectedOpponentMarbles Getter of ejectedOpponentMarbles.
     * @return The number of opposing marbles that the current player has ejected.
     */
    int ejectedOpponentMarbles() const;

    /**
     * @brief ejectedOpponentMarbles Setter of ejectedOpponentMarbles.
     * @param ejectedOpponentMarbles The number of opposing marbles that the
     * current player has ejected.
     */
    void ejectedOpponentMarbles(int ejectedOpponentMarbles);

    /**
     * Player Destructor of Player.
     */
    ~Player() =default;

    /**
     * @brief operator ==
     * @param player
     * @return True if the player is the same as the one given in the parameter.
     */
    bool operator==(Player const &player) const;

private:
    Color m_color;
    int m_ejectedOpponentMarbles;
};

inline Color Player::color() const
{
    return m_color;
}

inline void Player::color(Color color)
{
    m_color = color;
}

inline int Player::ejectedOpponentMarbles() const
{
    return m_ejectedOpponentMarbles;
}

inline void Player::ejectedOpponentMarbles(int ejectedOpponentMarbles)
{
    m_ejectedOpponentMarbles = ejectedOpponentMarbles;
}

#endif // PLAYER_H
