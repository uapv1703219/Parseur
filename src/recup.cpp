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

void recup::affichage(vector<string> bufferTemp)
{
	system("clear");
	for(int i = 0; i < bufferTemp.size(); i++)
		cout << i << ":" << bufferTemp.at(i) << endl;
}

vector<string> recup::menu()
{
	Utilitaire::ls(paper_path);
	ifstream fichier("PapersList_temp.txt", ios::in);
	vector<string> bufferTemp;
	vector<string> bufferText;
	if(fichier)
	{
		string ligne;
		while(getline(fichier,ligne))
		{
			bufferTemp.push_back(ligne);
		}
		fichier.close();
		system("rm PapersList_temp.txt");
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";

	int temp = 0;
	do
	{
		cout << "Liste des pdf non traiter : " << endl;
		affichage(bufferTemp);
		cout << "Choisir les pdf à traiter (rentré les numeros du pdf, -1 pour arreter) :" << endl;
		cin >> temp;
		if(temp >= 0 && temp < bufferTemp.size())
		{
			bufferText.push_back(bufferTemp.at(temp));
			bufferTemp.erase(bufferTemp.begin()+temp);
		}
	}
	while(temp >= 0);
	affichage(bufferText);
	return bufferText;
}

void recup::convert(vector<string> bufferText) 
{
	system("rm -R ../CONVERT/*");
	string name_fichier;
	string ligne;
	for(int i = 0; i < bufferText.size(); i++)
	{
		name_fichier = bufferText.at(i);
		name_fichier = Utilitaire::remplacement(name_fichier, " ", "\\ ");
		ligne = Utilitaire::remplacement(bufferText.at(i), " ", "\\ ");
		name_fichier.erase(name_fichier.size() - 4);
		system(("pdf2txt -o " + convert_path + name_fichier + ".txt " + paper_path + ligne).c_str());
	}
}
