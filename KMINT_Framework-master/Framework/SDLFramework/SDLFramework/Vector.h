#pragma once
class Vector
{
public:
	Vector();
	~Vector();

	void setRichting(int xIn, int yIn);

	int x;
	int y;
	int speed = 3;
};

