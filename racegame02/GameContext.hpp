#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include "json.hpp"

using json = nlohmann::json;


struct CarSetting {
	std::string Engine = "standard";
	std::string Bodies = "standard";
	std::string Tire = "standard";
};

struct CarStatus {
	float MAX_SPEED = 0;
	float ACCELLATE = 0;
	float TURN_SPEED = 0;
	float WEIGHT = 0;
	float BRAKE = 0;
	float FRICTION = 0;
};

struct GameContext {
	int alpha;
	bool fadecheck;
	sf::RenderWindow* window = nullptr;
	sf::RenderTexture canvas;
	sf::RectangleShape fade;
	sf::Font UIFont;
	sf::Texture SelectpinUItx;
	sf::Sprite SelectpinUIsp;
	sf::Text Resulttime;
	CarSetting carsetting;
	CarStatus carstatus;
	json partsData;

	void fadeOut(bool* sceneFinished) {
		if (alpha + 10 < 255) {
			alpha += 10;
			fade.setFillColor(sf::Color(0, 0, 0, alpha));
			canvas.draw(fade);
		}
		else {
			alpha = 255;
			fade.setFillColor(sf::Color(0, 0, 0, alpha));
			canvas.draw(fade);
			*sceneFinished = true;
		}
	}
	void fadeIn() {
		if (alpha - 10 > 0) {
			alpha -= 10;
			fade.setFillColor(sf::Color(0, 0, 0, alpha));
			canvas.draw(fade);
		}
		else {
			alpha = 0;
			fade.setFillColor(sf::Color(0, 0, 0, alpha));
			canvas.draw(fade);
			fadecheck = false;
		}
	}
};


