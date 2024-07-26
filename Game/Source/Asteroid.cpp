#include "Asteroid.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"

void Asteroid::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity = direction.Normalized() * m_speed * dt;
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(dt);
}

void Asteroid::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			player->SetFireModifier(0.2f);
			m_destroyed = true;
		}
	}

	if (actor->GetTag() == "Bullet")
	{
		m_scene->GetGame()->AddPoints(50);
		m_destroyed = true;
	}

	for (int i = 0; i < 100; i++)
	{
		Particle::Data data
		{
			m_transform.position,
			Vector2{1, 0}.Rotate(randomf(Math::TwoPi)) * 50,
			randomf(0.5f, 2.0f)
		};
		g_engine.GetPS().AddParticle(data);
	}
}