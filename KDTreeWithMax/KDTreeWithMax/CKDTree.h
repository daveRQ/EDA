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
	if (p->points.size() != 0)
	{
		p->sort_point();
		if (p->points.size() <= max_points)
		{
			p->P_nodes = p->points;
			p->points.clear();
			return;
		}
		int mid = (p->points.size() / 2);
		int median = mid - (max_points / 2);		// Ubicacion de la mediana
		// Agrego el punto medio al nodo
		for (int i = 0; i < max_points; ++i)
		{
			p->P_nodes.push_back(p->points[median + i]);
		}

		if (p->coordenada == 0)
		{
			
			if (median != 0)
			{
				p->left = new Node((p->coordenada)+ 1, p->top->x, p->top->y, p->top->z, p->points[mid]->x, p->down->y, p->down->z);
				for (int i = 0; i < median; i++)
				{
					p->left->points.push_back(p->points[i]);
				}
				split(p->left);
			}

			int temp = median + max_points;
			if (p->points.size() > temp)
			{
				p->right = new Node(p->coordenada + 1, p->points[mid]->x, p->top->y, p->top->z, p->down->x, p->down->y, p->down->z);
				for (temp; temp < p->points.size(); ++temp)
				{
					p->right->points.push_back(p->points[temp]);
				}
				split(p->right);
			}
			
			p->points.clear();
			return;
		}

		else if (p->coordenada == 1)
		{
			if (median != 0)
			{
				p->left = new Node(p->coordenada + 1, p->top->x, p->top->y, p->top->z, p->down->x, p->points[mid]->y, p->down->z);
				for (int i = 0; i < median; i++)
				{
					p->left->points.push_back(p->points[i]);
				}
				split(p->left);
			}

			int temp = median + max_points;
			if (p->points.size() > temp)
			{
				p->right = new Node(p->coordenada + 1, p->top->x, p->points[mid]->y, p->top->z, p->down->x, p->down->y, p->down->z);
				for (temp; temp < p->points.size(); ++temp)
				{
					p->right->points.push_back(p->points[temp]);
				}
				split(p->right);
			}

			p->points.clear();
			return;
		}

		else if (p->coordenada == 2)
		{
			if (median != 0)
			{
				p->left = new Node(p->coordenada + 1, p->top->x, p->top->y, p->top->z, p->down->x, p->down->y, p->points[mid]->z);
				for (int i = 0; i < median; i++)
				{
					p->left->points.push_back(p->points[i]);
				}
				split(p->left);
			}

			int temp = median + max_points;
			if (p->points.size() > temp)
			{
				p->right = new Node(p->coordenada + 1, p->top->x, p->top->y, p->points[mid]->z, p->down->x, p->down->y, p->down->z);
				for (temp; temp < p->points.size(); ++temp)
				{
					p->right->points.push_back(p->points[temp]);
				}
				split(p->right);
			}

			p->points.clear();
			return;
		}
	}
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
		Alola(a->right, n + 30);
		for (int i = 0; i < n; i++)
			std::cout << " ";
		a->print_points();
		std::cout << std::endl;
		Alola(a->left, n + 30);
	}
}

