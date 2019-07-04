#pragma once
#include "CPoint.h"
#include <algorithm>
#include <vector> 


inline bool compare_x(const Point* p, const Point* d)
{
	return p->x < d->x;
}
inline bool compare_y(const Point* p, const Point* d)
{
	return p->y < d->y;
}
inline bool compare_z(const Point* p, const Point* d)
{
	return p->z < d->z;
}


class Node
{
public:
	Point* top;
	Point* down;

	Node* left;
	Node* right;

	int coordenada;		// 0=x | 1=y | 2=z

	std::vector<Point*> points;

	Node(int coordenada, double top_x, double top_y, double top_z, double down_x, double down_y, double down_z);

	void sort_point();
	void print_points();
};

inline Node::Node(int coordenada, double top_x, double top_y, double top_z, double down_x, double down_y, double down_z)
{
	this->coordenada = coordenada % 3;
	top = new Point(top_x, top_y, top_z);
	down = new Point(down_x, down_y, down_z);

	left = right = NULL;
}

inline void Node::sort_point()
{
	if (coordenada == 0)
		std::stable_sort(points.begin(), points.end(), compare_x);
	else if (coordenada == 1)
		std::stable_sort(points.begin(), points.end(), compare_y);
	else 
		std::stable_sort(points.begin(), points.end(), compare_z);
}

inline void Node::print_points()
{
	for (int i = 0; i < points.size(); ++i)
	{
		points[i]->print();
	}
}

