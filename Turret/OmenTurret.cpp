#include "OmenTurret.hpp"
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "MachineGunTurret.hpp"
#include "Scene/PlayScene.hpp"

const int OmenTurret::Price = 1000;
bool OmenTurret::Placed = false;

OmenTurret::OmenTurret(float x, float y)
    : Turret("play/tool-base.png", "play/omen.png", x, y, 150.0f, Price, 0.05f) {
}

void OmenTurret::Update(float deltaTime) {
    Turret::Update(deltaTime);
    //Omen no rotating
    Rotation = 0 ;

}

void OmenTurret::ActivateTeleport() {
    auto* scene = getPlayScene();
    if (scene->killcnt >= 20) {
        scene->omenTeleportPending = true;
        scene->omenToTeleport = this;
        // 預覽
        AudioHelper::PlaySample("omen_ult_prev.mp3", false, 16.0f);
        if (scene->preview)
            scene->UIGroup->RemoveObject(scene->preview->GetObjectIterator());
        scene->preview = new OmenTurret(Position.x, Position.y);
        scene->preview->Tint = al_map_rgba(255, 255, 255, 128);
        scene->preview->Enabled = false;
        scene->preview->Preview = true;
        scene->UIGroup->AddNewObject(scene->preview);
    }
}

void OmenTurret::CreateBullet() {
    if (!Target) return;
    // 直接用目標方向計算子彈方向
    Engine::Point direction = (Target->Position - Position).Normalize();
    float rotation = atan2(direction.y, direction.x);
    // 子彈從砲台中心往目標方向發射
    getPlayScene()->BulletGroup->AddNewObject(
        new FireBullet(Position + direction * 36, direction, rotation, this)
    );
    AudioHelper::PlayAudio("gun.wav");
}



