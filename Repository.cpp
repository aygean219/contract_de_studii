#include "Repository.h"

const Disciplina Repository::find(const std::string den, const std::string prof) const
{
    auto it = find_if(discipline.begin(), discipline.end(), [den, prof](Disciplina d) {return d.getDenumire() == den && d.getCadruDidactic() == prof; });
    if (it != discipline.end())
    {
        return *it;
    }
    throw DisciplinaRepoException("There is no discipline called: " + den + " with teacher: " + prof);
}
const int Repository::findPoz(const std::string den, const std::string prof) const
{
    int poz = 0;
    for (const auto& d : discipline)
    {
        poz++;
        if (d.getDenumire() == den && d.getCadruDidactic() == prof)
        {
            return poz;
        }
    }
    throw DisciplinaRepoException("There is no discipline called: " + den + " with teacher: " + prof);
}
bool Repository::exist(const Disciplina& d) const
{
    try {
        find(d.getDenumire(), d.getCadruDidactic());
        return true;
    }
    catch (DisciplinaRepoException&) {
        return false;
    }
}

void Repository::add(const Disciplina& d)
{
    if (exist(d))
    {
        throw DisciplinaRepoException("There is already a discipline called: " + d.getDenumire() + " with teacher: " + d.getCadruDidactic());
    }
    discipline.push_back(d);
}

void Repository::del(const Disciplina& d)
{
    try {
        const int poz = findPoz(d.getDenumire(), d.getCadruDidactic());
        discipline.erase(discipline.begin() + (poz - 1));
    }
    catch (const DisciplinaRepoException& ex)
    {
        throw DisciplinaRepoException(ex);
    }
}

void Repository::upd(const Disciplina& d_vechi, const Disciplina& d_nou)
{
    try {
        const int poz = findPoz(d_vechi.getDenumire(), d_vechi.getCadruDidactic());
        discipline.at(poz - 1).setCadruDidactic(d_nou.getCadruDidactic());
        discipline.at(poz - 1).setDenumire(d_nou.getDenumire());
        discipline.at(poz - 1).setTip(d_nou.getTip());
        discipline.at(poz - 1).setNrOre(d_nou.getNrOre());
    }
    catch (const DisciplinaRepoException& ex)
    {
        throw DisciplinaRepoException(ex);
    }
}

const std::vector<Disciplina>& Repository::getAll()
{
    return discipline;
}

const int Repository::sizeRepo()const  noexcept
{
    return discipline.size();
}
std::ostream& operator<<(std::ostream& out, const DisciplinaRepoException& ex) {
    out << ex.msg;
    return out;
}