#include "Vector.h"
#include <cmath>


Vector::Vector()
{
}


Vector::~Vector()
{
}

void Vector::setRichting(double xIn, double yIn)
{
	x = xIn;
	y = yIn;
}

double Vector::getLength(double xBird, double yBird) {
	double yourX = xBird + x;
	double yourY = xBird + y;
	double lengteX = yourX - xBird;
	double lengteY = yourY - yBird;
	double lengte = sqrt((std::pow(lengteX, 2) + std::pow(lengteY, 2)));
	return lengte;
}

