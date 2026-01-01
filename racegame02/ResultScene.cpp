#include"ResultScene.hpp"
#include"SelectModeScene.hpp"
#include"RaceScene.hpp"

ResultScene::ResultScene(GameContext* context) : Sceneterminal(context){
	ctx->fadecheck = false;
	ctx->Resulttime.setCharacterSize(15);
	ctx->Resulttime.setFillColor(sf::Color::White);
	ctx->Resulttime.setPosition(50, 100);
	sceneFinished = false;
	Selectnumber = 0;
	SelectUItx[0].loadFromFile("ReturnUI.png");
	SelectUItx[1].loadFromFile("RetryUI.png");
	SelectbackUItx.loadFromFile("ResultSceneUI.png");
	for (int i = 0; i < 2; i++)SelectUIsp[i].setTexture(SelectUItx[i]);
	SelectbackUIsp.setTexture(SelectbackUItx);
}

void ResultScene::update(float dt){}

void ResultScene::handleEvent(const sf::Event& event) {
	if (event.type != sf::Event::KeyPressed) return;
	if (state == playing) {
		switch (event.key.code) {
		case sf::Keyboard::W:
			if (Selectnumber > 0)Selectnumber--;
			break;
		case sf::Keyboard::S:
			if (Selectnumber < 1)Selectnumber++;
			break;
		case sf::Keyboard::J:
			state = finish;
			ctx->fadecheck = true;
		}
	}
}

void ResultScene::draw(sf::RenderWindow& window) {
	ctx->canvas.draw(SelectbackUIsp);
	//‘I‘ð•`‰æ
	for (int i = 0; i < 2;i++) {
		if (i != Selectnumber) {
			SelectUIsp[i].setPosition(400 - (i+1)* 20,20 + i * 40);
			ctx->canvas.draw(SelectUIsp[i]);
		}
		else {
			SelectUIsp[i].setPosition(400 - (i + 1) * 20 - 50, 20 + i * 40);
			ctx->canvas.draw(SelectUIsp[i]);
			ctx->SelectpinUIsp.setPosition(400 - (i + 1) * 20 - 75, 20 + i * 40);
			ctx->canvas.draw(ctx->SelectpinUIsp);
		}
	}
	//ƒ^ƒCƒ€•`‰æ
	ctx->canvas.draw(ctx->Resulttime);
	//ˆÃ“]ˆ—
	if (state != playing) {
		switch (state) {
		case waiting:
			ctx->fadeIn();
			if (ctx->alpha <= 0)state = playing;
			break;
		case finish:
			ctx->fadeOut(&sceneFinished);
			break;
		}
	}
	ctx->canvas.display();
	sf::Sprite canvasSprite(ctx->canvas.getTexture());
	window.draw(canvasSprite);
}

Sceneterminal* ResultScene::nextScene() {
	switch (Selectnumber) {
	case 0:
		return new SelectModeScene(ctx);
		break;
	case 1:
		return new RaceScene(ctx);
		break;
	}
}

bool ResultScene::isSceneEnd() const {
	return sceneFinished;
}