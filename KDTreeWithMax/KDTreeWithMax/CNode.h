#pragma once
#include "CPoint.h"


class Node
{
public:
	Point* top;
	Point* down;

	Node* left;
	Node* right;

	int coordenada;		// 0=x | 1=y | 2=z

	std::vector<Point*> points;
	std::vector<Point*> P_nodes;

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
	{
		int tam_nodes = points.size();
		for (int i = tam_nodes - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (points[j]->x > points[j + 1]->x)
				{
					Point* t = points[j];
					points[j] = points[j + 1];
					points[j + 1] = t;
				}
			}
		}
	}
	else if (coordenada == 1)
	{
		int tam_nodes = points.size();
		for (int i = tam_nodes - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (points[j]->y > points[j + 1]->y)
				{
					Point* t = points[j];
					points[j] = points[j + 1];
					points[j + 1] = t;
				}
			}
		}
	}
	else if (coordenada == 2)
	{
		int tam_nodes = points.size();
		for (int i = tam_nodes - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (points[j]->z > points[j + 1]->z)
				{
					Point* t = points[j];
					points[j] = points[j + 1];
					points[j + 1] = t;
				}
			}
		}
	}
}

inline void Node::print_points()
{
	for (int i = 0; i < P_nodes.size(); ++i) 
	{
		P_nodes[i]->print();
	}
}
