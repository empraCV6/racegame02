#pragma once
#include"Sceneterminal.hpp"
#include"GameContext.hpp"
#include<SFML/Graphics.hpp>

class TitleScene : public Sceneterminal {
public:
	TitleScene(GameContext* context);
	void update(float dt)override;
	bool isSceneEnd()const override;
	void draw(sf::RenderWindow& window)override;
	void handleEvent(const sf::Event& event) override;
	Sceneterminal* nextScene() override;
	sf::Texture TitleLogoTex;
	sf::Sprite TitleLogoSp;
	sf::Texture SelectcursorTex;
	sf::Sprite SelectcursorSp;
	int Selectnumber1; //PRESS START BUTTON のとこかスタート、設定を選択する場所か分別する番号
	int Selectnumber2; //スタート、設定を選択する際に参照させる番号
};
