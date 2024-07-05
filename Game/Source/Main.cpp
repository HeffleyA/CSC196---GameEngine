#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 500, 400 };

	std::vector<Vector2> points;
	/*for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600});
	}*/

	std::vector<Particle> particles;
	for (int i = 0; i < 0; i++)
	{
		particles.push_back(Particle{ {rand() % 800, rand() % 800}, { randomf(100, 300), 0.0f}});
	}

	// main loop
	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		time.Tick();
		std::cout << time.GetTime() << std::endl;

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, {randomf(-100, 100), randomf(-100, 100)}, {randomf(1, 5)} });
		}
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
			if (particle.lifespan != 0) particle.lifespan -= time.GetDeltaTime();
		}

		/*if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		{
			std::cout << "mouse pressed\n";
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			if (distance > 5) points.push_back(mousePosition);

			points.push_back(mousePosition);
		}*/

		// [p, p, p, p]
		/*Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.002f;
		}*/

		// DRAW
		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		////draw line
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			if (particle.lifespan >= 0)
			{
				particle.Draw(renderer);
			}
		}

		/*renderer.DrawLine(300, 250, 500, 250);

		renderer.SetColor(255, 255, 255, 0);
		renderer.DrawLine(300, 250, 400, 200);

		renderer.SetColor(255, 255, 255, 0);
		renderer.DrawLine(400, 250, 500, 250);*/

		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		/*for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.SetColor(255, 255, 255, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}*/

		/*for (int i = 0; i < 25; i++)
		{
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000);
			renderer.DrawPoint(rand() % 1000, rand() % 1000);
		}*/

		//// show screen
		renderer.EndFrame();
	}

	return 0;
}