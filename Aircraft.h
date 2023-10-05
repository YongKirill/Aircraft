#pragma once
#include "Bullet.h"
#include "Settings.h"


class Aircraft
{
private:
    int R = 250, G = 250, B = 250;
    float x_coordinate, y_coordinate, speed, angle;
    sf::Texture texture;//сфмл текстура
public:
    sf::Sprite sprite;//сфмл спрайт
    Aircraft(float x, float y, float speed, float angle, std::string img);
    void Play(float x_cours, float y_cours, std::list<Bullet>& Bul_list, clock_t& t0);
};