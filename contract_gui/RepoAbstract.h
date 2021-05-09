#pragma once
#include "Disciplina.h"
#include <vector>
#include <ostream>
#include <string>


//Interfata-Clasa abstracta
class Repo {
public:
	Repo() = default;
	virtual ~Repo() = default;
	Repo(const Repo& rep) = delete;
	/// <summary>
	/// Adauga o disciplina
	/// </summary>
	/// <param name="d">Disciplina</param>
	virtual void add(const Disciplina& d) = 0;
	/// <summary>
	/// Sterge o disciplina
	/// </summary>
	/// <param name="d"></param>
	/// <returns></returns>
	virtual void del(const Disciplina& d) = 0;
	/// <summary>
	/// Modifica Disciplina d cu una noua
	/// </summary>
	/// <param name="d"></param>
	/// <param name="denumire"></param>
	/// <param name="nrOre"></param>
	/// <param name="profesor"></param>
	/// <param name="tip"></param>
	/// <returns></returns>
	virtual void upd(const Disciplina& d_vechi, const Disciplina& d_nou) = 0;
	/// <summary>
	/// Extrage toate disciplinele
	/// </summary>
	/// <returns></returns>
	/////////////////////////////////const MyVector<Disciplina>& getAll() const noexcept;
	virtual const std::vector<Disciplina>& getAll() = 0;
	/// <summary>
	/// Returneaza numarul curent de discipline aflate in repo
	/// </summary>
	/// <returns></returns>
	virtual const int sizeRepo() const noexcept = 0;
	virtual const int findPoz(const std::string den, const std::string prof) const = 0;
	virtual const Disciplina find(const std::string den, const std::string prof) const = 0;
};
class DisciplinaRepoException {
private:
	std::string msg;
public:
	DisciplinaRepoException(const std::string message) : msg{ message } {
	}
	std::string GetMessages() {
		return msg;
	}
	//functie friend (vreau sa folosesc membru privat msg)
	friend std::ostream& operator<<(std::ostream& out, const DisciplinaRepoException& ex);

};

std::ostream& operator<<(std::ostream& out, const DisciplinaRepoException& ex);