#include "Parse.h"
#include "Utilitaire.h"

using namespace std;

Parse::Parse() {
  	this->txt_path = "../CONVERT/";
}

string Parse::recupTitre(string cheminFichier) {
  	ifstream fichierConverti(cheminFichier, ios::in);
  	string titre;
  	getline(fichierConverti, titre);
  	do {
		string bufferTitre;
		getline(fichierConverti, bufferTitre);
		if (bufferTitre == "") continue;
		else if (isupper(bufferTitre[0])) 
		{
	 		titre += " " + bufferTitre;
	  		continue;
		}
	break;
  	} while(true);
  	fichierConverti.close();
  	return titre;
}

string Parse::recupResume(string cheminFichier) 
{
	string resume = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	while (true) 
	{
		fichierConverti >> mot;
		mot = Utilitaire::to_lower(mot);
		if (mot.find("abstract") != string::npos || mot.find("resume") != string::npos) 
			break;
	}
	string bufferResume;
	while (true) 
	{
		getline(fichierConverti, bufferResume);
		if (Utilitaire::isEmpty(bufferResume) && !Utilitaire::isEmpty(resume)) 
			break;
		resume += bufferResume;
	}
	return resume;
}

void Parse::exec(){
	Utilitaire::ls(txt_path);
	ifstream fichier("PapersList_temp.txt", ios::in);
	if (fichier)
	{

		string ligne;
		string name_fichier;
		while(getline(fichier, ligne))
		{
		  	ligne = (txt_path + Utilitaire::remplacement(ligne));
		  	cout << recupTitre(ligne) << endl;
		  	cout << recupResume(ligne);
		}
		
		fichier.close();

		system("rm PapersList_temp.txt");
	}
	else cerr << "Impossible d'ouvrir le fichier !";
}