#pragma once
#include "GameState.hpp"
#include <memory>

class StateManager {
public:
    std::unique_ptr<GameState> current;

    void Change(std::unique_ptr<GameState> next, GameContext& ctx) {
        if (current) current->Exit(ctx);
        current = std::move(next);
        current->Enter(ctx);
    }

    void Update(GameContext& ctx, float dt) {
        if (current) current->Update(ctx, dt);
    }

    void Render(GameContext& ctx, sf::RenderWindow& win) {
        if (current) current->Render(ctx, win);
    }
};
#pragma once
