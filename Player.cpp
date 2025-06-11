#include <allegro5/allegro_mouse.h>
#include <cmath>
#include <algorithm>

#include "Player/Player.hpp"
#include "Enemy/Enemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"

// 取得目前 PlayScene 指標
PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

// 建構子，imgBase是底座圖片，imgPlayer是玩家圖片
Player::Player(std::string imgBaseFile, std::string imgPlayerFile, float x, float y, float radius, float speed)
    : Engine::Sprite(imgPlayerFile, x, y), speed(speed), imgBase(imgBaseFile, x, y), CollisionRadius(radius), reload(0) {
}

// 移動與鎖敵和射擊更新
void Player::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();

    // 底座位置與透明度同玩家
    imgBase.Position = Position;
    imgBase.Tint = Tint;

    // 讀取鍵盤狀態
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    float dx = 0, dy = 0;

    if (al_key_down(&keyState, ALLEGRO_KEY_W)) dy -= 1;
    if (al_key_down(&keyState, ALLEGRO_KEY_S)) dy += 1;
    if (al_key_down(&keyState, ALLEGRO_KEY_A)) dx -= 1;
    if (al_key_down(&keyState, ALLEGRO_KEY_D)) dx += 1;

    // 正規化移動向量避免斜角速度變快
    if (dx != 0 || dy != 0) {
        float len = std::sqrt(dx*dx + dy*dy);
        dx /= len;
        dy /= len;

        Position.x += dx * speed * deltaTime;
        Position.y += dy * speed * deltaTime;
    }

    // 更新旋轉朝向滑鼠
    Engine::Point mousePos = Engine::GameEngine::GetInstance().GetMousePosition();
    float angle = std::atan2(mousePos.y - Position.y, mousePos.x - Position.x);
    Rotation = angle + ALLEGRO_PI / 2;  // 加90度校正圖片朝向

    // 尋找鎖定目標 (範圍內第一個敵人)
    Target = nullptr;
    for (auto& obj : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(obj);
        if (!enemy) continue;

        float dist = (enemy->Position - Position).Magnitude();
        if (dist <= CollisionRadius) {
            Target = enemy;
            break;
        }
    }

    // 射擊冷卻計時
    reload -= deltaTime;
    if (reload < 0) reload = 0;

    // 自動射擊範例：如果有目標且冷卻完畢，呼叫 Shoot
    if (Target && reload <= 0) {
        Shoot();
        reload = coolDown;
    }
}

// 畫底座跟玩家
void Player::Draw() const {
    imgBase.Draw();
    Sprite::Draw();
}

// 判斷滑鼠是否在玩家身上（判定範圍：圖片大小）
bool Player::IsMouseOver(int mouseX, int mouseY) const {
    return (mouseX >= Position.x - Size.x / 2 &&
            mouseX <= Position.x + Size.x / 2 &&
            mouseY >= Position.y - Size.y / 2 &&
            mouseY <= Position.y + Size.y / 2);
}

// 射擊子彈的簡單示範 (你可自行擴充)
void Player::Shoot() {
    PlayScene* scene = getPlayScene();
    if (!scene) return;

    // 這裡可以寫創建子彈的邏輯
    // 例如：scene->BulletGroup->AddNewObject(new PlayerBullet(Position.x, Position.y, Rotation));
}
