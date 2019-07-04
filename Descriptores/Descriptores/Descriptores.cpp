// Descriptores.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
//#include <dirent>
//#include "dirent.h"

#include <stdio.h>

using namespace std;

string sym = "\"?¿!¡-_.,:;<>() ";
vector<string> stopwords;

class TextWord {
public:
	string word;
	int cant;
	TextWord(string _word) {
		word = _word;
		cant = 1;
	}
	void other_word() {
		cant++;
	}
};

void check_word(string &word) {
	int len_word = word.length();
	int len_sym = sym.size();

	for (int i = 0; i < len_word; i++) {
		int ubi = sym.find(word[i]);
		if (ubi > len_sym || ubi < 0) {
			word[i] = tolower(word[i]);
		}
		else {
			word.erase(i, 1);
			--len_word;
			--i;
		}
	}
}

void create_stopwords(string name) {
	char cadena[128];
	ifstream fe(name);

	string word;

	while (!fe.eof()) {
		fe >> cadena;
		word = cadena;
		stopwords.push_back(word);
	}
}

void descriptor_texto(string name, vector<TextWord*> &v) {
	char cadena[128];
	ifstream fe(name);

	string word;

	while (!fe.eof()) {
		fe >> cadena;
		word = cadena;
		check_word(word);

		int len_stopword = stopwords.size();
		bool stop_holder; // es o no es?
		int cont = 0;
		while (cont < len_stopword && stopwords[cont] != word) {
			++cont;
		}

		if (cont == len_stopword) {
			bool check = false;     // false = no lo encontro
			for (int i = 0; i < v.size(); i++) {
				if (v[i]->word == word) {
					v[i]->other_word();
					check = true;
					break;
				}
			}
			if (check == false) {
				TextWord *temp = new TextWord(word);
				v.push_back(temp);
			}
		}
	}
	fe.close();
}

bool is_file(string file) {
	FILE* archivo;
	if (archivo = fopen(file.c_str(), "r")) {
		fclose(archivo);
		return true;
	}
	else {
		return false;
	}
}

int main() {
	create_stopwords("stopwords.txt");
	
	vector<vector<TextWord*>> vall;

	string name;
	int cant;
	cant = 7000;
	
	ofstream fs("salida.txt");
	for (int cont = 1; cont <= cant; ++cont) {
		name = "docs/AP__" + to_string(cont + 14) + ".txt";

		if (is_file(name) == 1) {
			vector<TextWord*> v;
			descriptor_texto(name, v);

			fs << cont << " documento tiene: { ";
			for (int i = 0; i < v.size(); ++i) {
				fs << v[i]->word << "-" << v[i]->cant << "; ";
			}
			fs << " }" << endl;

			vall.push_back(v);
		}

	}

	cout << "hi" << endl;
	// creando el vector con todas las palabras
	vector<string> vbig;
	for (int i = 0; i < vall.size(); ++i) {
		for (int j = 0; j < vall[i].size(); ++j) {
			bool check = false;     // false = no se encuentra
			for (int b = 0; b < vbig.size(); ++b) {
				if (vbig[b] == vall[i][j]->word) {
					check = true;       // se encuentra
					break;
				}
			}
			if (check == false) {
				vbig.push_back(vall[i][j]->word);
			}
		}
	}
	cout << "hi" << endl;
	
	fs << "TODAS LAS PALABRAS: { ";
	for (int i = 0; i < vbig.size(); ++i) {
		fs << vbig[i] << "; ";
	}
	fs << " }" << endl;

	fs << " { ";
	for (int b = 0; b < vbig.size(); ++b) {
		for (int i = 0; i < vall.size(); ++i) {
			bool check = false;
			int valor;
			for (int j = 0; j < vall[i].size(); ++j) {
				if (vall[i][j]->word == vbig[b]) {
					check = true;
					valor = vall[i][j]->cant;
					break;
				}
			}
			if (check == true) {
				fs << vbig[b] << "-" << valor << "; ";
			}
			else if (check == false) {
				fs << vbig[b] << "-" << " 0; ";
			}
		}
		fs << endl;
	}


	fs.close();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
