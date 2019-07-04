#include "CKDTree.h"

#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));

	std::vector<Point*>  probando;

	int cant_puntos = 40;
	for (int i = 1; i <= cant_puntos; ++i) {
		Point* T = new Point(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
		probando.push_back(T);
	}
	Point* x = new Point(8, 6, -5);
	probando.push_back(x);


	KDTree Tree(100, 1, probando);
	Tree.split(Tree.root);

	Tree.Alola(Tree.root, 0);

	Node* p = Tree.root;
	std::cout << Tree.find(p, x) << std::endl;
		
	system("Pause");
	return 0;
}
