#pragma once

enum GameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game {
  public:
    GameState m_state;
    bool m_keys;
    unsigned int width, height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    void update(float dt);
    void render();
    void process_input(float ft);
};
