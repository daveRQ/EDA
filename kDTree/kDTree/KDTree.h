#pragma once
#include "CNode.h"

class KDTree 
{
public:
	Node* root;
	double dimension;

	KDTree(double dimension, std::vector<Point*> points);

	void split(Node* p);
	void print(Node* p);
	void Alola(Node* a, int espacios);
};

KDTree::KDTree(double dimension, std::vector<Point*> points)
{
	this->dimension = dimension;

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
		int median = p->points.size() / 2;		// Ubicacion de la mediana
		// Agrego el punto medio al nodo
		p->P_node = new Point(p->points[median]->x, p->points[median]->y, p->points[median]->z);

		if (median != 0) 
		{
			if (p->coordenada == 0)
			{
				p->left = new Node((p->coordenada)++, p->top->x, p->top->y, p->top->z, p->P_node->x, p->down->y, p->down->z);
				for (int i = 0; i < median; i++) 
				{
					p->left->points.push_back(p->points[i]);
				}
				
				int temp = median + 1;
				if (p->points.size() - temp > 0)
				{
					p->right = new Node((p->coordenada)++, p->P_node->x, p->top->y, p->top->z, p->down->x, p->down->y, p->down->z);
					for (temp; temp < p->points.size(); ++temp)
					{
						p->right->points.push_back(p->points[temp]);
					}
					p->points.clear();
					split(p->left);
					split(p->right);
					return;
				}

				p->points.clear();
				split(p->left);
				return;
			}
			 
			else if (p->coordenada == 1) 
			{
				p->left = new Node((p->coordenada)++, p->top->x, p->top->y, p->top->z, p->down->x, p->P_node->y, p->down->z);
				for (int i = 0; i < median; i++)
				{
					p->left->points.push_back(p->points[i]);
				}

				int temp = median + 1;
				if (p->points.size() - temp > 0)
				{
					p->right = new Node((p->coordenada)++, p->top->x, p->P_node->y, p->top->z, p->down->x, p->down->y, p->down->z);
					for (temp; temp < p->points.size(); ++temp)
					{
						p->right->points.push_back(p->points[temp]);
					}
					p->points.clear();
					split(p->left);
					split(p->right);
					return;
				}

				p->points.clear();
				split(p->left);
				return;
			}

			else if (p->coordenada == 2)
			{
				p->left = new Node((p->coordenada)++, p->top->x, p->top->y, p->top->z, p->down->x, p->down->y, p->P_node->z);
				for (int i = 0; i < median; i++)
				{
					p->left->points.push_back(p->points[i]);
				}

				int temp = median + 1;
				if (p->points.size() - temp > 0)
				{
					p->right = new Node((p->coordenada)++, p->top->x, p->top->y, p->P_node->z, p->down->x, p->down->y, p->down->z);
					for (temp; temp < p->points.size(); ++temp)
					{
						p->right->points.push_back(p->points[temp]);
					}
					p->points.clear();
					split(p->left);
					split(p->right);
					return;
				}

				p->points.clear();
				split(p->left);
				return;
			}
		}
	}
}

void KDTree::print(Node* p) 
{
	if (p != NULL)
	{
		print(p->left);
		print(p->right);
		p->P_node->print();
	}
}

void KDTree::Alola(Node* a, int n) 
{
	if (a != NULL) 
	{
		Alola(a->right, n + 15);
		for (int i = 0; i < n; i++)
			std::cout << " ";
		a->P_node->print();
		Alola(a->left, n + 15);
	}
}