#include "Parse.h"
#include "Utilitaire.h"

#include <cstring>
#include <algorithm>

using namespace std;

Parse::Parse() {
  	this->txt_path = "../CONVERT/";
}

string Parse::recupTitre(string cheminFichier, string nomFichier)
{
	string auteur = recupAuteur(cheminFichier,nomFichier);
	nomFichier.erase(nomFichier.size() - 4);
	size_t pos = 0;
	// formater le nom de fichier
	while ((pos = nomFichier.find('_')) != string::npos)
	{
    	nomFichier.substr(0, pos);
   		nomFichier.erase(0, pos + 1);
	}
	ifstream fichierConverti(cheminFichier, ios::in);
	string titre;
	if(fichierConverti)
	{
		// se placer à la bonne position
		while (getline(fichierConverti, titre))
			if(Utilitaire::foundWord(titre,nomFichier))
				break;
		bool controle = false;
	  	do
	  	{
			string bufferTitre;
			getline(fichierConverti, bufferTitre);
			if (bufferTitre == "")
				continue;
			else if (!controle)
			{
				if(Utilitaire::foundWord(bufferTitre,auteur))
					break;
				controle = true;
		 		titre += " " + bufferTitre;
		  		continue;
			}
		break;
	  	} while(true);
	  	fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
    return titre;
}

string Parse::recupResume(string cheminFichier)
{
	string resume = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	if(fichierConverti)
	{
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
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	return resume;
}

string Parse::recupIntro(string cheminFichier)
{
	string intro = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	if(fichierConverti)
	{
		while (true)
		{
			fichierConverti >> mot;
			mot = Utilitaire::to_lower(mot);
			if (mot.find("introduction") != string::npos)
				break;
		}
		string bufferIntro;
		while (true)
		{
			getline(fichierConverti, bufferIntro);
      if (bufferIntro.find('\f') != std::string::npos) {
        do {
        	getline(fichierConverti, bufferIntro);
        } while (bufferIntro == "");
      }
      else if (estFinIntro(bufferIntro)) {
        return intro;
      }
      else {
        intro += bufferIntro;
      }
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	return intro;
}


string Parse::recupAuteur(string cheminFichier, string nomFichier)
{
	size_t pos = nomFichier.find('_');
    string nomAuteur = nomFichier.substr(0, pos);
   	ifstream fichierConverti(cheminFichier, ios::in);
   	string auteur;
   	if(fichierConverti)
   	{
   		while (getline(fichierConverti, auteur))
		{
			auteur = Utilitaire::conversion(auteur);
			size_t found = auteur.find(nomAuteur);
  			if (found!=string::npos)
  			{
  				pos = auteur.find(',');
  				auteur = auteur.substr(0,pos);
 				if(isdigit(auteur[auteur.size()-1]))
  					auteur.erase(auteur.size() - 1);
  				if(count( auteur.begin(), auteur.end(), ' ') > 1)
  					while(auteur[auteur.size()-1] != ' ')
  						auteur.erase(auteur.size() -1);
  				break;
  			}
		}
		fichierConverti.close();
   	}
   	else
   		cerr << "Impossible d'ouvrir le fichier !";
	return auteur;
}

string Parse::recupBibliographie(string cheminFichier, string auteur)
{
	string biblio = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	if(fichierConverti)
	{
		while (true)
		{
			getline(fichierConverti, mot);
			mot = Utilitaire::to_lower(mot);
			if (mot.find("references") != string::npos && mot.size() < 15)
				break;
		}
		string bufferBiblio;
		while (getline(fichierConverti, bufferBiblio))
		{
			if(bufferBiblio.find(auteur) != string::npos)
				break;
			biblio += bufferBiblio;
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	biblio.erase(biblio.size() - 1);
	return biblio;
}

void Parse::execTxt(){
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
	else
		cerr << "Impossible d'ouvrir le fichier !";
}

void Parse::execXML(){
    Utilitaire::ls(txt_path);
    system("rm -Rf ../PARSE");
    system("mkdir ../PARSE");
	ifstream fichier("PapersList_temp.txt", ios::in);
	if (fichier)
	{
		string ligne;
		string nameFormat;
		string nameFormat2;
		while(getline(fichier, ligne))
		{
			nameFormat = txt_path + ligne;
			nameFormat2 = ligne;
			nameFormat2.erase(nameFormat2.size() - 3);
			nameFormat2 += "xml";
			ofstream fichierEcriture("../PARSE/" + nameFormat2, ios::out | ios::trunc);
			if(fichierEcriture)
			{
				string auteur = recupAuteur(nameFormat, ligne);
				fichierEcriture << "<?xml version=\"1.0\"? encoding=\"UTF-8\"?>" << endl;
				fichierEcriture << "<article>" << endl;
				fichierEcriture << "\t <preamble> " << ligne << " </preamble>" << endl;
				fichierEcriture << "\t <titre> " << recupTitre(nameFormat, ligne) << " </titre>" << endl;
        fichierEcriture << "\t <introduction> " << recupIntro(nameFormat) << " </introduction>" << endl;
				fichierEcriture << "\t <auteur> " << auteur << " </auteur>" << endl;
				fichierEcriture << "\t <abstract> " << Utilitaire::formatage(recupResume(nameFormat)) << " </abstract>" << endl;
				fichierEcriture << "\t <biblio> " << recupBibliographie(nameFormat, auteur) << " </biblio>" << endl;
				fichierEcriture << "</article>";
				fichierEcriture.close();
			}
			else
				cerr << "Impossible d'ouvrir le fichier !";
		}
		fichier.close();
		system("rm PapersList_temp.txt");
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
}

bool Parse::estFinIntro(string ligne) {
  for (int i = 0; i < ligne.size(); ++i) {
    if (isalnum(ligne[i])) {
      if(ligne[i] == '2' || (ligne[i] == 'I' && ligne[i+1] == 'I')) {
        if (ligne[i] == '2') {
          return Utilitaire::suivantEstMajuscule(ligne, i+1);
        }
        else if (ligne[i] == 'I' && ligne[i+1] == 'I') {
          return Utilitaire::suivantEstMajuscule(ligne, i+2);
        }
      }
      return false;
    }
  }
  return false;
}
