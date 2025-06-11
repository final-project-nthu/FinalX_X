// Player.cpp
#include "Player.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include <allegro5/allegro.h>
#include "Bullet/FreezeBullet.hpp"
#include "Engine/Point.hpp"
PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y, float speed)
    : Engine::Sprite(img, x, y), speed(speed) {
}

void Player::Update(float deltaTime) {
    Sprite::Update(deltaTime);

    PlayScene* scene = getPlayScene();
    const float mapWidth = PlayScene::MapWidth * PlayScene::BlockSize;
    const float mapHeight = PlayScene::MapHeight * PlayScene::BlockSize;

    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    Engine::Point velocity(0, 0);
    if (al_key_down(&keyState, ALLEGRO_KEY_W)) velocity.y -= speed;
    if (al_key_down(&keyState, ALLEGRO_KEY_S)) velocity.y += speed;
    if (al_key_down(&keyState, ALLEGRO_KEY_A)) velocity.x -= speed;
    if (al_key_down(&keyState, ALLEGRO_KEY_D)) velocity.x += speed;

    if (velocity.Magnitude() > 0)
        velocity = velocity.Normalize() * speed * deltaTime;

    Position.x += velocity.x;
    Position.y += velocity.y;
    Position.x = std::max(0.0f, std::min(Position.x, mapWidth));
    Position.y = std::max(0.0f, std::min(Position.y, mapHeight));

    // --- 發射子彈 ---
    static bool prevSpace = false;
    bool currSpace = al_key_down(&keyState, ALLEGRO_KEY_SPACE);
    if (currSpace && !prevSpace) {
        // 取得滑鼠世界座標（已經轉換過）
        Engine::Point mousePos = Engine::GameEngine::GetInstance().GetMousePosition();

        // 計算方向向量
        Engine::Point direction = (mousePos - Position).Normalize();

        // 發射 FreezeBullet
        float bulletSpeed = 600;
        scene->BulletGroup->AddNewObject(new FreezeBullet(Position, direction, bulletSpeed, 0));
    }
    prevSpace = currSpace;
}



void Player::Draw() const {
    Engine::Sprite::Draw();
}
Engine::Point Player::GetPosition() const {
    return Position;
}
