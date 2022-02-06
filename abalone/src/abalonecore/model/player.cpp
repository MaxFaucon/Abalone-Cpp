#include "player.h"

Player::Player(Color color): m_color{color}, m_ejectedOpponentMarbles{0}
{}

bool Player::operator==(Player const &player) const
{
    return (m_color == player.color())
            && (m_ejectedOpponentMarbles == player.ejectedOpponentMarbles());
}
