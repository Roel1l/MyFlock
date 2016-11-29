#include "Bird.h"
#include <SDL_render.h>



Bird::Bird(int birdId, std::vector<Bird*>* birdsIn, double xIn, double yIn)
{

	x = xIn;
	y = yIn;

	birds = birdsIn;
	id = birdId;

	texture = mApplication->LoadTexture("square.gif");
	this->SetTexture(texture);
	this->SetSize(50, 50);
	SetOffset(x, y);

	direction.setRichting(yIn, 16);
	
}

Bird::~Bird()
{
	SDL_DestroyTexture(texture);
}

void Bird::Update(float deltaTime) {


	double currVectorLength = direction.getLength(x, y);
	double eenheidsVectorx = direction.x / currVectorLength;
	double eenheidsVectory = direction.y / currVectorLength;
	x = x + (eenheidsVectorx * speed);
	y = y + (eenheidsVectory * speed);

	if (x > 800) x = x - 800;
	if (x < 0) x = x + 800;
	if (y > 600) y = y - 600;
	if (y < 0) y = y + 600;

	std::vector<Bird*> nearbyBirds = getNearbyBirds();
	Vector one = avoidCollision(nearbyBirds);
	//Vector two = mimicDirection(nearbyBirds);
	//Vector three = stayNearOthers(nearbyBirds);

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
			Vector v = getOppositeVector(bird->direction);
			returnVector = addVectors(v, returnVector);
		}
	}

	if (nearbyBirds.size() > 1) {
		return returnVector;
	}
	else {
		return direction;
	}
	
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

Vector Bird::getOppositeVector(Vector v) {
	v.x = v.x - (v.x * 2);
	v.y = v.y - (v.y * 2);
	return v;
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
