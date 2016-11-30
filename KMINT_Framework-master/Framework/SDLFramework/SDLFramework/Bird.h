#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>

class Bird : public IGameObject
{
public:
	Bird(int birdId, std::vector<Bird*>* b, double xIn, double yIn);
	~Bird();
	void Update(float deltaTime);
	Vector avoidCollision(std::vector<Bird*> nearbyBirds);
	Vector mimicDirection(std::vector<Bird*> nearbyBirds);
	Vector stayNearOthers(std::vector<Bird*> nearbyBirds);
	Vector addVectors(Vector vectorOne, Vector vectorTwo);
	Vector getOppositeVector(Vector v);
	Vector direction;
	double x;
	double y;
	int id;
	std::vector<Bird*>* birds;
private:
	double range = 10;
	double speed = 2;
	int screenWidth = 800;
	int screenHeigth = 600;
	SDL_Texture *texture;
	std::vector<Bird*> getNearbyBirds();
	int generateRandom(int min, int max);
	std::random_device rd;
};

