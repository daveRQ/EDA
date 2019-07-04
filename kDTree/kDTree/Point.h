#pragma once
#include <iostream>
#include <vector>

class Point 
{
public:
	double x, y, z;
	Point(double x, double y, double z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void print() 
	{ 
		std::cout << "| " << x << ", " << y << ", " << z << " |" << std::endl; 
	}
};