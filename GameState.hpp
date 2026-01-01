class GameState {
public:
    virtual void render(GameContext& ctx) = 0;
    virtual ~GameState() = default;
};