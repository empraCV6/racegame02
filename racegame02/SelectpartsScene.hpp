#pragma once
#include "Sceneterminal.hpp"
#include "GameContext.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class SelectpartsScene : public Sceneterminal {
public:
    SelectpartsScene(GameContext* context);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool isSceneEnd() const override;
    void handleEvent(const sf::Event& event) override;
    Sceneterminal* nextScene() override;
private:
    int Selectnumber = 0;
    int Partsnumber = 0;
    bool KeyPress = false;
    sf::Texture PartsTextures[3][3];
    sf::Sprite PartsUI;
    std::string Descriptions[3][3];
    sf::Text uiText;
    sf::Texture SelectSceneUItx;
    sf::Sprite SelectSceneUIsp;
    sf::Texture statusgagetx;
    sf::Sprite statusgagesp;
};
