#include "Validator.h"
#include "Disciplina.h"

void Validator::ValidateDisciplina(const Disciplina& d)
{
	std::vector <std::string> messages;
	if (d.getCadruDidactic().size() == 0) messages.push_back("You must enter the teacher's name!!");
	if (d.getDenumire().size() == 0) messages.push_back("You must enter the discipline name!!");
	if (d.getTip().size() == 0) messages.push_back("You must enter the type!!");
	if (d.getNrOre() < 2) messages.push_back("Number of hours must be greater than 2!!");
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
		messages.push_back("Type must to be CSV!!");
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