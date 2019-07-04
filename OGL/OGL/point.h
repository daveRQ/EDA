#pragma once
#include <iostream>

using namespace std;

class Point //easy breezy
{
private:
	double x;
	double y;
	double z;
public:
	bool illumination;

	double get_x() { return x; }
	double get_y() { return y; }
	double get_z() { return z; }
	Point(double x, double y, double z);
	~Point();

	bool compare(Point P);
	void print() { std::cout << "|" << x << "; " << y << "; " << z << "|" << std::endl; }
};


Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	illumination = false;
}

Point::~Point()
{
}

inline bool Point::compare(Point P)
{
	if (P.get_x() == x && P.get_y() == y && P.get_z() == z) {
		return true;
	}
	return false;
}

