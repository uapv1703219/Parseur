#include <string>
#include <algorithm>
#include "Utilitaire.h"

#include <iostream>

using namespace std;

//traitement string
string Utilitaire::remplacement(string chaine, string found, string remp)
{
	string temp;
	string token;
	size_t pos = 0;
	while ((pos = chaine.find(found)) != string::npos) 
	{
	    token = chaine.substr(0, pos);
	    chaine += token + remp;
	   	chaine.erase(0, pos + found.size());
	}
	temp += chaine;
	return temp;
}

string Utilitaire::formatage(string chaine)
{
	chaine = Utilitaire::remplacement(chaine,"\r", " ");
	chaine = Utilitaire::remplacement(chaine, "- ", "");

	for(int i = 0; i < chaine.size(); i++)
	{
		if (chaine.at(i) != ' ')
			return chaine.substr(i,chaine.size()); 
	}
}

bool Utilitaire::foundWord(string chaine, string chaine2)
{
	if(chaine.size() == 0)
	{
		return false;
	}
	for(int i = 0; i < 5; i++)
	{
		if(tolower(chaine[i]) != tolower(chaine2[i]))
			return false;
	}
	return true;
}

string Utilitaire::conversion(string chaine)
{
	size_t pos = chaine.find("´");
	string temp;
	if(pos != string::npos)
	{
    	temp = chaine.substr(0, pos);
   		chaine.erase(0, pos + 2);
   		chaine = temp + chaine;
	}
	return chaine;
}

string Utilitaire::to_lower(string chaine) 
{
  	transform(chaine.begin(), chaine.end(), chaine.begin(), ::tolower);
  	return chaine;
}

bool Utilitaire::isEmpty(string chaine) 
{
  	for (int i = 0; i < chaine.size(); i++) 
  	{
		if (isalnum(chaine[i])) 
			return false;
  	}
 	return true;
}

//traitement parcours fichiers
void Utilitaire::ls(string path)
{
	system(("ls " + path + " > PapersList_temp.txt").c_str());
}