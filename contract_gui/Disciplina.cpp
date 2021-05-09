#include "Disciplina.h"

Disciplina::Disciplina()
{
	this->nrOre = 0;
}
Disciplina::Disciplina(const std::string denumire, int ore, const std::string profesor, const std::string tip)
{
	this->denumire = denumire;
	this->nrOre = ore;
	this->cadruDidactic = profesor;
	this->tip = tip;
}
Disciplina::Disciplina(const Disciplina& d)
{
	//std::cout << "Constructorul de copiere a fost apelat" << std::endl;
	this->denumire = d.denumire;
	this->nrOre = d.nrOre;
	this->cadruDidactic = d.cadruDidactic;
	this->tip = d.tip;
}

void Disciplina::setDenumire(std::string d)
{
	this->denumire = d;
}

void Disciplina::setNrOre(int ore)
{
	this->nrOre = ore;
}

void Disciplina::setCadruDidactic(std::string profesor)
{
	this->cadruDidactic = profesor;
}

void Disciplina::setTip(std::string t)
{
	this->tip = t;
}

std::string Disciplina::getDenumire() const
{
	return this->denumire;
}

int Disciplina::getNrOre() const
{
	return this->nrOre;
}

std::string Disciplina::getCadruDidactic() const
{
	return this->cadruDidactic;
}
std::string Disciplina::getTip() const
{
	return this->tip;
}

Disciplina& Disciplina::operator=(const Disciplina& d)
{
	this->setDenumire(d.denumire);
	this->setCadruDidactic(d.cadruDidactic);
	this->setNrOre(d.nrOre);
	this->setTip(d.tip);
	return *this;
}

bool Disciplina::operator==(const Disciplina& d)
{
	return (this->denumire == d.denumire) && (this->cadruDidactic == d.cadruDidactic)
		&& (this->nrOre == d.nrOre) && (this->tip == d.tip);
}
std::ostream& operator<<(std::ostream& os, const Disciplina& p)
{
	os << "---Denumire:" << p.denumire << "---NrOre: " << p.nrOre << "---Cadru Didactic: " << p.cadruDidactic << "---Tip: " << p.tip << " ;" << std::endl;
	return os;
}