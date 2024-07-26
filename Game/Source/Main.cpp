#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Font.h"
#include "Text.h"

#include <cstdlib>
#include <vector>


int main(int argc, char* argv[])
{
	g_engine.Initialize();

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	//Font* font = new Font();
	//font->Load("Blox2.ttf", 40);

	//Text* text = new Text(font);
	//text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

//	Vector2 v1{ 400, 300 };
//	Vector2 v2{ 500, 400 };
//
//	//std::vector<Vector2> points;
//	/*for (int i = 0; i < 100; i++)
//	{
//		points.push_back(Vector2{ rand() % 800, rand() % 600});
//	}*/
//
//	std::vector<Particle> particles;
//	float offset = 0;
//	for (int i = 0; i < 0; i++)
//	{
//		particles.push_back(Particle{ {rand() % 800, rand() % 800}, { randomf(100, 300), 0.0f}});
//	}
//
//	std::vector<Vector2> points;
//	points.push_back(Vector2{ 5, 0 });
//	points.push_back(Vector2{ -5, -5 });
//	points.push_back(Vector2{ -5, 5 });
//	points.push_back(Vector2{ 5, 0 });
//	Model model{ points, Color{ 0, 0, 1 } };
//
//	// actor
//	
//
//	Scene* scene = new Scene();
//
//	//Transform shipTransform{ Vector2{randomf(0, 800)}, Vector2{randomf(0, 600)}, 0 , randomf(1,5) };
//	
//
//	g_engine.GetAudio().AddSound("bass.wav");
//	g_engine.GetAudio().AddSound("snare.wav");
//	g_engine.GetAudio().AddSound("close-hat.wav");
//	g_engine.GetAudio().AddSound("open-hat.wav");
//	g_engine.GetAudio().AddSound("clap.wav");
//	g_engine.GetAudio().AddSound("cowbell.wav");
//
//	float spawnTimer = 2;
//
//	// main loop
//	bool quit = false;
//	while (!g_engine.IsQuit())
//	{
//		// input
//		// update
//		// draw
//
//		//std::cout << time.GetTime() << std::endl;
//
//		g_engine.Update();
//
//		// INPUT
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
//		{
//			quit = true;
//		}
//
//		//transform.rotation = velocity.Angle(); //rotation + time.GetDeltaTime();
//
//		spawnTimer -= g_engine.GetTime().GetDeltaTime();
//		if (spawnTimer <= 0)
//		{
//			
//
//			spawnTimer = 2;
//		}
//
//		// UPDATE
//
//		scene->Update(g_engine.GetTime().GetDeltaTime());
//		
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q))
//		{
//			g_engine.GetAudio().PlaySound("bass.wav");
//		}
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W))
//		{
//			g_engine.GetAudio().PlaySound("snare.wav");
//		}
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E))
//		{
//			g_engine.GetAudio().PlaySound("close-hat.wav");
//		}
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_D))
//		{
//			g_engine.GetAudio().PlaySound("open-hat.wav");
//		}
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_S))
//		{
//			g_engine.GetAudio().PlaySound("clap.wav");
//		}
//
//		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_A))
//		{
//			g_engine.GetAudio().PlaySound("cowbell.wav");
//		}
//
//		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
//
//		if (g_engine.GetInput().GetMouseButtonDown(0))
//		{
//			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(50, 300), randomf(1, 5)});
//		}
//		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
//
//		for (Particle& particle : particles)
//		{
//			particle.Update(g_engine.GetTime().GetDeltaTime());
//
//			if (particle.position.x > 800) particle.position.x = 0;
//			if (particle.position.x < 0) particle.position.x = 800;
//			if (particle.lifespan != 0) particle.lifespan -= g_engine.GetTime().GetDeltaTime();
//		}
//
//		/*if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
//		{
//			std::cout << "mouse pressed\n";
//			points.push_back(mousePosition);
//		}
//
//		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
//		{
//			float distance = (points.back() - mousePosition).Length();
//			if (distance > 5) points.push_back(mousePosition);
//
//			points.push_back(mousePosition);
//		}*/
//
//		// [p, p, p, p]
//		/*Vector2 speed{ 0.1f, -0.1f };
//		for (Vector2& point : points)
//		{
//			point = point + 0.002f;
//		}*/
//
//		// DRAW
//		//// clear screen
//		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
//		g_engine.GetRenderer().BeginFrame();
//
//		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
//		float radius = 60;
//		offset += (90 * g_engine.GetTime().GetDeltaTime());
//		for (float angle = 0; angle < 360; angle += 360 / 30)
//		{
//			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.05f) * radius;
//			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset  + angle) * 0.05f) * radius;
//
//			//renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
//		}
//
//		////draw line
//		for (Particle particle : particles)
//		{
//			if (particle.lifespan >= 0)
//			{
//				particle.Draw(g_engine.GetRenderer());
//			}
//		}
//
//		//model.Draw(renderer, transform);
//		scene->Draw(g_engine.GetRenderer());
//
//		/*renderer.DrawLine(300, 250, 500, 250);
//
//		renderer.SetColor(255, 255, 255, 0);
//		renderer.DrawLine(300, 250, 400, 200);
//
//		renderer.SetColor(255, 255, 255, 0);
//		renderer.DrawLine(400, 250, 500, 250);*/
//
//		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);
//
//		/*for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
//		{
//			renderer.SetColor(255, 255, 255, 0);
//			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
//		}*/
//
//		/*for (int i = 0; i < 25; i++)
//		{
//			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
//			renderer.DrawLine(rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000);
//			renderer.DrawPoint(rand() % 1000, rand() % 1000);
//		}*/
//
//		//// show screen
//		g_engine.GetRenderer().EndFrame();
//	}
//
//	return 0;
//}