#include "Bird.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>


Bird::Bird(int birdId, std::vector<Bird*>* birdsIn, double xIn, double yIn)
{

	x = xIn;
	y = yIn;

	birds = birdsIn;
	id = birdId;

	texture = mApplication->LoadTexture("square.png");
	this->SetTexture(texture);
	this->SetSize(10, 10);
	SetOffset(x, y);

	int a = generateRandom(-1000, 1000);
	int b = generateRandom(-1000, 1000);
	direction.setRichting(a, b);
	
}

Bird::~Bird()
{
	SDL_DestroyTexture(texture);
}

void Bird::Update(float deltaTime) {
	//if (direction.x == 0) direction.x = generateRandom(-1000, 1000);
	//if (direction.y == 0) direction.y = generateRandom(-1000, 1000);

	double currVectorLength = direction.getLength(x, y);
	double eenheidsVectorx = direction.x / currVectorLength;
	double eenheidsVectory = direction.y / currVectorLength;
	x = x + (eenheidsVectorx * speed);
	y = y + (eenheidsVectory * speed);
	//direction.x = x + eenheidsVectorx;
	//direction.y = y + eenheidsVectory;
	if (x > 800) x = x - 800;
	if (x < 0) x = x + 800;
	if (y > 600) y = y - 600;
	if (y < 0) y = y + 600;

	Vector one = avoidCollision(getNearbyBirds(collisionRadius));
	Vector two = mimicDirection(getNearbyBirds(directionRadius));
	//Vector three = stayNearOthers(nearbyBirds);

	one = addVectors(one, two);
	if (one.x == 0)  one.x = direction.x;
	if (one.y == 0) one.y = direction.y;

	direction = one;

	SetOffset(x, y);
}

Vector Bird::avoidCollision(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* bird in nearbyBirds)
	{
		if (bird->id != id) {
			if (bird->x > this->x && bird->direction.x < this->direction.x || bird->x < this->x && bird->direction.x > this->direction.x) {
				returnVector.x = this->direction.x - (this->direction.x * 2);
			}
			if (bird->y > this->y && bird->direction.y < this->direction.y || bird->y < this->y && bird->direction.y > this->direction.y) {
				returnVector.y = this->direction.y - (this->direction.y * 2);
			}
		}
	}
	
	return returnVector;

}

Vector Bird::mimicDirection(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* bird in nearbyBirds)
	{
		if (bird->id != id) {
			returnVector = addVectors(returnVector, bird->direction);
		}
	}

	return returnVector;
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

Vector Bird::getOppositeVector(Vector v) {
	v.x = v.x - (v.x * 2);
	v.y = v.y - (v.y * 2);
	return v;
}

std::vector<Bird*> Bird::getNearbyBirds(double range)
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


int Bird::generateRandom(int min, int max) {
	std::mt19937 rng(rd()); 
	std::uniform_int_distribution<int> uni(min, max); 

	auto random_integer = uni(rng);
	return random_integer;
}