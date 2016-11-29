#include "Bird.h"
#include <SDL_render.h>



Bird::Bird(int birdId, std::vector<Bird*>* birdsIn, int xIn, int yIn)
{
	x = xIn;
	y = yIn;
	direction.setRichting(3, 1);
	birds = birdsIn;
	id = birdId;

	texture = mApplication->LoadTexture("square.gif");
	this->SetTexture(texture);
	this->SetSize(50, 50);
	SetOffset(x, y);

}

Bird::~Bird()
{
	SDL_DestroyTexture(texture);
}

void Bird::Update(float deltaTime) {
	//const int a = (int)(sin(mApplication->GetTimeSinceStartedMS() / 300.0) * 15.0 + 400);
	//SetOffset(a, 250);

	x = x + direction.x;
	y = y + direction.y;

	if (x > 800) x = x - 800;
	if (x < 0) x = x + 800;
	if (y > 600) y = y - 600;
	if (y < 0) y = y + 600;

	std::vector<Bird*> nearbyBirds = getNearbyBirds();
	Vector one = avoidCollision(nearbyBirds);
	Vector two = mimicDirection(nearbyBirds);
	Vector three = stayNearOthers(nearbyBirds);

	SetOffset(x, y);
}

Vector Bird::avoidCollision(std::vector<Bird*> nearbyBirds) {
	for each (Bird* bird in nearbyBirds)
	{
		if (bird->id != id) {
			direction = addVectors(direction, bird->direction);
		}
	}
	return direction;
}

Vector Bird::mimicDirection(std::vector<Bird*> nearbyBirds) {
	Vector v;
	return v;
}

Vector Bird::stayNearOthers(std::vector<Bird*> nearbyBirds) {
	Vector v;
	return v;
}

Vector Bird::addVectors(Vector vectorOne, Vector vectorTwo) {
	Vector newVector;
	newVector.x = vectorOne.x + vectorTwo.x;
	newVector.y = vectorOne.y + vectorTwo.y;
	return newVector;
}

std::vector<Bird*> Bird::getNearbyBirds()
{
	std::vector<Bird*> nearbyBirds;
	std::vector<Bird*>& birdsRef = *birds;
	for (int i = 0; i < birdsRef.size(); i++) {
		if (birdsRef[i]->x < x + range && birdsRef[i]->x > x - range && birdsRef[i]->y < y + range && birdsRef[i]->y > y - range) {
			nearbyBirds.push_back(birdsRef[i]);
		}
	}

	return nearbyBirds;
}
