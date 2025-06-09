#ifndef MONEYBULLET_HPP
#define MONEYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class MoneyBullet : public Bullet {
public:
    explicit MoneyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // MONEYBULLET_HPP
