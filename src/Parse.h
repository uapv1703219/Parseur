#pragma once

#include <iostream>
#include <fstream>

class Parse {
private:
  std::string cheminFichier;
  std::string txt_path;

public:
  Parse();
  std::string remplacement(std::string);
  std::string recupTitre(std::string);
  std::string recupResume(std::string);
  void exec();
  void ls();
};