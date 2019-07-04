#include <iostream>
#include <string>
#include <fstream>


// to_string(cont + 14)
// #define _CRT_SECURE_NO_WARNINGS
bool is_file(std::string file)
{
	FILE* archivo;
	if (archivo = fopen(file.c_str(), "r"))
    {
		fclose(archivo);
		return true;
	}
	else
    {
		return false;
	}
}

void create_stopwords(std::string name) {
	char cadena[128];
	std::ifstream fe(name);

	std::string word;

	while (!fe.eof()) {
		fe >> cadena;
		word = cadena;
        // agregar a donde quieras
	}
}

int main()
{


    return 0;
}