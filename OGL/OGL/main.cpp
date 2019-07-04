#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <string>
#include <fstream>

#include "Octree.h"

#include <stdlib.h>
#include <time.h>

#include <ctime> 

#define KEY_ESC 27

using namespace std;

int mx = 0;
int my = 0;

float ax = 0.0;
float ay = 0.0;
float speed = 0.1;


//ESFERA
double e_x = 0;
double e_y = 0;
double e_z = 0;


// ESTRUCTURA
int tam = 20;
OctreeStruct A(tam, 100);

double radio = 2.0;

// FUNCIONES OCTREE
void print_all_Node(Node* p)
{
	if (p)
	{
		double me_x = (p->top->get_x() + p->down->get_x()) / 2;
		double me_y = (p->top->get_y() + p->down->get_y()) / 2;
		double me_z = (p->top->get_z() + p->down->get_z()) / 2;

		glTranslated(me_x, me_y, me_z);
		glColor3d(255, 0, 0);
		glutSolidCube(p->top->get_x() - p->down->get_x());
		glTranslated(-me_x, -me_y, -me_z);

		for (int i = 0; i < p->data.size(); ++i)
		{
			if (p->data[i]->illumination == false)
			{
				glColor3d(0, 0, 255);
				glPointSize(5);
				glBegin(GL_POINTS);
				glVertex3d(p->data[i]->get_x(), p->data[i]->get_y(), p->data[i]->get_z());
				glEnd();
			}
			else
			{
				glColor3d(255, 255, 255);
				glPointSize(5);
				glBegin(GL_POINTS);
				glVertex3d(p->data[i]->get_x(), p->data[i]->get_y(), p->data[i]->get_z());
				glEnd();
			}
		}
				
		print_all_Node(p->nw_front);
		print_all_Node(p->ne_front);
		print_all_Node(p->sw_front);
		print_all_Node(p->se_front);
		print_all_Node(p->nw_back);
		print_all_Node(p->ne_back);
		print_all_Node(p->sw_back);
		print_all_Node(p->se_back);

	}
}
void paint_sphere(int division)
{
	// Creo todos los puntos
	vector<Point*> spherePoints;
	double top_x = e_x + radio;
	double top_y = e_y + radio;
	double top_z = e_z + radio;
	double rango = (radio + radio) / division;
	for (double z = (e_z - radio); z <= top_z; z += rango)
	{
		for (double y = (e_y - radio); y <= top_y; y += rango)
		{
			for (double x = (e_x - radio); x <= top_x; x += rango)
			{
				if (A.root->top->get_x() <= x && A.root->down->get_x() >= x &&
					A.root->down->get_y() <= y && A.root->top->get_y() >= y &&
					A.root->top->get_z() <= z && A.root->down->get_z() >= z)
				{
					Point* t = new Point(x, y, z);
					spherePoints.push_back(t);
				}
			}
		}
	}

	// Buscar los nodos que chocan con los puntos
	vector<Node*> checkNodes;
	for (int i = 0; i < spherePoints.size(); ++i)
	{
		Node* t = A.root;
		
		A.find_cube(t, spherePoints[i]);

		bool check = true;
		for (int j = 0; j < checkNodes.size(); ++j)
		{
			if (checkNodes[j] == t)
			{
				check = false;
				break;
			}
		}
		if (check == true)
			checkNodes.push_back(t);
	}
	

	spherePoints.clear();
	// Volver a pintar los puntos
	for (int i = 0; i < checkNodes.size(); ++i)
	{
		for (int j = 0; j < checkNodes[i]->data.size(); ++j)
		{
			if ((sqrt(pow(checkNodes[i]->data[j]->get_x() - e_x, 2) +
				pow(checkNodes[i]->data[j]->get_y() - e_y, 2) +
				pow(checkNodes[i]->data[j]->get_z() - e_z, 2))) <= radio)
			{
				checkNodes[i]->data[j]->illumination = true;
			}
		}
	}
	
}

bool r = false;
void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x;
		my = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		r = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		r = false;
	}
}
void OnMouseMotion(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;

	mx = x;
	my = y;

	ax += dx * speed;
	ay += dy * speed;
}
void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(18.0, 1.0, 1.0, 500.0);

	glTranslatef(0, 0, -100.0);
	glRotatef(ax, 0, 1, 0);
	glRotatef(ay, 1, 0, 0);

	//displayGizmo();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glutSolidTeapot(7);
	
	print_all_Node(A.root);

	glTranslated(e_x, e_y, e_z);
	glColor3d(0, 255, 0);
	glutSolidSphere(radio, 10, 10);
	glTranslated(-e_x, -e_y, -e_z);

	


	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glEnable(GL_DEPTH_TEST);
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		cout << "hello" << endl;
		e_y += 1;
		//exit(0);
		break;
	case GLUT_KEY_UP:
		cout << "hello" << endl;
		//exit(0);
		break;
	default:
		break;
	}

}
//
//el programa principal
//

void ArrowKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		e_x += 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	case GLUT_KEY_LEFT:
		e_x -= 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	case GLUT_KEY_UP:
		e_y += 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	case GLUT_KEY_DOWN:
		e_y -= 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	case GLUT_KEY_HOME:
		e_z += 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	case GLUT_KEY_END:
		e_z -= 0.2;
		A.discolor(A.root);
		paint_sphere(15);
		break;
	}
}



int main(int argc, char** argv) {
	srand(time(NULL));
	
	int random = tam * 1000;
	int dife = tam / 2 * 1000;
	double div = tam / 2 * 100;


	/*int cant_puntos = 10000;
	for (int i = 1; i <= cant_puntos; ++i) {
		double a = ((rand()) % random - dife) / div;
		double b = ((rand()) % random - dife) / div;
		double c = ((rand()) % random - dife) / div;

		A.add_point(a, b, c);
	}*/


	double puntitos[3];
	

	char cadena[40];
	std::ifstream fe("bunny.txt");
	std::string word;


	unsigned t0, t1;

	t0 = clock();


	//BUNNY
	int x = 0;
	while (!fe.eof()) {
		fe >> cadena;
		word = cadena;

		//std::cout << word << endl;

		if (x == 3)
		{
			A.add_point(puntitos[0], puntitos[1], puntitos[2]);
			x = 0;
			//std::cout << puntitos[0] << " " << puntitos[1] << " " << puntitos[2] << std::endl;
		}

		if (x == 0) 
		{
			puntitos[x] = (stod(word) + 4) * 5;
		}
		
		if (x == 1)
		{
			puntitos[x] = (stod(word) - 1) * 5;
		}
		else 
		{
			puntitos[x] = stod(word) * 5;
		}

		x++;
	}


	//int top = (3745 * 4);
	//int num = 0;
	//int x = 0;
	//while (!fe.eof() /*&& num < top*/) {
	//	fe >> cadena;
	//	word = cadena;

	//	//std::cout << word << endl;

	//	if (x == 4)
	//	{
	//		A.add_point(puntitos[0], puntitos[1], puntitos[2]);
	//		x = 0;
	//		//std::cout << puntitos[0] << " " << puntitos[1] << " " << puntitos[2] << std::endl;
	//	}
	//	
	//	if (x == 0)
	//	{
	//		//puntitos[x] = (stod(word) + 4) * 5;
	//	}

	//	if (x == 1)
	//	{
	//		puntitos[x - 1] = (stod(word));
	//	}
	//	else if (x == 2)
	//	{
	//		puntitos[x - 1] = stod(word);
	//	}
	//	else if (x == 3)
	//	{
	//		puntitos[x - 1] = stod(word);
	//	}
	//	x++;
	//	num++;
	//}

	t1 = clock();

	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	std::cout << "Execution Time: " << time << endl;


	//A.add_point(3.0, 0, 0);
	//A.add_point(-3.0, 0, 0);
	//A.add_point(0, 3.0, 0);
	//A.add_point(0, -3.0, 0);

/*	A.add_point(3.0, 0, -1);
	A.add_point(-3.0, 0, -1);
	A.add_point(0, 3.0, -1);
	A.add_point(0, -3.0, -1);

	A.add_point(3.0, 0, 1);
	A.add_point(-3.0, 0, 1);
	A.add_point(0, 3.0, 1);
	A.add_point(0, -3.0, 1);

	A.add_point(3.0, 0, -2);
	A.add_point(-3.0, 0, -2);
	A.add_point(0, 3.0, -2);
	A.add_point(0, -3.0, -2);

	A.add_point(3.0, 0, 2);
	A.add_point(-3.0, 0, 2);
	A.add_point(0, 3.0, 2);
	A.add_point(0, -3.0, 2);
*/


	A.discolor(A.root);
	paint_sphere(15);

	
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700); //tamaño de la ventana
	glutInitWindowPosition(100, 10); //posicion de la ventana
	glutCreateWindow("OctTree"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutSpecialFunc(ArrowKey);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);


	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	system("PAUSE");
	return 0;
}