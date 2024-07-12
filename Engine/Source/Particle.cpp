#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
	renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
}
