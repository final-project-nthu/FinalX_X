#include <allegro5/allegro.h>
#include "Player/Wizard.hpp"
#include "Engine/GameEngine.hpp"

Wizard::Wizard(std::string imgBase, std::string imgPlayer, float x, float y, float radius, float speed)
    : Player(imgBase, imgPlayer, x, y, radius, speed) {
}

void Wizard::Update(float deltaTime) {
    Player::Update(deltaTime);  // 繼承Player的Update做移動、射擊等基本行為

    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if (al_key_down(&keyState, ALLEGRO_KEY_Q)) {
        CastQ();
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_E)) {
        CastE();
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_R)) {
        CastR();
    }
}

void Wizard::CastQ() {
    // 這裡放 Q 技能的程式碼，暫時空白
}

void Wizard::CastE() {
    // 這裡放 E 技能的程式碼，暫時空白
}

void Wizard::CastR() {
    // 這裡放 R 技能的程式碼，暫時空白
}
