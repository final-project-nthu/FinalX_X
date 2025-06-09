
#ifndef MONEY_EFFECT_HPP
#define MONEY_EFFECT_HPP

#include <allegro5/color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include "Engine/GameEngine.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"

class MoneyEffect : public Engine::IObject {
private:
    float alpha;
    float lifetime;
    std::string text;
    ALLEGRO_COLOR color;
    float speed;
public:
    MoneyEffect(std::string text, float x, float y);
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif
