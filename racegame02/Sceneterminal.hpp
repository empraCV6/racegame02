#pragma once
#include <SFML/Graphics.hpp>
#include "GameContext.hpp"

class Sceneterminal {
protected:
    GameContext* ctx;
    bool sceneFinished = false;
public:
    Sceneterminal(GameContext* context)
        : ctx(context) {
    }

    virtual ~Sceneterminal() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isSceneEnd() const = 0;
    virtual Sceneterminal* nextScene() { return nullptr; }
    virtual void handleEvent(const sf::Event& event) {}
};


