#pragma once
#include "IGameObject.h"
#include "vector.h"

class Bird : public IGameObject
{
public:
	Bird(int birdId, std::vector<Bird*>* b, int xIn, int yIn);
	~Bird();
	void Update(float deltaTime);
	Vector avoidCollision(std::vector<Bird*> nearbyBirds);
	Vector mimicDirection(std::vector<Bird*> nearbyBirds);
	Vector stayNearOthers(std::vector<Bird*> nearbyBirds);
	Vector addVectors(Vector vectorOne, Vector vectorTwo);
	Vector direction;
	int x;
	int y;
	int id;
	std::vector<Bird*>* birds;
private:
	int range = 100;
	int screenWidth = 800;
	int screenHeigth = 600;
	SDL_Texture *texture;
	std::vector<Bird*> getNearbyBirds();
};

