#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

#include "recup.h"
#include "Utilitaire.h"

using namespace std;

recup::recup()
{
	paper_path = "../Papers/";
	convert_path = "../CONVERT/";
}

void recup::convert() 
{
	Utilitaire::ls(paper_path);
	ifstream fichier("PapersList_temp.txt", ios::in);
	if (fichier)
	{
		string ligne;
		string name_fichier;
		while(getline(fichier, ligne))
		{
			name_fichier = ligne;
			
			name_fichier = Utilitaire::remplacement(name_fichier);
			ligne = Utilitaire::remplacement(ligne);
			name_fichier.erase(name_fichier.size() - 4);
			system(("pdf2txt -o " + convert_path + name_fichier + ".txt " + paper_path + ligne).c_str());
		}
		
		fichier.close();

		system("rm PapersList_temp.txt");
	}
	else cerr << "Impossible d'ouvrir le fichier !";
}
