#include "Parse.h"
#include <algorithm>

using namespace std;

string to_lower(string chaine) {
  std::transform(chaine.begin(), chaine.end(), chaine.begin(), ::tolower);
  return chaine;
}

bool isEmpty(string chaine) {
  for (int i = 0; i < chaine.size(); ++i) {
	if (isalnum(chaine[i])) return false;
  }
  return true;
}

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
	else if (isupper(bufferTitre[0])) {
	  titre += " " + bufferTitre;
	  continue;
	}
	break;
  } while(true);
  fichierConverti.close();
  return titre;
}

string Parse::recupResume(string cheminFichier) {
  string resume = "";
  ifstream fichierConverti(cheminFichier, ios::in);
  string mot;
  while (true) {
	fichierConverti >> mot;
	mot = to_lower(mot);
	if (mot.find("abstract") != string::npos || mot.find("resume") != string::npos) break;
  }
  string bufferResume;
  while (true) {
	getline(fichierConverti, bufferResume);
	if (isEmpty(bufferResume) && !isEmpty(resume)) break;
	resume += bufferResume;
  }
  return resume;
}

void Parse::exec(){
    
    ifstream fichier("PapersList_temp.txt", ios::in);
    if (fichier)
    {

        string ligne;
        string name_fichier;
        while(getline(fichier, ligne))
        {
            ligne = (txt_path + remplacement(ligne));
            cout << recupTitre(ligne) << endl;
            cout << recupResume(ligne);
         
        }
        
        fichier.close();

        system("rm PapersList_temp.txt");
    }
    else cerr << "Impossible d'ouvrir le fichier !";
}


void Parse::ls() {

    system(("ls " + txt_path + " > PapersList_temp.txt").c_str());
}

string Parse::remplacement(string name)
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