#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Settings.h"

class Bullet
{
private:
    float angle;
public:
    sf::CircleShape bullet;
    Bullet(float x, float y, float angle);
    void Play(std::list<Bullet>& Bul_list, std::list<Bullet>::iterator& itErase, int bull_behavior);
};

