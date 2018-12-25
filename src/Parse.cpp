#include "Parse.h"
#include "Utilitaire.h"

#include <cstring>

using namespace std;

Parse::Parse() {
  	this->txt_path = "../CONVERT/";
}

string Parse::recupTitre(string cheminFichier, string nomFichier)
{
	nomFichier.erase(nomFichier.size() - 4);
	string token;
	size_t pos = 0;
	// formater le nom de fichier
	while ((pos = nomFichier.find('_')) != string::npos) 
	{
    	token = nomFichier.substr(0, pos);
   		nomFichier.erase(0, pos + 1);
	}
	ifstream fichierConverti(cheminFichier, ios::in);
	string titre;
	int cpt = 0;
	if(fichierConverti)
	{
		// se placer aux bonnes endroits
		while (getline(fichierConverti, titre))
		{
			if(Utilitaire::foundWord(titre,nomFichier) == true)
				break;
		}
		int cpt;
		bool controle = false;
	  	do 
	  	{
			string bufferTitre;
			getline(fichierConverti, bufferTitre);
			if (bufferTitre == "" && cpt<2) 
			{
				cpt ++;
				continue;
			}
			else if ((isupper(bufferTitre[0]) && controle==false) || (!isupper(bufferTitre[0] && controle == false))  && cpt < 2) 
			{
				controle = true;
		 		titre += " " + bufferTitre;
		  		continue;
			}
		break;
	  	} while(true);
	  	fichierConverti.close();
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier !";
		cerr << "Error: " << strerror(errno);
	}
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
    system("rm -Rf ../PARSE");
    system("mkdir ../PARSE");
	ifstream fichier("PapersList_temp.txt", ios::in);
	if (fichier)
	{
		string ligne;
		string nameFormat;
		while(getline(fichier, ligne))
		{
			nameFormat = txt_path + ligne;
			ofstream fichierEcriture("../PARSE/" + ligne, ios::out | ios::trunc);
			if(fichierEcriture)
			{
				fichierEcriture << "Nom du fichier d'origine : " << ligne << endl;
				fichierEcriture << "Titre : " << recupTitre(nameFormat, ligne) << endl;
				fichierEcriture << "Resume : " << Utilitaire::formatage(recupResume(nameFormat)) << endl;
				fichierEcriture.close();
			}
			else cerr << "Impossible d'ouvrir le fichier !";
		}
		
		fichier.close();
		system("rm PapersList_temp.txt");
	}
	else cerr << "Impossible d'ouvrir le fichier !";
}
