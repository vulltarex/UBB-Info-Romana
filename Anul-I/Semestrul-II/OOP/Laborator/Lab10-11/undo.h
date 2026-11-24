#pragma once
#include "activitate.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Activitate activitate_adaugata;
	RepoAbstract& repo;
public:
	UndoAdauga(RepoAbstract& repo, const Activitate& a) : repo{ repo }, activitate_adaugata{ a } {}
	void doUndo() override {
		repo.repo_delete(activitate_adaugata.get_titlu(), activitate_adaugata.get_tip());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Activitate activitate_stearsa;
	RepoAbstract& repo;
public:
	UndoSterge(RepoAbstract& repo, const Activitate& a) : repo{ repo }, activitate_stearsa{ a } {}
	void doUndo() override {
		repo.repo_add(activitate_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	Activitate activitate_veche;
	RepoAbstract& repo;
public:
	UndoModifica(RepoAbstract& repo, const Activitate& a) : repo{ repo }, activitate_veche{ a } {}
	void doUndo() override {
		repo.repo_update(activitate_veche);
	}
};