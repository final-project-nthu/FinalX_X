
#include "Engine/Resources.hpp"
#include "MoneyEffect.hpp"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>    
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_color.h>  

MoneyEffect::MoneyEffect(std::string text, float x, float y)
    : text(text), alpha(1.0f), lifetime(0), speed(30.0f), color(al_map_rgb(255, 255, 0)) {
    Position.x = x;
    Position.y = y;
}

void MoneyEffect::Update(float deltaTime) {
    lifetime += deltaTime;
    Position.y -= speed * deltaTime;   
    alpha = 1.0f - (lifetime / 1.2f);  
    if (alpha <= 0)
        alpha = 0;
}

void MoneyEffect::Draw() const {
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_COLOR fadeColor = al_map_rgba_f(color.r, color.g, color.b, alpha);
    al_draw_text(font, fadeColor, Position.x, Position.y, ALLEGRO_ALIGN_CENTER, text.c_str());
    al_destroy_font(font);  
}


