#include <fstream>
#include "Sceneterminal.hpp"
#include "SelectModeScene.hpp"
#include"RaceScene.hpp"
#include "GameContext.hpp"

const float FPS = 60.0f;
const float frameTime = 1.0f / FPS;
const float GAME_WIDTH = 512;
const float GAME_HEIGHT = 224;

void resizeView(sf::RenderWindow& window, sf::View& view)
{
    float w = window.getSize().x;
    float h = window.getSize().y;

    float windowAspect = w / h;
    float gameAspect = GAME_WIDTH / GAME_HEIGHT;

    sf::FloatRect viewport;

    if (windowAspect > gameAspect) {
        float width = gameAspect / windowAspect;
        viewport = { (1 - width) / 2.f, 0, width, 1 };
    }
    else {
        float height = windowAspect / gameAspect;
        viewport = { 0, (1 - height) / 2.f, 1, height };
    }

    view.setViewport(viewport);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 448), "Game");

    GameContext context;
    context.window = &window;
    context.canvas.create(512, 224);

    std::ifstream file("Car_Parts.json");
    file >> context.partsData;

    sf::View gameView(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
    window.setView(gameView);

    Sceneterminal* currentScene = new SelectModeScene(&context);

    sf::Clock frameClock;

    while (window.isOpen())
    {
        float dt = frameClock.restart().asSeconds();

        // ƒCƒxƒ“ƒgˆ—
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                resizeView(window, gameView);
                window.setView(gameView);
            }

            currentScene->handleEvent(event);
        }

        currentScene->update(dt);

        window.clear();
        currentScene->draw(window);
        window.display();

        if (currentScene->isSceneEnd()) {
            Sceneterminal* next = currentScene->nextScene();
            delete currentScene;
            currentScene = next;
        }

        // FPSŒÅ’è
        float sleepTime = frameTime - dt;
        if (sleepTime > 0)
            sf::sleep(sf::seconds(sleepTime));
    }

    delete currentScene;
}
