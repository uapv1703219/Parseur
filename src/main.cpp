#include "recup.h"
#include "Parse.h"
#include <string.h>
#include <cstdlib>

using namespace std;

int main (int argc, char *argv[])
{
	if(argc < 2)
	{
		cout << "Arguments manquants, arguments possible : -t, -x" << endl;
		return EXIT_FAILURE ;
	}
	recup recuperation;
	//recuperation.convert();
	Parse parse;
	if(strcmp(argv[1],"-t") == 0)
	{
		//traiter TXT
		parse.execTxt();
	}
	else if(strcmp(argv[1],"-x") == 0)
	{
		//traiter XML
		parse.execXML();
	}
	else
	{
		cout << "Arguments incorrecte, arguments possible : -t, -x" << endl;
		return EXIT_FAILURE ;
	}	

	return EXIT_SUCCESS;
}
