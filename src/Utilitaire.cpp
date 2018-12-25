#include <string>
#include <algorithm>
#include "Utilitaire.h"

#include <iostream>

using namespace std;

//traitement string
string Utilitaire::remplacement(string name, string found, string remp)
{
	string temp;
	string token;
	size_t pos = 0;
	while ((pos = name.find(found)) != string::npos) 
	{
	    token = name.substr(0, pos);
	    temp += token + remp;
	   	name.erase(0, pos + found.length());
	}
	temp += name;
	return temp;
}

string Utilitaire::formatage(string name)
{
	name = Utilitaire::remplacement(name,"\r", " ");
	name = Utilitaire::remplacement(name, "- ", "");

	string tmp;
	for(int i = 0; i < name.length(); i++)
	{
		if (name.at(i) != ' ')
		{
			tmp = name.substr(i,name.length());
			return tmp; 
		}
	}
}

bool Utilitaire::foundWord(string name, string nomFichier)
{
	if(name.length() == 0)
	{
		return false;
	}
	for(int i = 0; i < 5; i++)
	{
		if(tolower(name[i]) != tolower(nomFichier[i]))
		{
			return false;
		}
	}
	return true;
}

string Utilitaire::to_lower(string name) 
{
  	transform(name.begin(), name.end(), name.begin(), ::tolower);
  	return name;
}

bool Utilitaire::isEmpty(string name) 
{
  	for (int i = 0; i < name.size(); i++) 
  	{
		if (isalnum(name[i])) 
			return false;
  	}
 	return true;
}

//traitement parcours fichiers
void Utilitaire::ls(string path)
{
	 system(("ls " + path + " > PapersList_temp.txt").c_str());
}