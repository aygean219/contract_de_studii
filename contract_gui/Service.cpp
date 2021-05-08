#include "Service.h"
#include <algorithm>

std::vector<Disciplina> Service::Sort(functie f) const
{
	std::vector<Disciplina> rez{ repo.getAll() };
	if (*f != nullptr)
		std::sort(rez.begin(), rez.end(), f);
	return rez;
}

std::vector<Disciplina> Service::filter(std::function<bool(const Disciplina&)> f) const
{
	std::vector<Disciplina> rez;
	std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rez), f);
	return rez;
}

void Service::addDisciplina(const Disciplina& d)
{
	val.ValidateDisciplina(d);
	repo.add(d);
	undo.push_back(std::make_unique<UndoAdd>(repo, d));
	redo.clear();
}

const std::vector<Disciplina>& Service::getAll()
{
	return repo.getAll();
}

void Service::deleteDisciplina(const Disciplina& d)
{
	;
	undo.push_back(std::make_unique<UndoDelete>(repo, d));
	redo.clear();
	repo.del(d);
}

void Service::updateDisciplina(const Disciplina& d_vechi, const Disciplina& d_nou)
{
	val.ValidateDisciplina(d_nou);
	undo.push_back(std::make_unique<UndoUpdate>(repo, d_vechi, d_nou));
	redo.clear();
	repo.upd(d_vechi, d_nou);
}

int Service::sizeService()
{
	return repo.sizeRepo();
}

int Service::find_denumire_prof(const std::string den, const std::string prof) const
{
	int i = 0;
	for (auto& el : repo.getAll())
	{
		if ((el.getCadruDidactic() == prof) && (el.getDenumire() == den))
		{
			return i;
		}
		i++;
	}
	return -1;
}
int Service::find_denumire(const std::string den) const
{
	int i = 0;
	for (auto& el : repo.getAll())
	{
		if (el.getDenumire() == den)
		{
			return i;
		}
		i++;
	}
	return -1;
}
std::vector<Disciplina> Service::FilterByNrOre(int ore) const
{
	return filter([ore](const Disciplina& d)noexcept {
		return d.getNrOre() == ore;
	});
}

std::vector<Disciplina> Service::FilterByProf(const std::string prof) const
{
	return filter([prof](const Disciplina& d)noexcept {
		return d.getCadruDidactic().compare(prof) == 0;
	});
}

std::vector<Disciplina> Service::SortAscendingByDenumire() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		return d1.getDenumire() < d2.getDenumire();
	});
}

std::vector<Disciplina> Service::SortAscendingByNrOre() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		return d1.getNrOre() < d2.getNrOre();
	});
}
std::vector<Disciplina> Service::SortAscendingByProfAndType() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		if (d1.getCadruDidactic() == d2.getCadruDidactic())
			return d1.getTip() < d2.getTip();
		return d1.getCadruDidactic() < d2.getCadruDidactic();
	});
}

std::vector<Disciplina> Service::SortDescendingByDenumire() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		return d1.getDenumire() > d2.getDenumire();
	});
}

std::vector<Disciplina> Service::SortDescendingByNrOre() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		return d1.getNrOre() > d2.getNrOre();
	});
}

std::vector<Disciplina> Service::SortDescendingByProfAndType() const noexcept
{
	return Sort([](const Disciplina& d1, const Disciplina& d2)
	{
		if (d1.getCadruDidactic() == d2.getCadruDidactic())
			return d1.getTip() > d2.getTip();
		return d1.getCadruDidactic() > d2.getCadruDidactic();
	});
}

void Service::AddContract(const std::string den, const std::string prof)
{

	const int i = find_denumire_prof(den, prof);
	contract.AddDisciplina(repo.getAll().at(i));

}

void Service::Random(std::vector<Disciplina> list, const size_t n)
{
	std::shuffle(list.begin(), list.end(), std::default_random_engine(std::random_device{}()));
	while ((GetAllContract().size() < n) && (list.size() > 0))
	{
		contract.AddDisciplina(list.back());
		list.pop_back();
	}

}

const std::vector<Disciplina>& Service::GetAllContract() noexcept
{
	return contract.GetAll();
}

void Service::DeleteContract() noexcept
{
	contract.DeleteContract();

}

void Service::ExportCSV(const std::string outCSV)
{
	val.validateFile(outCSV);
	std::ofstream out(outCSV);
	for (auto& el : GetAllContract())
	{
		out << el.getDenumire() << "," << el.getCadruDidactic() << "," << el.getNrOre() << "," << el.getTip() << "\n";
	}
	out.close();
}

const Disciplina Service::find2(const std::string den, const std::string prof) const
{
	auto it = find_if(repo.getAll().begin(), repo.getAll().end(), [den, prof](Disciplina d) {return d.getDenumire() == den && d.getCadruDidactic() == prof; });
	if (it != repo.getAll().end())
	{
		return *it;
	}
	throw ServiceException("Nu exista !!");
}

std::map<std::string, DTO> Service::raport_tip()
{
	std::map<std::string, DTO> raport;
	const std::vector<Disciplina> lista_discipline = getAll();
	for (const Disciplina& disciplina : lista_discipline)
	{
		if (raport.find(disciplina.getTip()) != raport.end())
		{
			raport[disciplina.getTip()].add();
		}
		else
		{
			raport[disciplina.getTip()] = DTO(disciplina.getTip());
		}
	}
	return raport;
}

void Service::Undo()
{
	if (undo.empty())
	{
		std::vector<std::string> messages;
		messages.push_back("Nu mai exista operatii");
		throw ValidateException(messages);
	}
	undo.back()->DoUndo();
	redo.push_back(std::move(undo.back()));
	undo.pop_back();
}

void Service::Redo()
{
	if (redo.size() == 0) return;
	redo.back()->DoRedo();
	undo.push_back(std::move(redo.back()));
	redo.pop_back();
}

void Service::ImportFile()
{
	std::ifstream in("contract.txt");
	int i = 0;
	while (repo.sizeRepo() != 0)
	{
		repo.del(repo.getAll()[0]);
	}
	char line[256]{ '\0' }, * next_token = NULL;
	while (in.getline(line, 256)) {
		char* pcs = strtok_s(line, ",", &next_token);
		std::string denumire = pcs;
		pcs = strtok_s(NULL, ",", &next_token);
		const int nrOre = atoi(pcs);
		pcs = strtok_s(NULL, ",", &next_token);
		std::string cadruDidactic = pcs;
		pcs = strtok_s(NULL, "\n", &next_token);
		std::string tip = pcs;
		repo.add(Disciplina(denumire, nrOre, cadruDidactic, tip));
	}
}

void Service::ExportFile()
{
	remove("contract.txt");
	std::ofstream out("contract.txt");
	for (auto& el : repo.getAll())
	{
		out << el.getDenumire() << "," << el.getNrOre() << "," << el.getCadruDidactic() << "," << el.getTip() << "\n";

	}
}
