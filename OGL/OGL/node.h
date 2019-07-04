#pragma once

#include "point.h"
#include <vector>
class Node
{
public:
	Point* top;
	Point* down;

	int limit;

	bool split;
	std::vector<Point*> data;

	Node* nw_front;
	Node* ne_front;
	Node* sw_front;
	Node* se_front;
	Node* nw_back;
	Node* ne_back;
	Node* sw_back;
	Node* se_back;

	Node(double top_x, double top_y, double top_z, double down_x, double down_y, double down_z);
	~Node();

	bool find_data(Point* P);
	void print_data();
};


Node::Node(double top_x, double top_y, double top_z, double down_x, double down_y, double down_z)
{
	top = new Point(top_x, top_y, top_z);
	down = new Point(down_x, down_y, down_z);

	split = false;

	nw_front = ne_front = sw_front = se_front = NULL;
	nw_back = ne_back = sw_back = se_back = NULL;
}

Node::~Node()
{

}

inline bool Node::find_data(Point* P)
{
	for (int i = 0; i < data.size(); ++i) {
		if (data[i]->compare(*P))
			return true;
	}
	return false;
}

inline void Node::print_data()
{
	for (int i = 0; i < data.size(); ++i)
	{
		data[i]->print();
	}
}

