#pragma once
#include "Repository.h"
#include "Undo.h"
#include "DTO.h"
#include "Validator.h"
#include <functional>
#include <vector>
#include <random>
#include <iterator>
#include <fstream>
#include <map>
using std::unique_ptr;
// Functie de comparare doua discipline dupa un anumit criteriu
typedef bool(*functie) (const Disciplina&, const Disciplina&);
class Contract {
	std::vector<Disciplina> contract_pe_an;
public:
	//Constructorul predefinit
	Contract() = default;
	/*
	Functie de adaugare disciplina pe contract
	*/
	void AddDisciplina(const Disciplina& d)
	{
		contract_pe_an.push_back(d);
	}
	//functie de getAll disipline
	const std::vector<Disciplina>& GetAll() const noexcept {
		return contract_pe_an;
	}
	void DeleteContract() noexcept
	{
		contract_pe_an.clear();
	}
};
class Service
{
private:
	Repo& repo;//repo
	Validator& val;//clasa de validare a datelor
	Contract contract;
	std::vector<unique_ptr<Undo>> undo;
	std::vector<unique_ptr<Undo>> redo;


	std::vector<Disciplina> Sort(functie f) const;//functia generica de sortare a elementelor
	std::vector<Disciplina> filter(std::function <bool(const Disciplina&)> f) const;//functia generica de filtrare
public:
	/*
		Functie de creare service
		rep - repository medicamente
		postconditii: obiect de tip service
	*/
	Service(Repo& rep) noexcept :repo{ rep }, val{ val }{};
	//nu permite copierea
	Service(const Service& serv) = delete;
	// Functie de distrugere service
	/*
		Adauga disciplina
		d-disciplina adaugata
	*/
	void addDisciplina(const Disciplina& d);

	//Functie care returneaza toate disciplinele curente
	const std::vector<Disciplina>& getAll();

	/*
		Sterge disciplina d ,daca exista
	*/
	void deleteDisciplina(const Disciplina& d);

	/*
	Modifica disciplina d_vechi ,daca exista cu disciplina d_nou
	*/
	void updateDisciplina(const Disciplina& d_vechi, const Disciplina& d_nou);

	//dimensiunea listei de discipline
	int sizeService();

	/// <summary>
	/// Cauta Disciplina cu denumirea data si acel profesor
	/// </summary>
	/// <param name="den"></param>
	/// <param name="prof"></param>
	/// <returns>pozitia unde l-a gasit sau -1</returns>
	int find_denumire_prof(const std::string den, const std::string prof) const;
	int find_denumire(const std::string den) const;

	/// <summary>
	/// Filtreaza vectorul si returneaza un vectoru nou cu discipline cu acelasi numar de ore ca si cel dat
	/// </summary>
	/// <param name="ore"></param>
	/// <returns></returns>
	std::vector<Disciplina> FilterByNrOre(int ore) const;

	/// <summary>
	/// Filtreaza vectorul si returneaza un vectoru nou cu discipline cu acelasi profesor ca si cel dat
	/// </summary>
	/// <param name="prof"></param>
	/// <returns></returns>
	std::vector<Disciplina> FilterByProf(const std::string prof) const;

	/// <summary>
	/// Creaza un vector ordonat de la a-z dupa denumire
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortAscendingByDenumire() const noexcept;

	/// <summary>
	/// Creaza un vector ordonat crescator dupa numarul de ore
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortAscendingByNrOre() const noexcept;

	/// <summary>
	/// Creaza un vector ordonat de la a-z dupa profesor si dupa tip
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortAscendingByProfAndType() const noexcept;

	/// <summary>
	/// Creaza un vecotr ordonat de la z-a dupa denumire
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortDescendingByDenumire() const noexcept;

	/// <summary>
	/// Creaza un vector ordonat descrescator in functie de numarul de ore
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortDescendingByNrOre() const noexcept;

	/// <summary>
	/// Creaza un vector ordonat de la a-z dupa profeosr si dupa tip
	/// </summary>
	/// <returns></returns>
	std::vector<Disciplina> SortDescendingByProfAndType() const noexcept;
	/// <summary>
	/// Adauga in contract disiplina cu numele den si profesorul prof
	/// </summary>
	/// <param name="den"></param>
	/// <param name="prof"></param>
	/// <returns></returns>
	void AddContract(const std::string den, const std::string prof);
	/// <summary>
	/// Functie de populat aleatoriu contractul
	/// </summary>
	/// <param name="list"></param>
	/// <returns></returns>
	void Random(std::vector<Disciplina> list, const size_t n);
	/// <summary>
	/// Functia de returnat contractul
	/// </summary>
	/// <returns></returns>
	const std::vector<Disciplina>& GetAllContract() noexcept;
	/// <summary>
	/// Functia care sterge contractul
	/// </summary>
	/// <returns></returns>
	void DeleteContract() noexcept;
	// Functie de exportat in CVS
	void ExportCSV(const std::string outCSV);

	const Disciplina find2(const std::string den, const std::string prof) const;
	/// <summary>
	/// Realizeaza un raport in functie de tip 
	/// </summary>
	/// <returns></returns>
	std::map<std::string, DTO> raport_tip();

	// Functie Undo
	void Undo();

	void Redo();

	void ImportFile();

	void ExportFile();
};

