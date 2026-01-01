#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include"GameContext.hpp"

class CarController {
public:
    float camX = 210.f;
    float camY = 460.f;
    float camAngle = 0.f;
    float SPEED = 0.f;

    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);

    // ---- ƒpƒ‰ƒ[ƒ^ ----

    void update(float dt, const CarStatus& carsta,float& SPEED);
    CarController();
};


