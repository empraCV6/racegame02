#include"SelectModeScene.hpp"
#include"GameContext.hpp"

SelectModeScene::SelectModeScene(GameContext* context) : Sceneterminal(context) {
	ctx->UIFont.loadFromFile("Orbitron-VariableFont_wght.ttf");
	SelectModeUItx.loadFromFile("modeselectUI.png");
	SelectModeUIsp.setTexture(SelectModeUItx);
	ModeUItx[0].loadFromFile("soloraceUI.png");
	ModeUItx[1].loadFromFile("freeplayUI.png");
	ModeUItx[2].loadFromFile("onlineUI.png");
	ModeUItx[3].loadFromFile("loadUI.png");
	ModeUItx[4].loadFromFile("saveUI.png");
	//説明文用意
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			discript[i] = "You can play this mode.";
		}
		else {
			discript[i] = "You can't use this mode.";
		}
	}
	modediscripttext.setFont(ctx->UIFont);
	modediscripttext.setCharacterSize(13);
	modediscripttext.setFillColor(sf::Color::White);
	modediscripttext.setPosition(30, 150);
	state = waiting;
	for (int i = 0; i < 5; i++) {
		ModeUIsp[i].setTexture(ModeUItx[i]);
	}

	Selectnumber = 0;
	ctx->alpha = 255;
	//いったん仮置きでフェードの大きさ指定
	ctx->fade.setSize(sf::Vector2f(512, 224));
	ctx->fadecheck = false;
	//ピン設定
	ctx->SelectpinUItx.loadFromFile("SelectpinUI.png");
	ctx->SelectpinUIsp.setTexture(ctx->SelectpinUItx);
}

void SelectModeScene::handleEvent(const sf::Event& event) {
	if (state == playing) {
		if (event.type != sf::Event::KeyPressed)return;
		switch (event.key.code) {
		case sf::Keyboard::W:
			if (Selectnumber > 0)Selectnumber--;
			break;
		case sf::Keyboard::S:
			if (Selectnumber < 4)Selectnumber++;
			break;
		case sf::Keyboard::J:
			if (Selectnumber == 0) {
				state = finish;
			}
			break;
		}
	}
}

void SelectModeScene::draw(sf::RenderWindow& window) {
	ctx->canvas.clear(sf::Color::Black);
	int x = 400;
	int y = 20;
	//UI描画
	ctx->canvas.draw(SelectModeUIsp);
	for (int i = 0; i < 5; i++) {
		if (i != Selectnumber) {
			ModeUIsp[i].setPosition(x - i * 25, y + i * 40);
			ctx->canvas.draw(ModeUIsp[i]);
		}
		else {
			ModeUIsp[i].setPosition(x - i * 25 - 100 , y + i * 40);
			ctx->canvas.draw(ModeUIsp[i]);
			ctx->SelectpinUIsp.setPosition(x - i * 25 - 125, y + i * 40);
			ctx->canvas.draw(ctx->SelectpinUIsp);
		}
	}
	//文章準備
	modediscripttext.setString(discript[Selectnumber]);
	ctx->canvas.draw(modediscripttext);
	//フェード処理
	switch (state) {
	case waiting:
		ctx->fadeIn();
		if (ctx->alpha <= 0)state = playing;
		break;
	case finish:
		ctx->fadeOut(&sceneFinished);
	}
	ctx->canvas.display();
	sf::Sprite canvasSprite(ctx->canvas.getTexture());
	window.draw(canvasSprite);
}

void SelectModeScene::update(float dt) {}

bool SelectModeScene::isSceneEnd() const {
	return sceneFinished;
}

Sceneterminal* SelectModeScene::nextScene() {
	sceneFinished = false;
	return new SelectpartsScene(ctx);
}