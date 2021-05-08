#pragma once
#include "Disciplina.h"
#include <vector>
#include <iterator>
#include "RepoAbstract.h"
//#include "MyVector.h"
/// <summary>
/// Clasa Repository-containerul cu Discipline
/// </summary>

class Repository :public Repo
{
private:
	//MyVector<Disciplina> discipline;
	std::vector<Disciplina> discipline;
	bool exist(const Disciplina& d)const;
public:
	//constructor
	Repository() = default;
	//Copy constr,nu perimite copiere
	Repository(const Repository& rep) = delete;
	/// <summary>
	/// Adauga o disciplina
	/// </summary>
	/// <param name="d">Disciplina</param>
	virtual void add(const Disciplina& d) override;
	/// <summary>
	/// Sterge o disciplina
	/// </summary>
	/// <param name="d"></param>
	/// <returns></returns>
	virtual void del(const Disciplina& d) override;
	/// <summary>
	/// Modifica Disciplina d cu una noua
	/// </summary>
	/// <param name="d"></param>
	/// <param name="denumire"></param>
	/// <param name="nrOre"></param>
	/// <param name="profesor"></param>
	/// <param name="tip"></param>
	/// <returns></returns>
	virtual void upd(const Disciplina& d_vechi, const Disciplina& d_nou)override;
	/// <summary>
	/// Extrage toate disciplinele
	/// </summary>
	/// <returns></returns>
	/////////////////////////////////const MyVector<Disciplina>& getAll() const noexcept;
	const std::vector<Disciplina>& getAll() override;
	/// <summary>
	/// Returneaza numarul curent de discipline aflate in repo
	/// </summary>
	/// <returns></returns>
	const int sizeRepo() const noexcept override;
	//virtual void emptyRepo()noexcept;
	const Disciplina find(const std::string den, const std::string prof) const override;
	const int findPoz(const std::string den, const std::string prof) const override;
};


