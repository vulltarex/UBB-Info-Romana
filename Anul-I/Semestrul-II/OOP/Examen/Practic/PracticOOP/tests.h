#pragma once
#include "student.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <fstream>

void testDomain() {
    Student s(1,"stud",20,"mate");
    assert(s.getNrMatricol() == 1);
    assert(s.getNume() == "stud");
    assert(s.getVarsta() == 20);
    assert(s.getFacultate() == "mate");
    s.setVarsta(30);
    assert(s.getVarsta() == 30);
}

void testRepo() {
    std::ofstream fout("test.txt");
    fout << "1,St1,10,mate\n";
    fout << "2,St2,20,mate-info\n";
    fout << "3,St3,30,info\n";
    fout.close();
    Repo repo("test.txt");
    assert(repo.getAll().size() == 3);
    assert(repo.getAll().at(0).getNrMatricol() == 1);
    assert(repo.getAll().at(1).getNrMatricol() == 2);
    assert(repo.getAll().at(2).getNrMatricol() == 3);
    repo.repoDelete(1);
    assert(repo.getAll().size() == 2);
    assert(repo.getAll().at(0).getNrMatricol() == 2);
    assert(repo.getAll().at(0).getVarsta() == 20);
    repo.repoUpdate(2, 50);
    assert(repo.getAll().at(0).getVarsta() == 50);
}

void testService() {
    std::ofstream fout("test.txt");
    fout << "1,St1,10,mate\n";
    fout << "2,St2,20,mate-info\n";
    fout << "3,St3,30,info\n";
    fout.close();
    Repo repo("test.txt");
    Service srv(repo);
    assert(srv.srvGetAll().at(0).getVarsta() == 10);
    assert(srv.srvGetAll().at(1).getVarsta() == 20);
    assert(srv.srvGetAll().at(2).getVarsta() == 30);
    srv.srvDelete(1);
    assert(srv.srvGetAll().at(0).getNrMatricol() == 2);
    srv.srvInc();
    assert(srv.srvGetAll().at(0).getVarsta() == 21);
    assert(srv.srvGetAll().at(1).getVarsta() == 31);
    srv.srvDec();
    assert(srv.srvGetAll().at(0).getVarsta() == 20);
    assert(srv.srvGetAll().at(1).getVarsta() == 30);
}

void testAll() {
    testDomain();
    testRepo();
    testService();
}