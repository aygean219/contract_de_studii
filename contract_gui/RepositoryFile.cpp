#include "RepositoryFile.h"
#include <fstream>
#include "Validator.h"
void RepositoryFile::loadFromFile()
{
	std::ifstream f(this->fileName);
	if (!f.is_open())
	{
		std::vector<std::string> messages;
		messages.push_back("Error open : " + fileName);
		throw ValidateException(messages);
	}
	if (f.is_open())
	{
		std::string linie;
		std::string delim = ",";
		while (getline(f, linie))
		{
			int pos = linie.find(delim);
			std::string denumire = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			pos = linie.find(delim);
			int nrOre = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			pos = linie.find(delim);
			std::string cadruDidactic = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			pos = linie.find(delim);
			std::string tip = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			Disciplina d(denumire, nrOre, cadruDidactic, tip);
			Repository::add(d);
		}
		f.close();
	}
}
void RepositoryFile::writeToFile()
{
	std::ofstream f(fileName);
	if (!f.is_open())
	{
		std::vector<std::string> messages;
		messages.push_back("Error open : " + fileName);
		throw ValidateException(messages);
	}
	for (auto& d : getAll())
	{
		f << d.getDenumire() << "," << d.getNrOre() << "," << d.getCadruDidactic() << "," << d.getTip() << std::endl;
	}
}