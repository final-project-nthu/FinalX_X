#pragma once
#include <vector>
#include <string>
#include <allegro5/allegro_font.h>
#include "Engine/IScene.hpp"



struct ScoreEntry {
    std::string name;
    int score;
    std::string datetime;
};

class ScoreboardScene : public Engine::IScene {
public:
    ALLEGRO_FONT* font = nullptr;
    std::vector<ScoreEntry> entries;
    int currentPage = 0;
    const int entriesPerPage = 5;
    void Initialize() override;
    void Draw() const override;
    void OnKeyDown(int keyCode) override;
    void OnMouseDown(int button, int mx, int my) override;
    void LoadScores();
    void SaveScores();
    void SortScores();
    
};