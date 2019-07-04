
#include "Octree.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));
	OctreeStruct A(20, 3);

	//A.add_points(2, 5, 6);
	//A.add_points(-2, 6, 6);
	//A.add_points(2, 4, 6);
	//A.add_points(-4, 3, 1);

	//A.root->nw_front->print_data();
	//A.root->ne_front->print_data();
	//A.root->sw_front->print_data();
	//A.root->se_front->print_data();
	//A.root->nw_back->print_data();
	//A.root->ne_back->print_data();
	//A.root->sw_back->print_data();
	//A.root->se_back->print_data();


	int cant_puntos = 1000;
	for (int i = 1; i <= cant_puntos; ++i) {
		A.add_point(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10);
	}


/*
	A.add_point(2, -5, 6);
	A.add_point(-2, 6, 6);
	A.add_point(2, -4, 6);
	A.add_point(-4, 3, 1);

	A.add_point(-4, -6, -7);

	A.add_point(2, 7, 6);
	A.add_point(2, 6, 6);
	A.add_point(2, 4, 6);
	A.add_point(4, 3, 1);*/

	A.print_all(A.root, 0);

	system("Pause");
	return 0;
}

