#include "Parse.h"
#include "Utilitaire.h"

#include <cstring>
#include <algorithm>

using namespace std;

Parse::Parse() {
	this->txt_path = "../CONVERT/";
}

string Parse::recupTitre(string cheminFichier, string auteur)
{
	ifstream fichierConverti(cheminFichier, ios::in);
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
  fichierConverti.close();
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
  		  	if (mot.find("introduction") != string::npos) {
  			  break;
        }
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
        fichierConverti.close();
        return intro;
      }
      else {
        intro += bufferIntro;
      }
	}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
  fichierConverti.close();
	return intro;
}

string Parse::recupCorp(string cheminFichier)
{
	string texte = "";
  string bufferTexte;
	ifstream fichierConverti(cheminFichier, ios::in);
	if(fichierConverti)
	{
		while (true)
		{
      getline(fichierConverti, bufferTexte);
			if (Parse::estFinIntro(bufferTexte))
				break;
		}
		while (getline(fichierConverti, bufferTexte))
		{
      if (bufferTexte.find('\f') != std::string::npos) {
        do {
        	getline(fichierConverti, bufferTexte);
        } while (bufferTexte == "");
      }
      else if (estFinCorp(bufferTexte)) {
        fichierConverti.close();
        return texte;
      }
      else {
        texte += bufferTexte;
      }
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !";
  fichierConverti.close();
	return texte;
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
  fichierConverti.close();
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
				string titre = recupTitre(nameFormat, titre);
				string auteur = recupAuteur2(nameFormat, titre);
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
				string titre = recupTitre(nameFormat, titre);
				string auteur = recupAuteur2(nameFormat, titre);
				fichierEcriture << "<?xml version = \"1.0\" encoding=\"UTF-8\"?>" << endl;
				fichierEcriture << "<article>" << endl;
				fichierEcriture << "\t <preamble> " << ligne << " </preamble>" << endl;
				fichierEcriture << "\t <titre> " << titre << " </titre>" << endl;
				fichierEcriture << "\t <auteur> " << auteur << " </auteur>" << endl;
				fichierEcriture << "\t <abstract> " << Utilitaire::formatage(recupResume(nameFormat)) << " </abstract>" << endl;
				fichierEcriture << "\t <intro> " << recupIntro(nameFormat) << " </intro>" << endl;
        		fichierEcriture << "\t <corp> " << recupCorp(nameFormat) << " </corp>" << endl;
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

bool Parse::estFinIntro(string ligne) {
  for (int i = 0; i < ligne.size(); ++i) {
    if (isalnum(ligne[i])) {
      if(ligne[i] == '2') {
        return Utilitaire::suivantEstMajuscule(ligne, i+1);
      }
      else if (ligne[i] == 'I' && ligne[i+1] == 'I') {
        return Utilitaire::suivantEstMajuscule(ligne, i+2 );
      }
      return false;
    }
  }
  return false;
}

bool Parse::estFinCorp(string ligne) {
  return (estDebutConclusion(ligne) || ligne.find("Discusion") != string::npos);
}

bool Parse::estDebutConclusion(string ligne) {
  ligne = Utilitaire::to_lower(ligne);
  return (ligne.find("conclusion") != string::npos && (isdigit(ligne[0]) || (ligne.find("\f") != string::npos ) || Utilitaire::controleRomain(ligne)));
}
