#pragma once

#include <iostream>
#include <fstream>

class Parse {
private:
  	std::string cheminFichier;
  	std::string txt_path;

public:
  	Parse();
  	std::string recupTitre(std::string, std::string);
  	std::string recupResume(std::string);
  	void exec();
};
