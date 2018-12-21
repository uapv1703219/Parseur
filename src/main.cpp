#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "recup.h"
#include "Parse.h"

using namespace std;

int main()
{



	recup recuperation;

	recuperation.ls();
	recuperation.convert();

	Parse parse;
	parse.exec();

	return 0;
}