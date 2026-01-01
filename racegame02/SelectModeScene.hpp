#pragma once
#include"Sceneterminal.hpp"
#include"SelectPartsScene.hpp"

class SelectModeScene : public Sceneterminal {
public:
	SelectModeScene(GameContext* context);
	void update(float dt)override;
	bool isSceneEnd()const override;
	void draw(sf::RenderWindow& window)override;
	void handleEvent(const sf::Event& event) override;
	Sceneterminal* nextScene() override;
	enum State{waiting,playing,finish};
private:
	State state;
	sf::Texture SelectModeUItx;
	sf::Sprite SelectModeUIsp;
	sf::Texture ModeUItx[5];
	sf::Sprite ModeUIsp[5]; //ここまでテクスチャ、スプライト準備
	std::string discript[5];
	sf::Text modediscripttext;
	int Selectnumber;
};