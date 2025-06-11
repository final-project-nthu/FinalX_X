#ifndef WIZARD_HPP
#define WIZARD_HPP

#include "Player/Player.hpp"
#include<string>
class Wizard : public Player {
public:
    Wizard(std::string imgBase, std::string imgPlayer, float x, float y, float radius, float speed);

    void Update(float deltaTime) override;

protected:
    // 技能按鍵事件，現在先空著
    void CastQ();
    void CastE();
    void CastR();
};

#endif // WIZARD_HPP
