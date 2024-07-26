#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Game.h"

#include <iostream>

void Player::Update(float dt)
{
	// movement
	Vector2 direction{ 0, 0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;
	
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetWidth());

	// fire
	m_fireTimer -= dt;
	m_upgradeTimer -= dt;
	if (g_engine.GetInput().GetMouseButtonDown(0) && m_fireTimer <= 0) //&& !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		m_fireTimer = 0.5f * m_fireModifier;

		g_engine.GetAudio().PlaySound("blaster.wav");

		if (m_upgradeTimer <= 0)
		{
			m_fireModifier = 1;
		}

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();

		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });

		// actor
		Model* bulletModel = new Model{ points, Color{ 1, 1, 1 } };
		Transform transform{ m_transform.position, angle, (1 * m_fireSize)};

		auto bullet = std::make_unique<Bullet>(400, transform, bulletModel);
		bullet->SetLifespan(1);
		bullet->SetTag("Bullet");
		m_scene->AddActor(std::move(bullet));
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy" || actor->GetTag() == "Asteroid")
	{
			m_destroyed = true;
			dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}

	if (actor->GetTag() == "Pickup")
	{
		m_upgradeTimer = 3;
	}

	if (actor->GetTag() == "Plus")
	{
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->addLives();
	}

	if (actor->GetTag() == "Double")
	{
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->DoubleScore();
	}
}
