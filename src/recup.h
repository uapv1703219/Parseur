#pragma once

#include <string>
#include <vector>

class recup
{
	private:
    std::string paper_path;
    std::string convert_path;

	public:
	recup();
	void affichage(std::vector<std::string>);
	std::vector<std::string> menu();
	void convert(std::vector<std::string>);
};
