#pragma once
#include <cctype>
#include <iostream>
#include <vector>
#include "Repository.h"

class ValidateException {
	std::vector<std::string> messages;

public:
	/*
		Functie de initializare validator
		errors - eroors de afisat
	*/
	ValidateException(const std::vector<std::string>& errors) : messages{ errors } {};

	std::vector<std::string> GetMessages() {
		return messages;
	}

	friend std::ostream& operator<<(std::ostream& out, const ValidateException& err);
};
class ServiceException {
	std::string messages;

public:
	/*
		Functie de initializare validator
		errors - eroors de afisat
	*/
	ServiceException(const std::string& errors) : messages{ errors } {};
	friend std::ostream& operator<<(std::ostream& out, const ServiceException& err);
};

/*
	Functie de overload al operatorului <<
	out - streamul de scriere
	err - eroarea ce se afiseaza
*/
std::ostream& operator<<(std::ostream& out, const ServiceException& err);
std::ostream& operator<<(std::ostream& out, const ValidateException& err);
class Validator {
public:
	/*
		Functie care valideaza disciplina
		d-disciplina validata
	*/
	void ValidateDisciplina(const Disciplina& d);
	/*
	Functia care valideaza daca numele fisierului dat constine ".csv"
	*/
	void validateFile(const std::string file);
};