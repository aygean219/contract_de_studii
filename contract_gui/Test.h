#pragma once
#include <assert.h>
#include "Disciplina.h"
#include  "DTO.h"
class Test
{
private:
	void testDisciplina();
	void testRepo();
	void testRepoFile1();
	void testRepoFile2();
	void testService();
	void testServiceFilters();
	void testServiceSorts();
	void testContract();
	void testDTO();
	void testRaport();
	void testUndoRedo();
	void testRepoLab();
public:
	void testAll();
};
