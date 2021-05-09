#pragma once
#include "Repository.h"
#include <string> 
class RepositoryFile :public Repository
{
private:
	std::string fileName;
	void loadFromFile();
	void writeToFile();
public:
	RepositoryFile(std::string f) :Repository(), fileName{ f }{
		loadFromFile();
	}
	void add(const Disciplina& d)override {
		Repository::add(d);
		writeToFile();
	}
	void del(const Disciplina& d) override
	{
		Repository::del(d);
		writeToFile();
	}
	void upd(const Disciplina& d_vechi, const Disciplina& d_nou) override {
		Repository::upd(d_vechi, d_nou);
		writeToFile();
	}
};