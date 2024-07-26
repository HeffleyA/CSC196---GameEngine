#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"
#include "Font.h"
#include "Text.h"
#include "Pickup.h"
#include "Asteroid.h"

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);
    m_font = new Font();
    m_font->Load("QuirkyRobot.ttf", 20);

    m_fontLarge = new Font();
    m_fontLarge->Load("QuirkyRobot.ttf", 72);

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    g_engine.GetAudio().AddSound("space-blueberry.aiff");
    g_engine.GetAudio().AddSound("blaster.wav");
    g_engine.GetAudio().AddSound("explosion.wav");

    return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case eState::Title:
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
        }
        break;
    case eState::StartGame:
        g_engine.GetAudio().PlaySound("space-blueberry.aiff");
        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;
        break;
    case eState::StartLevel:
        m_scene->RemoveAll();
        {
            Transform shipTransform{ { g_engine.GetRenderer().GetWidth() >> 1, g_engine.GetRenderer().GetHeight() >> 1}, 0, 10 };
            Model* shipModel = new Model{ GameData::shipPoints, Color{ 1, 1, 1, 0} };
            auto player = std::make_unique<Player>(300, shipTransform, shipModel);
            player->SetDamping(1.5f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }

        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;

        m_state = eState::Game;
        break;
    case eState::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            int rPickup = random(4);
            m_spawnTimer = m_spawnTime;

            // create enemy
            auto* enemyModel = new Model{ GameData::enemyPoints, Color{1, 1, 1} };
            auto enemy = std::make_unique<Enemy>(5000, Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight()) }, 0, 7.5f }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(std::move(enemy));

            // create pickup
            if (rPickup == 1)
            {
                auto* pickupModel = new Model{ GameData::pickupPoints, Color{1, 1, 1} };
                auto pickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight()) }, 0, 5 }, pickupModel);
                pickup->SetTag("Pickup");
                m_scene->AddActor(std::move(pickup));
            }

            if (rPickup == 2)
            {
                auto* pickupModel = new Model{ GameData::plusPoints, Color{1, 1, 1} };
                auto pickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight()) }, 0, 5 }, pickupModel);
                pickup->SetTag("Plus");
                m_scene->AddActor(std::move(pickup));
            }

            if (rPickup == 3)
            {
                auto* pickupModel = new Model{ GameData::doublePoints, Color{1, 1, 1} };
                auto pickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight()) }, 0, 5 }, pickupModel);
                pickup->SetTag("Double");
                m_scene->AddActor(std::move(pickup));
            }

            // create asteroid
            auto* asteroidModel = new Model{ GameData::asteroidPoints, Color{1, 1, 1} };
            auto asteroid = std::make_unique<Asteroid>(4000, Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight()) }, 0, 5 }, asteroidModel);
            asteroid->SetTag("Asteroid");
            m_scene->AddActor(std::move(asteroid));
        }

        break;
    case eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::StartLevel;
        }
        break;
    case eState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::Title;
        }
        break;
    default:
        break;
    }
   

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_state)
    {
    case SpaceGame::eState::Title:
        // draw text "Game Title"
        m_textTitle->Create(renderer, "MilkyWay Battle!", Color{ 1, 0, 0 });
        m_textTitle->Draw(renderer, 200, 300);
        break;
    case SpaceGame::eState::GameOver:
        // draw text "Game Over"
        m_textTitle->Create(renderer, "Game Over!", Color{ 1, 0, 0 });
        m_textTitle->Draw(renderer, 260, 300);
        break;
    default:
        break;
    }

    // draw score
    std::string text = "Score " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0, 1, 0 });
    m_textScore->Draw(renderer, 20, 20);
    // draw lives
    text = "Lives " + std::to_string(m_lives);
    m_textLives->Create(renderer, text, { 0, 1, 0 });
    m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);
    

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    g_engine.GetAudio().PlaySound("explosion.wav");
    m_lives--;
    m_state = (m_lives <= 0) ? eState::GameOver : eState::PlayerDead;
    m_stateTimer = 3;
}

void SpaceGame::addLives()
{
    m_lives++;
}

void SpaceGame::DoubleScore()
{
    m_score = m_score * 2;
}
