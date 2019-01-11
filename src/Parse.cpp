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
	ifstream fichierConverti(cheminFichier, ios::in);
	string auteur = recupAuteur(cheminFichier,nomFichier);
	string titre;
	if(fichierConverti)
	{
		while(getline(fichierConverti, titre))
		{
			if(Utilitaire::findCaractereNonAlphabetique(titre))
			{
				bool controle;
				string bufferTitre;
				while(getline(fichierConverti, bufferTitre))
				{
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
				}
				break;
			}
		}
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
		fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	return resume;
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

string Parse::recupAuteur2(string cheminFichier, string titre)
{
	ifstream fichierConverti(cheminFichier, ios::in);
	string auteur;
	string bufferTemp;
	if(fichierConverti)
	{
		while(getline(fichierConverti, bufferTemp))
		{
			if(Utilitaire::findCaractereNonAlphabetique(bufferTemp))
			{
				while(getline(fichierConverti, auteur))
				{
					if(Utilitaire::to_lower(auteur).find("abstract") != string::npos || auteur.size() == 1)
						break;
					else if(auteur.find("@") != string::npos)
						continue;
					else if(auteur != "" && auteur != " ")
						bufferTemp += " " + auteur;
				}
				break;
			}
		}
		fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	bufferTemp = Utilitaire::suppressionTitre(bufferTemp,titre);
	return bufferTemp;
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
			biblio += bufferBiblio + " ";
			if(biblio[biblio.size()-1] == '-')
			{
				biblio.erase(biblio.size() - 1);
			}
			else if(biblio[biblio.size()-1] !=  ' ')
			{
				biblio += " ";
			}
		}
		fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	biblio.erase(biblio.size() - 1);
	biblio = Utilitaire::remplacement(biblio,"\f", " ");
	return biblio;
}

string Parse::recupConclusion(string cheminFichier)
{
	string conclu = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	bool controle = false;
	if(fichierConverti)
	{
		while(true)
		{
			getline(fichierConverti, mot);
			mot = Utilitaire::to_lower(mot);
			if(mot.size() == 0)
			{
				controle = true;
				continue;
			}
			if(mot.find("conclusion") != string::npos && controle == true && (isdigit(mot[0]) || (mot.find("\f") != string::npos ) || Utilitaire::controleRomain(mot)))
			{
				break;
			}
			else
				controle = false;
		}
		string bufferConclusion;
		string bufferTemp;
		int compteur = 0;
		while(getline(fichierConverti, bufferConclusion))
		{
			bufferTemp = Utilitaire::to_lower(bufferConclusion);
			if(bufferTemp.find("references") != string::npos || bufferTemp.find("acknowledgment") != string::npos)
				break;
			else if (bufferConclusion.find("\f") != string::npos)
			{
				compteur = 2;
				continue;
			}
			if(compteur > 0)
			{
				compteur -= 1;
				continue;
			}
			conclu += bufferConclusion;
			if(conclu[conclu.size()-1] == '-')
			{
				conclu.erase(conclu.size() - 1);
			}
			else if(conclu[conclu.size()-1] !=  ' ')
			{
				conclu += " ";
			}
		}
		fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	conclu.erase(conclu.size() - 1);
	conclu = Utilitaire::remplacement(conclu,"\f", " ");
	return conclu;
}

string Parse::recupDiscussion(string cheminFichier)
{
	string discu = "";
	ifstream fichierConverti(cheminFichier, ios::in);
	string mot;
	string bufferTemp;
	bool controle;
	if(fichierConverti)
	{
		while(getline(fichierConverti, mot))
		{
			if(mot.find("Discussion") != string::npos )
			{
				string bufferDiscussion;
				string bufferTemp;
				while(getline(fichierConverti,bufferDiscussion))
				{
					bufferTemp = Utilitaire::to_lower(bufferDiscussion);
					if(bufferTemp.find("conclusion") != string::npos)
						break;
					discu += bufferDiscussion;
					if(discu[discu.size()-1] == '-')
					{
						discu.erase(discu.size() - 1);
					}
					else if(discu[discu.size()-1] !=  ' ')
					{
						discu += " ";
					}
				}
				discu.erase(discu.size() - 1);
				break;
			}
		}
		fichierConverti.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
	discu = Utilitaire::remplacement(discu,"\f", " ");
	return discu;
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
				string titre = recupTitre(nameFormat, ligne);
				fichierEcriture << "<?xml version = \"1.0\" encoding=\"UTF-8\"?>" << endl;
				fichierEcriture << "<article>" << endl;
				fichierEcriture << "\t <preamble> " << ligne << " </preamble>" << endl;
				fichierEcriture << "\t <titre> " << titre << " </titre>" << endl;
				fichierEcriture << "\t <auteur> " << recupAuteur2(nameFormat, titre) << " </auteur>" << endl;
				fichierEcriture << "\t <abstract> " << Utilitaire::formatage(recupResume(nameFormat)) << " </abstract>" << endl;
				fichierEcriture << "\t <biblio>" << recupBibliographie(nameFormat, auteur) << " </biblio>" << endl;
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

void Parse::execXML2(){
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
				string titre = recupTitre(nameFormat, ligne);
				fichierEcriture << "<?xml version = \"1.0\" encoding=\"UTF-8\"?>" << endl;
				fichierEcriture << "<article>" << endl;
				fichierEcriture << "\t <preamble> " << ligne << " </preamble>" << endl;
				fichierEcriture << "\t <titre> " << titre << " </titre>" << endl;
				fichierEcriture << "\t <auteur> " << recupAuteur2(nameFormat,titre) << " </auteur>" << endl;
				fichierEcriture << "\t <abstract> " << Utilitaire::formatage(recupResume(nameFormat)) << " </abstract>" << endl;
				fichierEcriture << "\t <conclusion>" << recupConclusion(nameFormat) << " </conclusion>" << endl;  
				fichierEcriture << "\t <discussion>" << recupDiscussion(nameFormat) << " </discussion>" << endl;
				fichierEcriture << "\t <biblio>" << recupBibliographie(nameFormat, auteur) << " </biblio>" << endl;
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