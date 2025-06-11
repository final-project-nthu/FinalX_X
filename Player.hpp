// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "Engine/Sprite.hpp"

class PlayScene;

class Player : public Engine::Sprite {
protected:
    float speed;
    PlayScene* getPlayScene();

public:
    bool Enabled = true;
    Player(std::string img, float x, float y, float speed);
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // PLAYER_HPP
