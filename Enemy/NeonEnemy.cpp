#include "NeonEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Resources.hpp"
#include <allegro5/allegro.h>
#include "Engine/AudioHelper.hpp"

NeonEnemy::NeonEnemy(int x, int y)
    : Enemy("play/neon_Vsmall_rBG.png", x, y, 30, 100, 100, 300)
{
    spawnTime = al_get_time();
}

void NeonEnemy::Update(float deltaTime) {
    if (!enraged && al_get_time() - spawnTime >= 5.0f) {
        enraged = true;
        speed *= 3; 
        bmp = Engine::Resources::GetInstance().GetBitmap("play/neon_ult.png");
        AudioHelper::PlaySample("neon_ult.mp3", false, 4.0f);
    }
    
    /*Enemy::Update(deltaTime);
    Rotation = 0;*/
    float remainSpeed = speed * deltaTime;
    while (remainSpeed != 0) {
        if (path.empty()) {
            // 到達終點時扣 4 點血
            Hit(hp);
            PlayScene* scene = getPlayScene();
            if (scene) {
                for (int i = 0; i < 4; i++)
                    scene->Hit();
            }
            reachEndTime = 0;
            return;
        }
        Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
        Engine::Point vec = target - Position;
        reachEndTime = (vec.Magnitude() + (path.size() - 1) * PlayScene::BlockSize - remainSpeed) / speed;
        Engine::Point normalized = vec.Normalize();
        if (remainSpeed - vec.Magnitude() > 0) {
            Position = target;
            path.pop_back();
            remainSpeed -= vec.Magnitude();
        } else {
            Velocity = normalized * remainSpeed / deltaTime;
            remainSpeed = 0;
        }
    }
    
    Sprite::Update(deltaTime);
}

void NeonEnemy::OnExplode() {
    Enemy::OnExplode();
    AudioHelper::PlaySample("clutch.mp3", false, 6.0f);
}

