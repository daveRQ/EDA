#pragma once
#include "CNode.h"

class KDTree
{
public:
	Node* root;
	double dimension;
	int max_points;

	KDTree(double dimension, int max_points, std::vector<Point*> points);

	void split(Node* p);
	bool find(Node* &p, Point* P);
	void print(Node* p);
	void Alola(Node* a, int espacios);
};

KDTree::KDTree(double dimension, int max_points, std::vector<Point*> points)
{
	this->dimension = dimension;
	this->max_points = max_points;

	int pos = (dimension / 2);
	int neg = pos * -1;

	root = new Node(0, neg, pos, neg, pos, neg, pos);
	root->points = points;
}

void KDTree::split(Node* p)
{
	if (p)
	{
		p->sort_point();
		if (p->points.size() > max_points)
		{
			int mid = p->points.size() / 2;

			if (p->coordenada == 0)
			{
				p->left = new Node(p->coordenada + 1, p->top->x, p->top->y, p->top->z, p->points[mid]->x, p->down->y, p->down->z);
				for (int i = 0; i < mid; i++)
				{
					p->left->points.push_back(p->points[i]);
				}

				p->right = new Node(p->coordenada + 1, p->points[mid]->x, p->top->y, p->top->z, p->down->x, p->down->y, p->down->z);
				for (int i = mid; i < p->points.size(); ++i)
				{
					p->right->points.push_back(p->points[i]);
				}
				p->points.clear();
				split(p->left);
				split(p->right);
				return;
			}
			if (p->coordenada == 1)
			{
				p->left = new Node(p->coordenada + 1, p->top->x, p->points[mid]->y, p->top->z, p->down->x, p->down->y, p->down->z);
				for (int i = 0; i < mid; i++)
				{
					p->left->points.push_back(p->points[i]);
				}
				p->right = new Node(p->coordenada + 1, p->top->x, p->top->y, p->top->z, p->down->x, p->points[mid]->y, p->down->z);
				for (int i = mid; i < p->points.size(); ++i)
				{
					p->right->points.push_back(p->points[i]);
				}
				p->points.clear();
				split(p->left);
				split(p->right);
				return;
			}
			if (p->coordenada == 2)
			{
				p->left = new Node(p->coordenada + 1, p->top->x, p->top->y, p->top->z, p->down->x, p->down->y, p->points[mid]->z);
				for (int i = 0; i < mid; i++)
				{
					p->left->points.push_back(p->points[i]);
				}

				p->right = new Node(p->coordenada + 1, p->top->x, p->top->y, p->points[mid]->z, p->down->x, p->down->y, p->down->z);
				for (int i = mid; i < p->points.size(); ++i)
				{
					p->right->points.push_back(p->points[i]);
				}
				p->points.clear();
				split(p->left);
				split(p->right);
				return;
			}
		}
	}
}

inline bool KDTree::find(Node* &p, Point* P)
{
	if (p)
	{
		if (p->coordenada == 0)
		{
			if (p->left && p->left->down->x > P->x)
			{
				return find(p->left, P);
			}
			else if (p->right)
			{
				return find(p->right, P);
			}
			for (int i = 0; i < p->points.size(); ++i)
			{
				if (p->points[i]->x == P->x && p->points[i]->y == P->y && p->points[i]->z == P->z)
					return true;
			}
		}
		else if (p->coordenada == 1)
		{
			if (p->left && p->left->top->y > P->y)
			{
				return find(p->left, P);
			}
			else if (p->right)
			{
				return find(p->right, P);
			}
			for (int i = 0; i < p->points.size(); ++i)
			{
				if (p->points[i]->x == P->x && p->points[i]->y == P->y && p->points[i]->z == P->z)
					return true;
			}
		}
		else if (p->coordenada == 2)
		{
			if (p->left && p->left->down->z > P->z)
			{
				return find(p->left, P);
			}
			else if (p->right)
			{
				return find(p->right, P);
			}
			for (int i = 0; i < p->points.size(); ++i)
			{
				if (p->points[i]->x == P->x && p->points[i]->y == P->y && p->points[i]->z == P->z)
					return true;
			}
		}
	}
	return false;
}

void KDTree::print(Node* p)
{
	if (p != NULL)
	{
		print(p->left);
		print(p->right);
		p->print_points();
	}
}

void KDTree::Alola(Node* a, int n)
{
	if (a != NULL)
	{
		Alola(a->right, n + 10);
		for (int i = 0; i < n; i++)
			std::cout << " ";
		a->print_points();
		std::cout << std::endl;
		Alola(a->left, n + 10);
	}
}

