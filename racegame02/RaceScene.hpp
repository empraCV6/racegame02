#pragma once
#include"Sceneterminal.hpp"
#include"GameContext.hpp"
#include "CarController.hpp"
#include<SFML/Graphics.hpp>

class RaceScene : public Sceneterminal {
public:
	const int SCREEN_W = 512;
	const int SCREEN_H = 224;
	const float HORIZON = SCREEN_H * 0.40f;
	const float FOCAL = 110.0f;
	const float WORLD_SCALE = 50.0f;
	float Finishwaittime;
	enum State{waiting,playing,finish};
	State state;
	float racelimittime;
	RaceScene(GameContext* ctx);
	void update(float dt)override;
	bool isSceneEnd()const override;
	void draw(sf::RenderWindow& window)override;
	Sceneterminal* nextScene() override;
	sf::Texture PCartex;
	sf::Texture PUItx;
	sf::Sprite PCarsp;
	sf::Sprite PUIsp;
	sf::Texture roadTex;
	sf::Text SPEEDUI;
	sf::Texture FinishUItx;
	sf::Sprite FinishUIsp;
	sf::Clock Racetime;
	sf::Text Racetimetext;
private:
	sf::Vector2f position{ 210.f, 460.f };
	sf::Vector2f velocity{ 0.f, 0.f };
	CarController CarCtrl;
};
