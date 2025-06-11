# FinalX_X
//cmakelist加入
Player/Player.cpp
Player/Player.hpp
Player/Wizard.cpp
Player/Wizard.hpp

//enemy.hpp加入
float speedMultiplier = 1.0f;
float slowTimer = 0.0f;
void ApplySlow(float rate, float duration);
ALLEGRO_COLOR TintOverride;  
bool useTintOverride = false;


//enemy.cpp加入
void Enemy::ApplySlow(float rate, float duration) {
    if (rate < speedMultiplier || slowTimer <= 0) {
        speedMultiplier = rate;
        slowTimer = duration;
    }
}

//update裡加入
if (slowTimer > 0) {
        slowTimer -= deltaTime;
        const_cast<Enemy*>(this)->useTintOverride = true;
        const_cast<Enemy*>(this)->TintOverride = al_map_rgba(0, 0, 255, 150);  
        if (slowTimer <= 0) {
            speedMultiplier = 1.0f;
            slowTimer = 0;
            const_cast<Enemy*>(this)->useTintOverride = false;
        }
    }
    float remainSpeed = speed * deltaTime * speedMultiplier;

//draw
void Enemy::Draw() const {
    if (useTintOverride) {
        ALLEGRO_COLOR oldTint = Tint;
        const_cast<Enemy*>(this)->Tint = TintOverride;
        Sprite::Draw();
        const_cast<Enemy*>(this)->Tint = oldTint;
    } 
    else {
        Sprite::Draw();
    }
    //original
    if (PlayScene::DebugMode) {
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }

    float barWidth = 40;     
    float barHeight = 4;     
    float offsetY = -18;     
    float healthRatio = hp / hpMax;

    // 背景（灰色）
    al_draw_filled_rectangle(
        Position.x - barWidth / 2, Position.y + offsetY,
        Position.x + barWidth / 2, Position.y + offsetY + barHeight,
        al_map_rgb(160, 160, 160)
    );

    // 血量（紅色）
    al_draw_filled_rectangle(
        Position.x - barWidth / 2, Position.y + offsetY,
        Position.x - barWidth / 2 + barWidth * healthRatio, Position.y + offsetY + barHeight,
        al_map_rgb(255, 0, 0)
    );
}

//playscene :: initialize加入
player = new Wizard("play/turret-1.png", 100, 100, 300);  
AddNewObject(player);

//playscene::upate加入
if (player)
        player->Update(deltaTime);

//playscene :: draw加入
if (player)
        player->Draw();

//playscene.hpp加入 建議在public
Player* player; 

// 記得include 
Player/Player.hpp
Player/Wizard.hpp
