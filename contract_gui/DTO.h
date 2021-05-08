#pragma once
#include <string>
#include <iostream>
class DTO
{
private:
	int nrAparitii = 1;
	std::string tip;
public:

	DTO();

	DTO(const std::string tip);

	DTO(const DTO& d);

	~DTO();

	void setTip(std::string);

	void setNrAparitii(int);

	int getNrAparitii() const;

	std::string getTip() const;

	void add() noexcept;
};
