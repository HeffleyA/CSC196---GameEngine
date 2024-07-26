#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid() = default;
	Asteroid(const Transform& transform) : Actor{ transform } {}
	Asteroid(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Asteroid(float speed, const Transform& transform, Model* model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt);

	virtual void OnCollision(Actor* actor);

private:
	float m_speed = 0;
};