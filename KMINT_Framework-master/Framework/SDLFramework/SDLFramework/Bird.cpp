#include "Bird.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>
#include <iostream>

Bird::Bird(int birdId, std::vector<Bird*>* birdsIn, double xIn, double yIn)
{

	x = xIn;
	y = yIn;

	birds = birdsIn;
	id = birdId;

	texture = mApplication->LoadTexture("square.png");
	this->SetTexture(texture);
	this->SetSize(10, 10);

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

	double currVectorLength = direction.getLength();
	
	if (currVectorLength > speed) {
		direction.x = direction.x / currVectorLength * speed;
		direction.y = direction.y / currVectorLength * speed;
	}

	x = x + direction.x;
	y = y + direction.y;
	//direction.x = x + eenheidsVectorx;
	//direction.y = y + eenheidsVectory;
	if (x > 800) x = x - 800;
	if (x < 0) x = x + 800;
	if (y > 600) y = y - 600;
	if (y < 0) y = y + 600;

	//std::cout << x << std::endl;

	Vector one = avoidCollision(getNearbyBirds(collisionRadius));
	Vector two = mimicDirection(getNearbyBirds(directionRadius));
	//Vector three = stayNearOthers(nearbyBirds);

	//one = addVectors(one, two);
	//if (one.x == 0)  one.x = direction.x;
	//if (one.y == 0) one.y = direction.y;

	direction.x += one.x;
	direction.y += one.y;

	SetOffset(x-5, y-5);
}

Vector Bird::avoidCollision(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* otherBird in nearbyBirds)
	{
		if (otherBird->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;
			temp.x += x - otherBird->x;
			temp.y += y - otherBird->y;
			
			double length = temp.getLength();
			if (length > 1) {
				temp.x = temp.x / length * 1;
				temp.y = temp.y / length * 1;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}
	
	return returnVector;

}

Vector Bird::mimicDirection(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* otherBird in nearbyBirds)
	{
		if (otherBird->id != id) {
			returnVector.x += otherBird->direction.x; 
			returnVector.y += otherBird->direction.y;
		}
	}

	return returnVector;
}

Vector Bird::stayNearOthers(std::vector<Bird*> nearbyBirds) {
	Vector v;
	return v;
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