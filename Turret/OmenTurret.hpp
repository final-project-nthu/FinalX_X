#pragma once
#include "Turret.hpp"

class OmenTurret : public Turret {
public:
    static const int Price;
    static bool Placed; // 只能放一隻
    OmenTurret(float x, float y);
    void Update(float deltaTime) override;
    void ActivateTeleport();
    void CreateBullet() override;
};