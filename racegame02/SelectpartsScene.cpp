#include"SelectpartsScene.hpp"
#include"RaceScene.hpp"
#include<iostream>

void SelectpartsScene::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) return;
    if (!ctx->fadecheck && Selectnumber < 3) {
        switch (event.key.code) {
        case sf::Keyboard::A:
            if (Partsnumber > 0) Partsnumber--;
            break;

        case sf::Keyboard::D:
            if (Partsnumber < 2) Partsnumber++;
            break;

        case sf::Keyboard::J:
            // 今の選択を保存

            Selectnumber++;
            Partsnumber = 0; // 次のパーツ用にリセット

            if (Selectnumber >= 3 && !sceneFinished) {
                ctx->carstatus.ACCELLATE +=
                    ctx->partsData.at("Engines")
                    .at(ctx->carsetting.Engine)
                    .at("Accellate")
                    .get<float>();

                ctx->carstatus.MAX_SPEED +=
                    ctx->partsData.at("Engines")
                    .at(ctx->carsetting.Engine)
                    .at("MAX_SPEED")
                    .get<float>();

                ctx->carstatus.WEIGHT +=
                    ctx->partsData.at("Bodies")
                    .at(ctx->carsetting.Bodies)
                    .at("WEIGHT")
                    .get<float>();

                ctx->carstatus.TURN_SPEED +=
                    ctx->partsData.at("Bodies")
                    .at(ctx->carsetting.Bodies)
                    .at("TURN_SPEED")
                    .get<float>();

                ctx->carstatus.BRAKE +=
                    ctx->partsData.at("Tire")
                    .at(ctx->carsetting.Tire)
                    .at("Brake")
                    .get<float>();

                ctx->carstatus.FRICTION +=
                    ctx->partsData.at("Tire")
                    .at(ctx->carsetting.Tire)
                    .at("FRICTION")
                    .get<float>();

                ctx->fadecheck = true;
            }
            break;
        case sf::Keyboard::K:
            if (Selectnumber > 0) {
                Selectnumber--;
                Partsnumber = 0;
            }
            break;
        }
        if (Selectnumber == 0) {
            ctx->carsetting.Engine =
                (Partsnumber == 0 ? "standard" :
                    Partsnumber == 1 ? "highpower" : "highaccel");
        }
        else if (Selectnumber == 1) {
            ctx->carsetting.Bodies =
                (Partsnumber == 0 ? "standard" :
                    Partsnumber == 1 ? "groundstar" : "airstar");
        }
        else if (Selectnumber == 2) {
            ctx->carsetting.Tire =
                (Partsnumber == 0 ? "standard" :
                    Partsnumber == 1 ? "highgripper" : "slidegripper");
        }
    }
}

	void SelectpartsScene::update(float dt){}

    Sceneterminal* SelectpartsScene::nextScene() {
        return new RaceScene(ctx);
    }


	void SelectpartsScene::draw(sf::RenderWindow& window){
        //基本画面表示
        if (Selectnumber < 3)
        {
            PartsUI.setTexture(PartsTextures[Selectnumber][Partsnumber]);
            std::string infomation = Descriptions[Selectnumber][Partsnumber];
            uiText.setString(infomation);
        }
        ctx->canvas.clear(sf::Color(0,0,0));
        ctx->canvas.draw(SelectSceneUIsp);
        PartsUI.setPosition(224, 70);
        ctx->canvas.draw(PartsUI);
        ctx->canvas.draw(uiText);

        //画面左側のステータスバー表示
        if (Selectnumber >= 0) {
            //エンジン性能表示
            statusgagesp.setPosition(8, 47);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Engines").at(ctx->carsetting.Engine).at("MAX_SPEED")) * 0.8, 11));
            ctx->canvas.draw(statusgagesp);
            statusgagesp.setPosition(8, 79);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Engines").at(ctx->carsetting.Engine).at("Accellate")) * 0.8, 11));
            ctx->canvas.draw(statusgagesp);
        }
        if (Selectnumber >= 1) {
            statusgagesp.setPosition(8, 111);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Bodies").at(ctx->carsetting.Bodies).at("TURN_SPEED")) * 3, 11));
            ctx->canvas.draw(statusgagesp);
            statusgagesp.setPosition(8, 143);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Bodies").at(ctx->carsetting.Bodies).at("WEIGHT")) * 3, 11));
            ctx->canvas.draw(statusgagesp);
        }
        if (Selectnumber >= 2) {
            statusgagesp.setPosition(8, 175);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Tire").at(ctx->carsetting.Tire).at("Brake")) * 3, 11));
            ctx->canvas.draw(statusgagesp);
            statusgagesp.setPosition(8, 207);
            statusgagesp.setTextureRect(sf::IntRect(0, 0, (ctx->partsData.at("Tire").at(ctx->carsetting.Tire).at("FRICTION")) * 3, 11));
            ctx->canvas.draw(statusgagesp);
        }

        //暗転関連
        if (ctx->fadecheck) {
            switch (Selectnumber) {
            case 0:
                ctx->fadeIn();
                break;
            case 3:
                ctx->fadeOut(&sceneFinished);
                break;
            }
        }
        //画面表示
        ctx->canvas.display();
        sf::Sprite canvasSprite(ctx->canvas.getTexture());
        window.draw(canvasSprite);
	}
    bool SelectpartsScene::isSceneEnd() const {
        return sceneFinished;
    }
    SelectpartsScene::SelectpartsScene(GameContext* context)
        : Sceneterminal(context) {

    uiText.setFont(ctx->UIFont);
    uiText.setCharacterSize(13);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(360, 150);
    PartsUI.setPosition(224, 82);
    SelectSceneUItx.loadFromFile("PartsSelectSceneUI.png");
    SelectSceneUIsp.setTexture(SelectSceneUItx);
    statusgagetx.loadFromFile("gage.png");
    statusgagesp.setTexture(statusgagetx);
    ctx->fadecheck = true;
 
    // 例：エンジン
    PartsTextures[0][0].loadFromFile("standardEngine-SelectUI.png");
    PartsTextures[0][1].loadFromFile("highpowerEngine-SelectUI.png");
    PartsTextures[0][2].loadFromFile("highaccelEngine-SelectUI.png");

    // 例：タイヤ
    PartsTextures[1][0].loadFromFile("standard-SelectUI.png");
    PartsTextures[1][1].loadFromFile("groundstar-SelectUI.png");
    PartsTextures[1][2].loadFromFile("airstar-SelectUI.png");

    // 例：ボディ
    PartsTextures[2][0].loadFromFile("standardsystem-SelectUI.png");
    PartsTextures[2][1].loadFromFile("groundstarsystem-SelectUI.png");
    PartsTextures[2][2].loadFromFile("airstarsystem-SelectUI.png");

    PartsUI.setPosition(256, 112);

    Descriptions[0][0] = "Well-balanced\n standard parts";
    Descriptions[0][1] = "Fastest, \nbut a slow starter";
    Descriptions[0][2] = "Acceleration is fast\n -keep your speed down.";

    Descriptions[1][0] = "Well-balanced\n standard parts";
    Descriptions[1][1] = "Heavy body\n Minimizes bending";
    Descriptions[1][2] = "Lightweight body\n Smooth glide";

    Descriptions[2][0] = "Well-balanced\n standard parts";
    Descriptions[2][1] = "Responsive brakes,\n moderate turning";
    Descriptions[2][2] = "Seems easy to maneuver\n Slippery smooth";
    }