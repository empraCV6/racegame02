#include"RaceScene.hpp"
#include"ResultScene.hpp"
#include"CarController.hpp"

RaceScene::RaceScene(GameContext* context)
    : Sceneterminal(context){
        state = waiting;
        sceneFinished = false;
        racelimittime = 0;
        Finishwaittime = 0.f;
        PCartex.loadFromFile(ctx->carsetting.Bodies + ".png");
        PCarsp.setTexture(PCartex);
        sf::Vector2u size = PCartex.getSize();
        PCarsp.setOrigin(size.x / 2.f, size.y / 2.f);
        PCarsp.setPosition(SCREEN_W / 2, 150 );
        PCarsp.setScale(2.2f, 2.2f);
        PUItx.loadFromFile("UIracing.png");
        PUIsp.setTexture(PUItx);
        roadTex.loadFromFile("road01.png");
        SPEEDUI.setFont(ctx->UIFont);
        FinishUItx.loadFromFile("FinishUI.png");
        FinishUIsp.setTexture(FinishUItx);
        Racetimetext.setPosition(450, 0);
        Racetimetext.setFont(ctx->UIFont);
        Racetimetext.setCharacterSize(13);
        Racetimetext.setFillColor(sf::Color::White);
    }


void RaceScene::update(float dt) {
    if (state == playing) {
        CarCtrl.update(dt, ctx->carstatus, CarCtrl.SPEED);
        racelimittime += dt;
        if (racelimittime >= 20.0f) {
            state = finish;
        }
    }
    if (state == finish) {
        Finishwaittime += dt;
    }
}

void RaceScene::draw(sf::RenderWindow& window) {
    

    // ======================================================
    //                  canvas begin draw
    // ======================================================
    ctx->canvas.clear(sf::Color(120, 180, 255));

    // Mode7 floor uses camX, camY, camAngle
    sf::Vector2f forwardForDraw(std::cos(CarCtrl.camAngle), std::sin(CarCtrl.camAngle)); // re-evaluate for draw
    sf::Vector2f leftDir(-forwardForDraw.y, forwardForDraw.x);

    // ---------- Mode7 Floor ----------
    for (int sy = int(HORIZON)+1; sy < SCREEN_H; ++sy) {
        float row = float(sy) - HORIZON;
        float depth = FOCAL / row;
        float halfW = SCREEN_W * 0.5f;
        float worldHalfWidth = (halfW * depth) / WORLD_SCALE;

        sf::Vector2f worldLeft(
            CarCtrl.camX + forwardForDraw.x * depth + leftDir.x * (-worldHalfWidth),
            CarCtrl.camY + forwardForDraw.y * depth + leftDir.y * (-worldHalfWidth)
        );

        sf::Vector2f step(
            (leftDir.x * (worldHalfWidth * 2.0f)) / float(SCREEN_W),
            (leftDir.y * (worldHalfWidth * 2.0f)) / float(SCREEN_W)
        );

        sf::VertexArray va(sf::Points, SCREEN_W);
        sf::Vector2f sample = worldLeft;

        for (int x = 0; x < SCREEN_W; ++x) {
            va[x].position = sf::Vector2f(float(x), float(sy));
            va[x].texCoords = sample;
            sample += step;
        }

        sf::RenderStates rs;
        rs.texture = &roadTex;
        ctx->canvas.draw(va, rs);
    }
    // ---------------- Player car ----------------
    ctx->canvas.draw(PCarsp);

    // ---------------- UI ----------------
    ctx->canvas.draw(PUIsp);
    std::string info = std::to_string((int)CarCtrl.SPEED * 2);
    SPEEDUI.setString(info);
    SPEEDUI.setPosition(35.f, SCREEN_H - 76.f);
    ctx->canvas.draw(SPEEDUI);
    //ƒ^ƒCƒ€§Œä
    if (state == playing) {
        float time = Racetime.getElapsedTime().asSeconds();
        std::string Racetimetex = std::to_string(time);
        Racetimetext.setString(Racetimetex);
    }
    ctx->canvas.draw(Racetimetext);
    
    if (state != playing) {
        switch (state) {
        case waiting:
            ctx->fadeIn();
            if (ctx->fadecheck == false) {
                state = playing;
                Racetime.restart();
            }
            break;
        case finish:
            ctx->canvas.draw(FinishUIsp);
            if (Finishwaittime > 3.0f) {
                ctx->Resulttime = Racetimetext;
                ctx->fadeOut(&sceneFinished);
            }
            break;
        }
}

    ctx->canvas.display();
    sf::Sprite canvasSprite(ctx->canvas.getTexture());
    canvasSprite.setPosition(0.f, 0.f);

    // ======================================================
    //                draw to window
    // ======================================================
    window.draw(canvasSprite);
}

bool RaceScene::isSceneEnd() const {
    return sceneFinished;
}

Sceneterminal* RaceScene::nextScene() {
    return new ResultScene(ctx);
}
