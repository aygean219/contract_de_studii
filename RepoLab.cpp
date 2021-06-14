#include "RepoLab.h"
double randomDouble() {
	return ((double)rand()) / (double)RAND_MAX;
}
void RepoLab::throwRandomExcept()
{
	const double val = randomDouble();
	if (val <= this->p) {
		throw DisciplinaRepoException("Random Exception!");
	}
}

bool RepoLab::exist(const Disciplina& d) const
{
	try {
		find(d.getDenumire(), d.getCadruDidactic());
		return true;
	}
	catch (DisciplinaRepoException&)
	{
		return false;
	}
}

void RepoLab::add(const Disciplina& d)
{
	this->throwRandomExcept();
	if (exist(d))
	{
		throw DisciplinaRepoException("Exista deja disciplina cu denumirea : " + d.getDenumire() + " si cadrul didactic: " + d.getCadruDidactic());
	}
	discipline.insert({ id,d });
	id = id + 1;
}

void RepoLab::del(const Disciplina& d)
{
	this->throwRandomExcept();

	try {
		const int poz = findPoz(d.getDenumire(), d.getCadruDidactic());
		discipline.erase(poz);
	}
	catch (const DisciplinaRepoException& ex)
	{
		throw DisciplinaRepoException(ex);
	}
}

void RepoLab::upd(const Disciplina& d_vechi, const Disciplina& d_nou)
{
	this->throwRandomExcept();

	try {
		const int poz = findPoz(d_vechi.getDenumire(), d_vechi.getCadruDidactic());
		discipline.at(poz - 1).setCadruDidactic(d_nou.getCadruDidactic());
		discipline.at(poz - 1).setDenumire(d_nou.getDenumire());
		discipline.at(poz - 1).setTip(d_nou.getTip());
		discipline.at(poz - 1).setNrOre(d_nou.getNrOre());
	}
	catch (const DisciplinaRepoException& ex)
	{
		throw DisciplinaRepoException(ex);
	}
}

const std::vector<Disciplina>& RepoLab::getAll()
{
	vect.clear();
	for (auto it = discipline.begin(); it != discipline.end(); ++it) {
		vect.push_back(it->second);
	}
	return vect;
}

const int RepoLab::sizeRepo() const noexcept
{
	return discipline.size();
}

const Disciplina RepoLab::find(const std::string den, const std::string prof) const
{
	for (auto it = discipline.begin(); it != discipline.end(); it++)
	{
		if (it->second.getDenumire() == den && it->second.getCadruDidactic() == prof)
		{
			return it->second;
		}
	}
	throw DisciplinaRepoException("NU exista deja disciplina cu denumirea : " + den + " si cadrul didactic: " + prof);
}


const int RepoLab::findPoz(const std::string den, const std::string prof) const
{
	for (auto it = discipline.begin(); it != discipline.end(); it++)
	{
		if (it->second.getDenumire() == den && it->second.getCadruDidactic() == prof)
		{
			return it->first;
		}
	}
	throw DisciplinaRepoException("NU exista deja disciplina cu denumirea : " + den + " si cadrul didactic: " + prof);
}
