#include <string>
#include <algorithm>
#include "Utilitaire.h"

using namespace std;

//traitement string
string Utilitaire::remplacement(string name)
{
	string temp;
	string token;
	size_t pos = 0;
	while ((pos = name.find(" ")) != string::npos) 
	{
	    token = name.substr(0, pos);
	    name += token + "\\ ";
	    name.erase(0, pos + 1);
	}
	temp += name;
	return name;
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