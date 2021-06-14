#pragma once
#include "Disciplina.h"
#include "Repository.h"
#include "RepoAbstract.h"
class Undo
{
public:
	virtual void DoUndo() = 0;
	virtual void DoRedo() = 0;
	virtual ~Undo() = default;
};
class UndoAdd :public Undo {
	Disciplina d;
	Repo& repo;
public:
	UndoAdd(Repo& repo, const Disciplina& d) :repo{ repo }, d{ d }{}
	void DoUndo() override {
		repo.del(d);
	}
	void DoRedo() override {
		repo.add(d);
	}
};
class UndoDelete :public Undo {
	Disciplina d;
	Repo& repo;
public:
	UndoDelete(Repo& repo, const Disciplina& d) :repo{ repo }, d{ d }{}
	void DoUndo() override {
		repo.add(d);

	}
	void DoRedo() override {
		repo.del(d);
	}
};
class UndoUpdate :public Undo {
	Disciplina d_vechi;
	Disciplina d_nou;
	Repo& repo;
public:
	UndoUpdate(Repo& repo, const Disciplina& d_vechi, const Disciplina& d_nou) :repo{ repo }, d_vechi{ d_vechi }, d_nou{ d_nou }{}
	void DoUndo() override {
		repo.upd(d_nou, d_vechi);

	}
	void DoRedo() override {
		repo.upd(d_vechi, d_nou);
	}
};
