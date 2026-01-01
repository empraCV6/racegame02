#pragma once
#include"Sceneterminal.hpp"
#include"GameContext.hpp"

class ResultScene : public Sceneterminal {
public:
    ResultScene(GameContext* context);
    enum State{waiting,playing,finish};
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool isSceneEnd() const override;
    void handleEvent(const sf::Event& event) override;
    Sceneterminal* nextScene() override;
private:
    int Selectnumber;
    State state;
    sf::Texture SelectUItx[2];
    sf::Texture SelectbackUItx;
    sf::Sprite SelectUIsp[2];
    sf::Sprite SelectbackUIsp;
};
