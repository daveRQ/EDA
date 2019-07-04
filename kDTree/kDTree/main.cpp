#include "KDTree.h"

#include <stdlib.h>
#include <time.h>

int main() 
{
	srand(time(NULL));

	std::vector<Point*>  probando;

	int cant_puntos = 100;
	for (int i = 1; i <= cant_puntos; ++i) {
		Point* T = new Point(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
		probando.push_back(T);
	}

	/*for (int i = 0; i < probando.size(); ++i) 
	{
		probando[i]->print();
	}*/

	KDTree Tree(100, probando);
	Tree.split(Tree.root);

	Tree.Alola(Tree.root, 0);

	/*Point* A = new Point(-1, -5, 8);
	Point* B = new Point(2, 3, 0);
	Point* C = new Point(12, -2, -4);
	Point* D = new Point(-1, 5, -2);
	Point* E = new Point(-1, 8, -2);
	Point* F = new Point(0, 1, -2);
	Point* G = new Point(19, 2, 17);
	Point* H = new Point(-1, 5, -17);
	Point* I = new Point(-1, 2, -2);
	Point* J = new Point(0, 0, 1);
	std::vector<Point*>  probando;
	probando.push_back(A);
	probando.push_back(B);
	probando.push_back(C);
	probando.push_back(D);
	probando.push_back(E);
	probando.push_back(F);
	probando.push_back(G);
	probando.push_back(H);
	probando.push_back(I);
	probando.push_back(J);
	
	KDTree Tree(20, probando);

	Tree.split(Tree.root);*/

	//Tree.print(Tree.root);
	//Tree.Alola(Tree.root, 0);

	/*for (int i = 0; i < No.points.size(); ++i)
	{
		No.points[i]->print();
	}

	std::cout << std::endl;

	No.sort_point();


	for (int i = 0; i < No.points.size(); ++i)
	{	
		No.points[i]->print();
	}*/

	system("Pause");
	return 0;
}
