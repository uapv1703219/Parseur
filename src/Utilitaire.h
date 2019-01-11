#pragma once

class Utilitaire 
{
	public:
		static std::string remplacement(std::string, std::string, std::string);
		static std::string to_lower(std::string);
		static std::string formatage(std::string);
		static std::string conversion(std::string);
		static std::string suppressionTitre(std::string, std::string);
		static bool foundWord(std::string, std::string);
		static bool findCaractereNonAlphabetique(std::string);
		static bool controleRomain(std::string);
		static bool isEmpty(std::string);
		static void ls(std::string);
};
