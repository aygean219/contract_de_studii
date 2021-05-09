#pragma once
#include <string>
#include <iostream>
/// <summary>
/// Clasa Disciplina
/// @param: denumire(string),nrOre(int),cadruDidactic(string),tip(string)
/// </summary>

class Disciplina
{
private:
	std::string denumire;
	int nrOre;
	std::string cadruDidactic;
	std::string tip;
public:
	/// <summary>
	/// Constructorul implicit-atribuie null la stringuri si 0 la int
	/// </summary>
	Disciplina();
	/// <summary>
	/// constructorul cu parametrii
	/// </summary>
	/// <param name="denumire"> string </param>
	/// <param name="nrOre"> int </param>
	/// <param name="cadruDidactic"> string </param>
	/// <param name="tip"> string </param>
	Disciplina(const std::string denumire, int nrOre, const std::string cadruDidactic, const std::string tip);
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="d">Disciplina&</param>
	Disciplina(const Disciplina& d);
	/// <summary>
	/// Seteaza Denumirea
	/// </summary>
	/// < =""> string </param>
	void setDenumire(std::string);
	/// <summary>
	/// Seteaza nr de ore
	/// </summary>
	/// <param name=""> int </param>
	void setNrOre(int);
	/// <summary>
	/// Seteaza cadrul didactic
	/// </summary>
	/// <param name=""> string </param>
	void setCadruDidactic(std::string);
	/// <summary>
	/// Seteaza tipul
	/// </summary>
	/// <param name=""> string </param>
	void setTip(std::string);
	/// <summary>
	/// Returneaza denumirea disciplinei curente
	/// </summary>
	/// <returns> string </returns>
	std::string getDenumire()const;
	/// <summary>
	/// Returneaza numarul de ore a disciplinei curente
	/// </summary>
	/// <returns> int </returns>
	int getNrOre() const;
	/// <summary>
	/// Returneaza cadrul didactic al disciplinei curente
	/// </summary>
	/// <returns> string </returns>
	std::string getCadruDidactic() const;
	/// <summary>
	/// Returneaza tipul disciplinei curente
	/// </summary>
	/// <returns> string </returns>
	std::string getTip() const;
	/// <summary>
	/// Suprascrie operatorul =
	/// </summary>
	/// <param name="">Disciplina&</param>
	/// <returns></returns>
	Disciplina& operator=(const Disciplina&);
	/// <summary>
	/// Verifica daca 2 discipline sunt egale
	/// </summary>
	/// <param name="">Disciplina&</param>
	/// <returns></returns>
	bool operator==(const Disciplina&);
	/// <summary>
	/// Suprascrierea operatorului de afisare
	/// </summary>
	/// <param name="os"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	friend std::ostream& operator<<(std::ostream& os, const Disciplina& p);
};