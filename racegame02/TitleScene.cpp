#include"TitleScene.hpp"
#include"SelectPartsScene.hpp"
#include"GameContext.hpp"

TitleScene::TitleScene(GameContext* context) : Sceneterminal(context) {
	TitleLogoTex.loadFromFile("ここにファイル名");
	TitleLogoSp.setTexture(TitleLogoTex);
	SelectcursorTex.loadFromFile("ここにファイル名");
	Selectnumber1 = 0;
	Selectnumber2 = 0; //初期値はスタートの0
}

void TitleScene::handleEvent(const sf::Event& event) {
	if (event.type != sf::Event::KeyPressed)return;
	switch (Selectnumber1) {
	case 0://PRESS STARTシーン
		if (event.key.code == sf::Keyboard::Space) {
			Selectnumber1 = 1;
		}
		break;
	case 1://設定、プレイ選択シーン
		switch (event.key.code) {
		case sf::Keyboard::W:
			if (Selectnumber2 > 0) {
				Selectnumber2--;
				//ここにカーソル移動書く
			}
			break;
		case sf::Keyboard::S:
			if (Selectnumber2 < 1) {
				Selectnumber2++;
				//ここにカーソル移動書く
			}
			break;
		case sf::Keyboard::BackSpace://PRESS START シーンへ戻る
			Selectnumber1 = 0;
			break;
		case sf::Keyboard::Space://次シーンへ遷移準備
				sceneFinished = true;
			break;
		}
		break;
	}

}

Sceneterminal* TitleScene::nextScene() {
	if (Selectnumber2 == 0) {
		return new SelectpartsScene(ctx);
	}
	else {
		//設定シーンへ遷移、おそらく処理書くまではここにかかるとフリーズ
	}
}
bool TitleScene::isSceneEnd()const { return sceneFinished; }
void TitleScene::draw(sf::RenderWindow& window){
	ctx->canvas.clear(sf::Color(0, 0, 0));
	//ここから先続きはタイトルUIできてから作る
}
void TitleScene::update(float dt){}