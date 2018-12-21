#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "recup.h"

#include <string>

using namespace std;

recup::recup()
{
	paper_path = "../Papers/";
	convert_path = "../CONVERT/";
}

void recup::ls() {

	system(("ls " + paper_path + " > PapersList_temp.txt").c_str());
}

void recup::convert() {

	ifstream fichier("PapersList_temp.txt", ios::in);
	if (fichier)
	{
		string ligne;
		string name_fichier;
		while(getline(fichier, ligne))
		{
			name_fichier = ligne;
			
			name_fichier = remplacement(name_fichier);
			ligne = remplacement(ligne);
			name_fichier.erase(name_fichier.size() - 4);
			system(("pdf2txt -o " + convert_path + name_fichier + ".txt " + paper_path + ligne).c_str());
		}
		
		fichier.close();

		system("rm PapersList_temp.txt");
	}
	else cerr << "Impossible d'ouvrir le fichier !";
}

string recup::remplacement(string name)
{
	string temp;
	size_t pos = 0;
	string token;
	while ((pos = name.find(" ")) != string::npos) 
	{
	    token = name.substr(0, pos);
	    temp += token + "\\ ";
	    name.erase(0, pos + 1);
	}
	temp += name;
	//cout << temp << endl;
	return temp;
}