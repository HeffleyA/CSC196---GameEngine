#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fmod.hpp>

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	Input input;
	input.Initialize();

	Time time;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 500, 400 };

	//std::vector<Vector2> points;
	/*for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600});
	}*/

	std::vector<Particle> particles;
	float offset = 0;
	for (int i = 0; i < 0; i++)
	{
		particles.push_back(Particle{ {rand() % 800, rand() % 800}, { randomf(100, 300), 0.0f}});
	}

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });
	Model model{ points, Color{ 0, 0, 1 } };

	std::vector<Vector2> ship;
	ship.push_back(Vector2{ 0, 0 });

	ship.push_back(Vector2{ -1.0f, 0.5f });
	ship.push_back(Vector2{ -1, 1 });
	ship.push_back(Vector2{ 0, 1 });
	ship.push_back(Vector2{ 0.0f, 0.5f });
	ship.push_back(Vector2{ -1.0f, 0.5f });

	ship.push_back(Vector2{ -2, 1 });

	ship.push_back(Vector2{ -3, 1 });
	ship.push_back(Vector2{ -3.0f, 0.5f });
	ship.push_back(Vector2{ -2.0f, 0.5f });
	ship.push_back(Vector2{ -2, 1 });

	ship.push_back(Vector2{ -2.0f, -0.5f });
	ship.push_back(Vector2{ -3.0f, -0.5f });
	ship.push_back(Vector2{ -3, -1 });
	ship.push_back(Vector2{ -2, -1 });
	ship.push_back(Vector2{ -2.0f, -0.5f });

	ship.push_back(Vector2{ -2, -1 });


	ship.push_back(Vector2{ -1.0f, -0.5f });
	ship.push_back(Vector2{ -1, -1 });
	ship.push_back(Vector2{ 0, -1 });
	ship.push_back(Vector2{ 0.0f, -0.5f });
	ship.push_back(Vector2{ -1.0f, -0.5f });

	ship.push_back(Vector2{ 0, 0 });


	Model shipModel{ ship, Color{ 1, 1, 1, 0} };
	
	Transform transform{ { renderer.GetWidth() >> 1, renderer.GetHeight() >> 1}, 0, 5};

	Transform shipTransform{ { renderer.GetWidth() >> 1, renderer.GetHeight() >> 1}, 0, 20};

	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

	audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	// main loop
	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			audio->playSound(sounds[0], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[1], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[2], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_D) && !input.GetPreviousKeyDown(SDL_SCANCODE_D))
		{
			audio->playSound(sounds[3], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_S) && !input.GetPreviousKeyDown(SDL_SCANCODE_S))
		{
			audio->playSound(sounds[4], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_A) && !input.GetPreviousKeyDown(SDL_SCANCODE_A))
		{
			audio->playSound(sounds[5], nullptr, false, nullptr);
		}

		time.Tick();
		std::cout << time.GetTime() << std::endl;

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		if (input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;

		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.GetWidth());

		//transform.rotation = velocity.Angle(); //rotation + time.GetDeltaTime();

		// UPDATE
		audio->update();

		Vector2 mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(50, 300), randomf(1, 5)});
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

		renderer.SetColor(255, 255, 255, 0);
		float radius = 60;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.05f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset  + angle) * 0.05f) * radius;

			//renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}

		////draw line
		for (Particle particle : particles)
		{
			if (particle.lifespan >= 0)
			{
				particle.Draw(renderer);
			}
		}

		//model.Draw(renderer, transform);
		shipModel.Draw(renderer, shipTransform);

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