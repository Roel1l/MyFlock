#pragma once
#include "IGameObject.h"
#include "vector.h"

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
	double range = 100;
	double speed = 4;
	int screenWidth = 800;
	int screenHeigth = 600;
	SDL_Texture *texture;
	std::vector<Bird*> getNearbyBirds();
};

