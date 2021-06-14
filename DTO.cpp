#include "DTO.h"
DTO::DTO()
{
	//this->nrAparitii = 0;
}

DTO::DTO(const std::string tip)
{
	this->tip = tip;
}

DTO::DTO(const DTO& d)
{
	this->nrAparitii = d.nrAparitii;
	this->tip = d.tip;
}

DTO::~DTO()
{
}

void DTO::setTip(std::string d)
{
	this->tip = d;
}

void DTO::setNrAparitii(int d)
{
	this->nrAparitii = d;
}

int DTO::getNrAparitii() const
{
	return this->nrAparitii;
}

std::string DTO::getTip() const
{
	return this->tip;
}

void DTO::add() noexcept
{
	this->nrAparitii++;
}