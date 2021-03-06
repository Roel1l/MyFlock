#include <iostream>
#include <vector>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Bird.h"
#include "ExampleGameObject.h"

using namespace std;

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	
	std::vector<Bird*>* birds = new vector<Bird*>;

	for (int i = 10; i > 0; i--) {
		Bird* bird = new Bird(i, birds, 250, 250 + i *100);
		birds->push_back(bird);
		application->AddRenderable(bird);
	}


	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

				default:
					break;
				}
			}
		}
		
		// This is example code, replace with your own!

		// Dancing cow


		//// Text drawing
		//application->SetColor(Color(0, 0, 0, 255));
		//application->DrawText("Welcome to KMint", 400, 300);
		//
		//// Graph drawing
		//application->SetColor(Color(0, 0, 0, 255));
		//application->DrawLine(400, 350, 350, 400);
		//application->DrawLine(350, 400, 450, 400);
		//application->DrawLine(450, 400, 400, 350);

		//application->SetColor(Color(0, 0, 255, 255));
		//application->DrawCircle(400, 350, 10, true);
		//application->DrawCircle(350, 400, 10, true);
		//application->DrawCircle(450, 400, 10, true);

		//// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	for each (Bird* var in *birds)
	{
		delete var;
	}
	delete birds;
	return EXIT_SUCCESS;
}