#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "recup.h"

using namespace std;

int main()
{

	/*string s = "The quick brown fox jumps over the lazy dog.";
  	replace( s.begin(), s.end(), ' ', '/' );
  	cout << s << endl;*/

	recup recuperation;

	recuperation.ls();
	recuperation.convert();

	//system("pdf2txt -o ../CONVERT/test ../Papers/Alexandrov_2015_A\\ Modified\\ Tripartite\\ Model\\ for\\ Document\\ Representation\\ in\\ Internet\\ Sociology.pdf");
	return 0;
}