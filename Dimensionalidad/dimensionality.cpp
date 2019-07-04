#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;


void distancia(int cant_puntos, int dim, vector<double> vec) {
    double dis_menor = 10000000;
    double dis_mayor = 0;

    double sum_promedio = 0;
    double cant_sumas = 0;

    for (int i = 0; i < cant_puntos - 1; i++) {
        for (int j = i + 1; j < cant_puntos; j++) {
            double dis = 0;
            for (int d = 0; d < dim; d++) {
                double temp = pow(vec[i * dim + d] - vec[j * dim + d], 2);
                dis += temp;
            }
            dis = sqrt(dis);
            sum_promedio += dis;

            if (dis < dis_menor)
                dis_menor = dis;
            if (dis > dis_mayor)
                dis_mayor = dis;

            cant_sumas++;
        }
    }
    double promedio = sum_promedio / cant_sumas;
    cout << "El promedio es: " << promedio << endl; 
    cout << "La distancia mayor es: " << dis_mayor << endl;
    cout << "La distacia menor es: " << dis_menor << endl;
}


int main() {
    srand(time(NULL));
    cout << "Maldicion de la Dimensionalidad" << endl << endl;
    
    int points;
    int dim;
    cout << "Ingrese Numero de puntos: ";
    cin >> points;
    cout << "Ingrese Numero de Dimensiones: ";
    cin >> dim;

    vector<double> vecD;
    for (int i = 1; i <= points; i++) {
        for (int j = 1; j <= dim; j++){
            int num=rand()%101;
            double x = (double)num * 0.01;
            vecD.push_back(x);
        }
    }

    // int cont = 0;
    // for (int i = 0; i < vecD.size(); i += 2) {
    //     cont++;
    //     cout << cont << " Point:   " << vecD[i] << " - " << vecD[i + 1] << endl;
    // }

    distancia(points, dim, vecD);

    system("PAUSE");
    return 0;
}