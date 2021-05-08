#pragma once
#include "Disciplina.h"
#include "RepoAbstract.h"
#include <string>
#include <iterator>
#include <vector>
#include <map>

class RepoLab :public Repo
{
private:
	std::map<int, Disciplina> discipline;
	double p;
	int id = 1;
	std::vector<Disciplina> vect;//vect actual de dis
	void throwRandomExcept();
public:
	RepoLab(double probability) :p{ probability } {}

	RepoLab(const RepoLab& rep) = delete;

	~RepoLab() = default;
	bool exist(const Disciplina& d)const;
	/// <summary>
	/// Adauga o disciplina
	/// </summary>
	/// <param name="d">Disciplina</param>
	void add(const Disciplina& d) override;
	/// <summary>
	/// Sterge o disciplina
	/// </summary>
	/// <param name="d"></param>
	/// <returns></returns>
	void del(const Disciplina& d) override;
	/// <summary>
	/// Modifica Disciplina d cu una noua
	/// </summary>
	/// <param name="d"></param>
	/// <param name="denumire"></param>
	/// <param name="nrOre"></param>
	/// <param name="profesor"></param>
	/// <param name="tip"></param>
	/// <returns></returns>
	void upd(const Disciplina& d_vechi, const Disciplina& d_nou)override;
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