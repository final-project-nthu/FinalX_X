#include <functional>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"

std::string playerName = "";
Engine::Label* playerNameLabel = nullptr;

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    
    // 顯示輸入
    AddNewObject(new Engine::Label("Enter your name:", "pirulen.ttf", 32, halfW+520, halfH * 7 / 4 - 110+40+30, 255, 255, 255, 255, 0.5, 0.5));
    // 建立並記錄指標
    playerNameLabel = new Engine::Label(playerName, "pirulen.ttf", 32, halfW+520, halfH * 7 / 4 - 70+40+30, 255, 255, 0, 255, 0.5, 0.5);
    AddNewObject(playerNameLabel);

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
}

void WinScene::OnKeyDown(int keyCode) {
    if (playerName.size() < 12) {
        // 數字
        if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9)
            playerName += '0' + (keyCode - ALLEGRO_KEY_0);
        // 英文大寫
        else if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z)
            playerName += 'A' + (keyCode - ALLEGRO_KEY_A);
        // 空白
        else if (keyCode == ALLEGRO_KEY_SPACE)
            playerName += ' ';
    }
    // Backspace
    if (keyCode == ALLEGRO_KEY_BACKSPACE && !playerName.empty()) {
        playerName.pop_back();
    }
    // 更新 Label 內容
    if (playerNameLabel) playerNameLabel->Text = playerName;
}

void WinScene::BackOnClick(int stage) {
    int score = 0;
    auto playScene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (playScene) {
        score = playScene->killcnt + playScene->GetMoney() + playScene->getLive() * 100;
    }

    playerName = playerName.empty() ? "anonymous" : playerName;

    std::time_t t = std::time(nullptr);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    tm = *std::localtime(&t);
#endif
    std::ostringstream dateStream;
    dateStream << std::put_time(&tm, "%Y-%m-%d");
    printf("Try write: %s %d %s\n", playerName.c_str(), score, dateStream.str().c_str());
    std::ofstream fout("C:/2025I2P2_Tower_Defense/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt", std::ios::app); 
    fout << playerName << " " << score << " " << dateStream.str() << std::endl;
    fout.close();

    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
