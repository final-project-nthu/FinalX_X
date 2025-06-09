//#pragma once
#include "Enemy.hpp"

class NeonEnemy : public Enemy {
protected:
    bool enraged = false;
    float spawnTime = 0;
public:
    NeonEnemy(int x, int y);
    void Update(float deltaT) override;
    void OnExplode() override;
};