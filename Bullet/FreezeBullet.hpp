#ifndef FREEZEBULLET_HPP
#define FREEZEBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class FreezeBullet : public Bullet {
public:
    explicit FreezeBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // FreezeBULLET_HPP
