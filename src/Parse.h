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
  	std::string recupAuteur(std::string, std::string);
  	std::string recupBibliographie(std::string, std::string);
  	std::string recupConclusion(std::string);
  	std::string recupDiscussion(std::string);
  	void execTxt();
  	void execXML();
};
