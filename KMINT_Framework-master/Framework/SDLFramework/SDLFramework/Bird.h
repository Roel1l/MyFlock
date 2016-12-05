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
	Vector getOppositeVector(Vector v);
	Vector direction;
	double x;
	double y;
	int id;
	std::vector<Bird*>* birds;
private:
	double collisionRadius = 20;
	double directionRadius = 20;
	double speed = 1;
	int screenWidth = 800;
	int screenHeigth = 600;
	SDL_Texture *texture;
	std::vector<Bird*> getNearbyBirds(double range);
	int generateRandom(int min, int max);
	std::random_device rd;
};

