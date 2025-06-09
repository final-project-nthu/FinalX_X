#include "ScoreboardScene.hpp"
#include <fstream>
#include <algorithm>
#include <ctime>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Engine/GameEngine.hpp"

void ScoreboardScene::Initialize() {
    font = al_load_ttf_font("Resource/fonts/pirulen.ttf", 36, 0);
    LoadScores();
    SortScores();
}

void ScoreboardScene::Draw() const {
    if (!font) printf("Font load failed!\n");
    al_clear_to_color(al_map_rgb(0, 0, 0)); // 清空畫面為黑色
    
    int centerX = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int centerY = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    // 畫標題
    al_draw_text(font, al_map_rgb(255,255,255), centerX, 50, ALLEGRO_ALIGN_CENTRE, "Scoreboard");
    // 畫分數
    int start = currentPage * entriesPerPage;
    for (int i = 0; i < entriesPerPage && start + i < entries.size(); ++i) {
        const auto& e = entries[start + i];
        al_draw_textf(font, al_map_rgb(255,255,0), centerX, 120 + i * 60, ALLEGRO_ALIGN_CENTRE, "%s  %d  %s", e.name.c_str(), e.score, e.datetime.c_str());
    }
    // 畫翻頁按鈕
    al_draw_text(font, al_map_rgb(200,200,200), centerX - 300, centerY + 250, ALLEGRO_ALIGN_CENTRE, "PREV PAGE");
    al_draw_text(font, al_map_rgb(200,200,200), centerX + 300, centerY + 250, ALLEGRO_ALIGN_CENTRE, "NEXT PAGE");
    // 畫返回按鈕
    al_draw_text(font, al_map_rgb(255,100,100), centerX, 500+250, ALLEGRO_ALIGN_CENTRE, "BACK");
}

void ScoreboardScene::OnKeyDown(int keyCode) {
    if (keyCode == ALLEGRO_KEY_LEFT && currentPage > 0) currentPage--;
    if (keyCode == ALLEGRO_KEY_RIGHT && (currentPage+1)*entriesPerPage < entries.size()) currentPage++;
    if (keyCode == ALLEGRO_KEY_ESCAPE) Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreboardScene::OnMouseDown(int button, int mx, int my) {
    int centerX = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int centerY = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;
    // PREV PAGE
    if (mx >= centerX - 450 && mx <= centerX - 150 && my >= centerY + 250 && my <= centerY + 290) {
        if (currentPage > 0) currentPage--;
    }
    // NEXT PAGE
    if (mx >= centerX + 150 && mx <= centerX + 450 && my >= centerY + 250 && my <= centerY + 290) {
        if ((currentPage + 1) * entriesPerPage < entries.size()) currentPage++;
    }
    // BACK
    if (mx >= centerX - 80 && mx <= centerX + 80 && my >= 500+250 && my <= 560+250) {
        Engine::GameEngine::GetInstance().ChangeScene("stage-select");
    }
}
void ScoreboardScene::LoadScores() {
    entries.clear();
    std::ifstream fin("C:/2025I2P2_Tower_Defense/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string name, datetime;
    int score;
    while (fin >> name >> score >> datetime) {
        entries.push_back({name, score, datetime});
    }
}

void ScoreboardScene::SaveScores() {
    std::ofstream fout("Resource/scoreboard.txt");
    for (const auto& e : entries)
        fout << e.name << " " << e.score << " " << e.datetime << "\n";
}

void ScoreboardScene::SortScores() {
    std::sort(entries.begin(), entries.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score; // 由高到低
    });
}