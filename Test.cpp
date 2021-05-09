#include "Repository.h"
#include "RepositoryFile.h"
#include "Test.h"
#include "RepoLab.h"
#include "Validator.h"
#include "Service.h"
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <assert.h>

void Test::testDisciplina()
{	//constructor fara parametrii//
	Disciplina d;
	assert(d.getNrOre() == 0);
	assert(d.getCadruDidactic() == "");
	assert(d.getTip() == "");
	assert(d.getDenumire() == "");
	//constructor cu parametrii//
	Disciplina d1("OOP", 5, "AnaMaria", "Obligatoriu");
	assert(d1.getNrOre() == 5);
	assert(d1.getCadruDidactic() == "AnaMaria");
	assert(d1.getTip() == "Obligatoriu");
	assert(d1.getDenumire() == "OOP");
	//constructor de copiere//
	Disciplina d2 = d1;
	assert(d2.getNrOre() == 5);
	assert(d2.getCadruDidactic() == "AnaMaria");
	assert(d2.getTip() == "Obligatoriu");
	assert(d2.getDenumire() == "OOP");
	assert(d2 == d1);
	//setter
	d.setCadruDidactic("AnaMaria");
	d.setDenumire("OOP");
	d.setNrOre(5);
	d.setTip("Obligatoriu");
	assert(d.getNrOre() == 5);
	assert(d.getCadruDidactic() == "AnaMaria");
	assert(d.getTip() == "Obligatoriu");
	assert(d.getDenumire() == "OOP");
	d = d1;
	assert(d == d1);
}
void Test::testRepo()
{
	Repository r;
	assert(r.sizeRepo() == 0);
	r.add(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"));
	assert(r.sizeRepo() == 1);
	r.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	r.add(Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	assert(r.sizeRepo() == 3);
	r.del(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	assert(r.sizeRepo() == 2);
	r.upd(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"), Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	assert(r.getAll().at(0).getDenumire() == "StructuriDeDate");
	std::vector<Disciplina> rez = r.getAll();
	assert(rez.at(0) == Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	try {
		r.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		r.del(Disciplina("aa", 5, "bb", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		r.upd(Disciplina("aa", 5, "bb", "Obligatoriu"), Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
}
void Test::testRepoFile1()
{
	try {
		RepositoryFile r("testCSV.csv");
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	std::ofstream out("testCSV.csv", std::ios::trunc);
	RepositoryFile r("testCSV.csv");
	assert(r.sizeRepo() == 0);
	r.add(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"));
	assert(r.sizeRepo() == 1);
	r.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	r.add(Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	assert(r.sizeRepo() == 3);
	r.del(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	assert(r.sizeRepo() == 2);
	r.upd(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"), Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	assert(r.getAll().at(0).getDenumire() == "StructuriDeDate");
	std::vector<Disciplina> rez = r.getAll();
	assert(rez.at(0) == Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	try {
		r.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		r.del(Disciplina("aa", 5, "bb", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		r.upd(Disciplina("aa", 5, "bb", "Obligatoriu"), Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
}
void Test::testRepoFile2()
{
	RepositoryFile r("testCSV2.csv");
	assert(r.sizeRepo() == 1);
	r.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	assert(r.sizeRepo() == 2);
	r.del(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	try {
		RepositoryFile r1("aa.csv");
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	/*try {
		std::ofstream f("bb.csv");
		RepositoryFile r2("bb.csv");
		remove("bb.csv");
		r2.add(Disciplina("StructuriDeDate", 5, "DianaLucia", "Obligatoriu"));
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	*/
}

void Test::testService()
{
	Repository r;
	Service s(r);
	assert(s.sizeService() == 0);
	Disciplina d0("", 5, "", "");
	try {
		s.addDisciplina(d0);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	Disciplina d("OOP", 5, "AnaMaria", "Obligatoriu");
	try {
		s.addDisciplina(d);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	Disciplina d1("StructuriDeDate", 5, "DianaLucia", "Obligatoriu");
	try {
		s.addDisciplina(d1);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	Disciplina d2("Scufundari", 3, "SteaDeMare", "Optional");
	try {
		s.addDisciplina(d2);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	assert(s.sizeService() == 3);
	try {
		s.addDisciplina(d2);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		s.deleteDisciplina(Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	assert(s.sizeService() == 2);
	//s-a sters deja
	try {
		s.deleteDisciplina(Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	//nu exista
	assert(s.sizeService() == 2);
	try {
		s.updateDisciplina(Disciplina("Scufundari", 3, "SteaDeMare", "Optional"), Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		s.updateDisciplina(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"), Disciplina("Scufundari", 3, "SteaDeMare", "Optional"));
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	assert(s.getAll().at(0).getCadruDidactic() == "SteaDeMare");
	//////////////////Gaseste diciplina dupa nume si prof//////////////////
	int ok = s.find_denumire_prof("Scufundari", "SteaDeMare");
	assert(ok != -1);
	ok = s.find_denumire_prof("aa", "bb");
	assert(ok == -1);
	/////////////////FIND2//////////////
	Disciplina dd = s.find2("Scufundari", "SteaDeMare");
	assert(dd.getNrOre() == 3);
	try {
		Disciplina dd2 = s.find2("aa", "bb");
	}
	catch (ServiceException&)
	{
		assert(true);
	}
}
void Test::testServiceFilters()
{
	Repository r;
	Service serv(r);
	Disciplina d1("OOP", 4, "Ana Maria", "obligatoriu");
	Disciplina d2("Sisteme de operare", 6, "Boian Rares", "obligatoriu");
	Disciplina d3("Engleza", 4, "Teacher", "facultativ");
	Disciplina d4("Sisteme dinamice", 4, "Moga Madalina", "obligatoriu");
	Disciplina d5("OOP", 6, "Istvan", "obligatoriu");
	Disciplina d6("Sisteme dinamice", 4, "Bota Monica", "obligatoriu");
	Disciplina d7("Sisteme de operare", 4, "Florian Mircea", "obligatoriu");
	Disciplina d8("Structuri de date", 4, "Istvan", "obligatoriu");
	serv.addDisciplina(d1);
	serv.addDisciplina(d2);
	serv.addDisciplina(d3);
	serv.addDisciplina(d4);
	serv.addDisciplina(d5);
	serv.addDisciplina(d6);
	serv.addDisciplina(d7);
	serv.addDisciplina(d8);
	assert(serv.sizeService() == 8);
	////////////////////Profesor/////////////////////////
	std::vector<Disciplina> filter1 = serv.FilterByProf("Istvan");
	assert(filter1.at(0).getDenumire() == "OOP");
	assert(filter1.at(1).getDenumire() == "Structuri de date");
	//////////////////Ore///////////////////////
	std::vector<Disciplina> filter2 = serv.FilterByNrOre(6);
	assert(filter2.at(0).getDenumire() == "Sisteme de operare");
	assert(filter2.at(1).getDenumire() == "OOP");
}
void Test::testServiceSorts()
{
	Repository r;
	Service serv(r);
	Disciplina d1("OOP", 4, "Ana Maria", "obligatoriu");
	Disciplina d2("Sisteme de operare", 6, "Boian Rares", "obligatoriu");
	Disciplina d3("Engleza", 4, "Teacher", "facultativ");
	Disciplina d4("Sisteme dinamice", 4, "Moga Madalina", "obligatoriu");
	Disciplina d5("OOP", 6, "Istvan", "obligatoriu");
	Disciplina d6("Sisteme dinamice", 4, "Bota Monica", "obligatoriu");
	Disciplina d7("Sisteme de operare", 4, "Florian Mircea", "obligatoriu");
	Disciplina d8("Structuri de date", 4, "Istvan", "facultativ");
	serv.addDisciplina(d1);
	serv.addDisciplina(d2);
	serv.addDisciplina(d3);
	serv.addDisciplina(d4);
	serv.addDisciplina(d5);
	serv.addDisciplina(d6);
	serv.addDisciplina(d7);
	serv.addDisciplina(d8);
	assert(serv.sizeService() == 8);
	//////////////Sort Crescator By Denumire////////
	std::vector<Disciplina> vect1 = serv.SortAscendingByDenumire();
	assert(vect1.at(0).getDenumire() == "Engleza");
	assert(vect1.at(1).getDenumire() == "OOP");
	assert(vect1.at(2).getDenumire() == "OOP");
	assert(vect1.at(3).getDenumire() == "Sisteme de operare");
	assert(vect1.at(4).getDenumire() == "Sisteme de operare");
	assert(vect1.at(5).getDenumire() == "Sisteme dinamice");
	assert(vect1.at(6).getDenumire() == "Sisteme dinamice");
	assert(vect1.at(7).getDenumire() == "Structuri de date");

	//////////////Sort Descrescator By Denumire////////
	std::vector<Disciplina> vect2 = serv.SortDescendingByDenumire();
	assert(vect2.at(7).getDenumire() == "Engleza");
	assert(vect2.at(6).getDenumire() == "OOP");
	assert(vect2.at(5).getDenumire() == "OOP");
	assert(vect2.at(4).getDenumire() == "Sisteme de operare");
	assert(vect2.at(3).getDenumire() == "Sisteme de operare");
	assert(vect2.at(2).getDenumire() == "Sisteme dinamice");
	assert(vect2.at(1).getDenumire() == "Sisteme dinamice");
	assert(vect2.at(0).getDenumire() == "Structuri de date");

	//////////////Sort Crescator By NrOre////////
	std::vector<Disciplina> vect3 = serv.SortAscendingByNrOre();
	assert(vect3.at(0).getDenumire() == "OOP");
	assert(vect3.at(1).getDenumire() == "Engleza");
	assert(vect3.at(2).getDenumire() == "Sisteme dinamice");
	assert(vect3.at(3).getDenumire() == "Sisteme dinamice");
	assert(vect3.at(4).getDenumire() == "Sisteme de operare");
	assert(vect3.at(5).getDenumire() == "Structuri de date");
	assert(vect3.at(6).getDenumire() == "Sisteme de operare");
	assert(vect3.at(7).getDenumire() == "OOP");

	//////////////Sort Descrescator By NrOre////////
	std::vector<Disciplina> vect4 = serv.SortDescendingByNrOre();
	assert(vect4.at(7).getDenumire() == "Structuri de date");
	assert(vect4.at(6).getDenumire() == "Sisteme de operare");
	assert(vect4.at(5).getDenumire() == "Sisteme dinamice");
	assert(vect4.at(4).getDenumire() == "Sisteme dinamice");
	assert(vect4.at(3).getDenumire() == "Engleza");
	assert(vect4.at(2).getDenumire() == "OOP");
	assert(vect4.at(1).getDenumire() == "OOP");
	assert(vect4.at(0).getDenumire() == "Sisteme de operare");

	//////////////Sort Crescator By CadruDidactic&&Tip////////
	std::vector<Disciplina> vect5 = serv.SortAscendingByProfAndType();
	assert(vect5.at(0).getCadruDidactic() == "Ana Maria");
	assert(vect5.at(1).getCadruDidactic() == "Boian Rares");
	assert(vect5.at(2).getCadruDidactic() == "Bota Monica");
	assert(vect5.at(3).getCadruDidactic() == "Florian Mircea");
	assert((vect5.at(4).getCadruDidactic() == "Istvan") && (vect5.at(4).getNrOre() == 4));
	assert((vect5.at(5).getCadruDidactic() == "Istvan") && (vect5.at(5).getNrOre() == 6));
	assert(vect5.at(6).getCadruDidactic() == "Moga Madalina");
	assert(vect5.at(7).getCadruDidactic() == "Teacher");

	//////////////Sort Descrescator By CadruDidactic&&Tip////////
	std::vector<Disciplina> vect6 = serv.SortDescendingByProfAndType();
	assert(vect6.at(7).getCadruDidactic() == "Ana Maria");
	assert(vect6.at(6).getCadruDidactic() == "Boian Rares");
	assert(vect6.at(5).getCadruDidactic() == "Bota Monica");
	assert(vect6.at(4).getCadruDidactic() == "Florian Mircea");
	assert((vect6.at(3).getCadruDidactic() == "Istvan") && (vect6.at(3).getNrOre() == 4));
	assert((vect6.at(2).getCadruDidactic() == "Istvan") && (vect6.at(2).getNrOre() == 6));
	assert(vect6.at(1).getCadruDidactic() == "Moga Madalina");
	assert(vect6.at(0).getCadruDidactic() == "Teacher");

}
void Test::testContract()
{
	Repository r;
	Contract c;
	Service serv(r);
	Disciplina d1("OOP", 4, "Ana Maria", "obligatoriu");
	Disciplina d2("Sisteme de operare", 6, "Boian Rares", "obligatoriu");
	Disciplina d3("Engleza", 4, "Teacher", "facultativ");
	Disciplina d4("Sisteme dinamice", 4, "Moga Madalina", "obligatoriu");
	Disciplina d5("OOP", 6, "Istvan", "obligatoriu");
	Disciplina d6("Sisteme dinamice", 4, "Bota Monica", "obligatoriu");
	Disciplina d7("Sisteme de operare", 4, "Florian Mircea", "obligatoriu");
	Disciplina d8("Structuri de date", 4, "Istvan", "facultativ");
	serv.addDisciplina(d1);
	serv.addDisciplina(d2);
	serv.addDisciplina(d3);
	serv.addDisciplina(d4);
	serv.addDisciplina(d5);
	serv.addDisciplina(d6);
	serv.addDisciplina(d7);
	serv.addDisciplina(d8);
	assert(serv.sizeService() == 8);
	serv.AddContract("OOP", "Ana Maria");
	serv.AddContract("Engleza", "Teacher");
	serv.AddContract("Sisteme dinamice", "Bota Monica");
	assert(serv.GetAllContract().size() == 3);
	serv.DeleteContract();
	assert(serv.GetAllContract().size() == 0);
	serv.Random(serv.getAll(), 4);
	assert(serv.GetAllContract().size() == 4);
	serv.ExportCSV("abc.csv");
	try {
		serv.ExportCSV("aaa");
	}
	catch (ValidateException&)
	{
		assert(true);
	}
	serv.DeleteContract();
	assert(serv.GetAllContract().size() == 0);
}
void Test::testDTO()
{
	DTO d;
	assert(d.getNrAparitii() == 1);
	DTO d1("aaaa");
	assert(d1.getNrAparitii() == 1 && d1.getTip() == "aaaa");
	d1.setNrAparitii(3);
	d1.setTip("bbbb");
	d1.add();
	assert(d1.getNrAparitii() == 4 && d1.getTip() == "bbbb");
	DTO d2(d1);
	assert(d2.getNrAparitii() == 4 && d2.getTip() == "bbbb");
}
void Test::testRaport()
{
	Repository r;
	Service serv(r);
	Disciplina d1("OOP", 4, "Ana Maria", "obligatoriu");
	Disciplina d2("Sisteme de operare", 6, "Boian Rares", "obligatoriu");
	Disciplina d3("Engleza", 4, "Teacher", "facultativ");
	Disciplina d4("Sisteme dinamice", 4, "Moga Madalina", "obligatoriu");
	Disciplina d5("OOP", 6, "Istvan", "obligatoriu");
	Disciplina d6("Sisteme dinamice", 4, "Bota Monica", "obligatoriu");
	Disciplina d7("Sisteme de operare", 4, "Florian Mircea", "obligatoriu");
	Disciplina d8("Structuri de date", 4, "Istvan", "facultativ");
	serv.addDisciplina(d1);
	serv.addDisciplina(d2);
	serv.addDisciplina(d3);
	serv.addDisciplina(d4);
	serv.addDisciplina(d5);
	serv.addDisciplina(d6);
	serv.addDisciplina(d7);
	serv.addDisciplina(d8);
	assert(serv.sizeService() == 8);
	auto raport = serv.raport_tip();
	assert(raport.at("facultativ").getNrAparitii() == 2);
	assert(raport.at("obligatoriu").getNrAparitii() == 6);
}
void Test::testUndoRedo()
{
	Repository r;
	Service serv(r);
	Disciplina d1("OOP", 4, "Ana Maria", "obligatoriu");
	Disciplina d2("Sisteme de operare", 6, "Boian Rares", "obligatoriu");
	Disciplina d3("Engleza", 4, "Teacher", "facultativ");
	Disciplina d4("Sisteme dinamice", 4, "Moga Madalina", "obligatoriu");
	Disciplina d5("OOP", 6, "Istvan", "obligatoriu");
	Disciplina d6("Sisteme dinamice", 4, "Bota Monica", "obligatoriu");
	Disciplina d7("Sisteme de operare", 4, "Florian Mircea", "obligatoriu");
	Disciplina d8("Structuri de date", 4, "Istvan", "facultativ");
	serv.addDisciplina(d1);
	serv.addDisciplina(d2);
	serv.addDisciplina(d3);
	serv.addDisciplina(d4);
	serv.addDisciplina(d5);
	serv.addDisciplina(d6);
	serv.addDisciplina(d7);
	serv.addDisciplina(d8);
	assert(serv.sizeService() == 8);
	//ANULEZ ULTIMUL ADAUGAT
	serv.Undo();
	assert(serv.sizeService() == 7);
	//PUN INAPOI ULTIMUL ADAUGAT
	serv.Redo();
	assert(serv.sizeService() == 8);
	//STERG D2
	serv.deleteDisciplina(d2);
	assert(serv.sizeService() == 7);
	//ANULEZ STERGEREA
	serv.Undo();
	assert(serv.sizeService() == 8);
	//IL STERG INAPOI
	serv.Redo();
	assert(serv.sizeService() == 7);
	//DAU UPDATE LUI D3 CU D2
	serv.updateDisciplina(d3, d2);
	assert(serv.getAll().at(1).getTip() == d2.getTip());
	//DAU UNDO LA UPDATE
	serv.Undo();
	assert(serv.getAll().at(1).getTip() == d3.getTip());
	//DAU REDO LA UPDATE
	serv.Redo();
	assert(serv.getAll().at(1).getTip() == d2.getTip());
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	serv.Undo();
	try {
		serv.Undo();
	}
	catch (ValidateException&)
	{
		assert(true);
	}
}

void Test::testRepoLab()
{
	RepoLab r(0.4);
	int v = 0;
	while (!v)
	{
		try {
			r.add(Disciplina("OOP", 5, "AnaMaria", "Obligatoriu"));
			assert(r.getAll().size() == 1);
			v = 1;
		}
		catch (DisciplinaRepoException&)
		{
			v = 0;
		}
	}
	v = 0;
	while (!v)
	{
		try {
			r.add(Disciplina("Sisteme de operare", 6, "Boian Rares", "obligatoriu"));
			assert(r.getAll().size() == 2);
			v = 1;
		}
		catch (DisciplinaRepoException&)
		{
			v = 0;
		}
	}
	v = 0;
	while (!v)
	{
		try {
			r.add(Disciplina("Engleza", 4, "Teacher", "facultativ"));
			assert(r.getAll().size() == 3);
			v = 1;
		}
		catch (DisciplinaRepoException&)
		{
			v = 0;
		}
	}
	try {
		r.add(Disciplina("Engleza", 23, "Teacher", "facultativ"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	v = 0;
	while (!v)
	{
		try {
			r.del(Disciplina("Engleza", 4, "Teacher", "facultativ"));
			assert(r.getAll().size() == 2);
			v = 1;
		}
		catch (DisciplinaRepoException&)
		{
			v = 0;
		}
	}
	try {
		r.del(Disciplina("Engleza", 23, "Teacher", "facultativ"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	v = 0;
	while (!v)
	{
		try {
			r.upd(Disciplina("Sisteme de operare", 6, "Boian Rares", "obligatoriu"), Disciplina("Engleza", 4, "Teacher", "facultativ"));
			assert(r.sizeRepo() == 2);
			v = 1;
		}
		catch (DisciplinaRepoException&)
		{
			v = 0;
		}
	}
	try {
		r.upd(Disciplina("Sisteme de operare", 6, "Boian Rares", "obligatoriu"), Disciplina("Engleza", 4, "Teacher", "facultativ"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
	try {
		r.upd(Disciplina("aa", 6, "bb", "obligatoriu"), Disciplina("Engleza", 4, "Teacher", "facultativ"));
	}
	catch (DisciplinaRepoException&)
	{
		assert(true);
	}
}
void Test::testAll()
{
	testDisciplina();
	testRepo();
	testRepoFile1();
	testRepoFile2();
	testService();
	testServiceFilters();
	testServiceSorts();
	testContract();
	testDTO();
	testRaport();
	testUndoRedo();
	testRepoLab();
}
