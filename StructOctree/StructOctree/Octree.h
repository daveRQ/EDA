#pragma once
#include "Node.h"

class OctreeStruct
{
private:
	void add(Node* N, Point* P);
public:
	Node* root;
	double dimensions;
	int max_points;

	OctreeStruct(double dimensions, int max_points);
	~OctreeStruct();

	void find_cube(Node* &N, Point* P);
	bool add_point(double x, double y, double z);

	void print_all(Node* p, int n);
};

OctreeStruct::OctreeStruct(double dimensions, int max_points)
{
	this->dimensions = dimensions;
	this->max_points = max_points;
	root = NULL;

	double top_x = dimensions / 2 - dimensions;
	double top_y = dimensions / 2;
	double top_z = dimensions / 2 - dimensions;
	double down_x = dimensions / 2;
	double down_y = dimensions / 2 - dimensions;
	double down_z = dimensions / 2;

	root = new Node(top_x, top_y, top_z, down_x, down_y, down_z);
}
OctreeStruct::~OctreeStruct()
{
}
inline void OctreeStruct::find_cube(Node* &N, Point* P)
{
	if (N->split == true)
	{
		if (N->nw_front->top->get_z() <= P->get_z())
		{
			if (N->nw_front->down->get_y() <= P->get_y())
			{
				if (N->nw_front->down->get_x() >= P->get_x())
				{
					N = N->nw_front;
					return find_cube(N, P);
				}
				else
				{
					N = N->ne_front;
					return find_cube(N, P);
				}
			}
			else
			{
				if (N->sw_front->down->get_x() >= P->get_x())
				{
					N = N->sw_front;
					return find_cube(N, P);
				}
				else
				{
					N = N->se_front;
					return find_cube(N, P);
				}
			}
		}
		else
		{
			if (N->nw_back->down->get_y() <= P->get_y())
			{
				if (N->nw_back->down->get_x() >= P->get_x())
				{
					N = N->nw_back;
					return find_cube(N, P);
				}
				else
				{
					N = N->ne_back;
					return find_cube(N, P);
				}
			}
			else
			{
				if (N->sw_back->down->get_x() >= P->get_x())
				{
					N = N->sw_back;
					return find_cube(N, P);
				}
				else
				{
					N = N->se_back;
					return find_cube(N, P);
				}
			}
		}
	}
}

// esto es privado
inline void OctreeStruct::add(Node* N, Point* P)
{
	N->data.push_back(P);
	if (N->data.size() > max_points)
	{
		N->split = true;
		double temp = (N->down->get_z() - N->top->get_z()) / 2;
		N->nw_front = new Node(N->top->get_x(), N->top->get_y(), N->top->get_z() + temp, N->top->get_x() + temp, N->down->get_y() + temp, N->down->get_z());
		N->ne_front = new Node(N->top->get_x() + temp, N->top->get_y(), N->top->get_z() + temp, N->down->get_x(), N->down->get_y() + temp, N->down->get_z());
		N->sw_front = new Node(N->top->get_x(), N->top->get_y() - temp, N->top->get_z() + temp, N->top->get_x() + temp, N->down->get_y(), N->down->get_z());
		N->se_front = new Node(N->top->get_x() + temp, N->top->get_y() - temp, N->top->get_z() + temp, N->down->get_x(), N->down->get_y(), N->down->get_z());
		N->nw_back = new Node(N->top->get_x(), N->top->get_y(), N->top->get_z(), N->top->get_x() + temp, N->down->get_y() + temp, N->down->get_z() - temp);
		N->ne_back = new Node(N->top->get_x() + temp, N->top->get_y(), N->top->get_z(), N->down->get_x(), N->down->get_y() + temp, N->down->get_z() - temp);
		N->sw_back = new Node(N->top->get_x(), N->top->get_y() - temp, N->top->get_z(), N->top->get_x() + temp, N->down->get_y(), N->down->get_z() - temp);
		N->se_back = new Node(N->top->get_x() + temp, N->top->get_y() - temp, N->top->get_z(), N->down->get_x(), N->down->get_y(), N->down->get_z() - temp);

		for (int i = 0; i < N->data.size(); i++)
		{
			Node* t = N;
			find_cube(t, N->data[i]);
			add(t, N->data[i]);
		}
		N->data.clear();
	}
}

inline bool OctreeStruct::add_point(double x, double y, double z)
{
	// Comprobando que entre en el rango del tamaño
	if (root->top->get_x() < x && root->down->get_x() > x &&
		root->down->get_y() < y && root->top->get_y() > y &&
		root->top->get_z() < z && root->down->get_z() > z)
	{
		Node* N = root;
		Point* P = new Point(x, y, z);
		find_cube(N, P);

		if (!N->find_data(P))
		{
			add(N, P);
			return true;
		}
	}
	return false;
}

inline void OctreeStruct::print_all(Node* p, int n)
{
	if (p) 
	{
		cout << "nivel: " << n << endl;
		p->print_data();
		if (p->split == true)
		{
			print_all(p->nw_front, n + 1);
			print_all(p->ne_front, n + 1);
			print_all(p->sw_front, n + 1);
			print_all(p->se_front, n + 1);
			print_all(p->nw_back, n + 1);
			print_all(p->ne_back, n + 1);
			print_all(p->sw_back, n + 1);
			print_all(p->se_back, n + 1);
		}
	}
}
