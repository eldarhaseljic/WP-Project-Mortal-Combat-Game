#include "Player.h"

Player::Player()
{
    //ctor
}

void Player::updateX(const int& x)
{
    if (warrior.x + x > 498 || warrior.x + x < 5)
        return;
    warrior.x += x;
    armKick.x += x;
    comboKick.x += x;
    flyKick.x += x;
    kickedKick.x += x;
    knockedKick.x += x;
    kneeKick.x += x;
    legKick.x += x;
    blockStance.x += x;
}
