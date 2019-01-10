#include "recup.h"
#include "Parse.h"
#include <string.h>
#include <cstdlib>

using namespace std;

int main (int argc, char *argv[])
{
	if(argc < 2)
	{
		cout << "arguments possible : -t, -x -c, -x -n" << endl;
		return EXIT_FAILURE;
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
		if(strcmp(argv[2], "-n") == 0)
		{
			//traiter XML non complet
			parse.execXML();
		}
		else if(strcmp(argv[2], "-c") == 0)
		{
			//traiter XML complet
			parse.execXML2();
		}
		else
		{
			cout << "Arguments incorrecte, arguments possible : -t, -x -c, -x -n" << endl;
			cout << "-x -n pour XML non complet, -x -c pour XML complet(introduction, corps, conclusion et discussion)" << endl;
			return EXIT_FAILURE ;
		}
	}
	else
	{
		cout << "Arguments incorrecte, arguments possible : -t, -x -c, -x -n" << endl;
		cout << "-x -n pour XML non complet, -x -c pour XML complet(introduction, corps, conclusion et discussion)" << endl;
		return EXIT_FAILURE ;
	}	

	return EXIT_SUCCESS;
}
