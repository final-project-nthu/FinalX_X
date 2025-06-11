#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Engine/Sprite.hpp"

class Player : public Engine::Sprite {
public:
    explicit Player(std::string img, float x, float y, float speed);
    virtual void Update(float deltaTime) override;
    virtual void Draw() const override;

protected:
    float speed;
};

#endif
