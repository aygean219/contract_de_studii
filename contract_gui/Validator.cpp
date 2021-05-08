#include "Validator.h"
#include "Disciplina.h"

void Validator::ValidateDisciplina(const Disciplina& d)
{
	std::vector <std::string> messages;
	if (d.getCadruDidactic().size() == 0) messages.push_back("Cadrul didactic trebuie sa existe!!");
	if (d.getDenumire().size() == 0) messages.push_back("Denumirea trebuie sa existe!!");
	if (d.getTip().size() == 0) messages.push_back("Tipul trebuie sa existe!!");
	if (d.getNrOre() < 2) messages.push_back("Numarul de ore nu poate fii mai mic decat 2!!");
	if (messages.size() > 0)
		throw ValidateException(messages);
}

void Validator::validateFile(const std::string file)
{
	int ok = 0;
	std::vector <std::string> messages;
	if (0 <= file.find(".csv") && file.find(".csv") < file.size())
	{
		ok = 1;
	}
	if (ok == 0)
	{
		messages.push_back("Tipul trebuie sa fie CSV!!");
	}
	if (messages.size() > 0)
		throw ValidateException(messages);
}
std::ostream& operator<<(std::ostream& out, const ValidateException& err) {
	for (const auto& message : err.messages)
		out << message << "\n";
	return out;
}
std::ostream& operator<<(std::ostream& out, const ServiceException& err) {
	out << err.messages << "\n";
	return out;
}