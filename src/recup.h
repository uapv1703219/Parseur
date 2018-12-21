#pragma once

#include <string>
#include <vector>

class recup
{
	public:
	
	std::string paper_path;
	std::string convert_path;

	recup();
	void ls();
	void convert();
	std::string remplacement(std::string);
};