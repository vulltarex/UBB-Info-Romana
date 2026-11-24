#pragma once
#include "tractor.h"
#include <vector>

class RepoException {
private:
    std::string msg;
public:
    RepoException(const std::string& msg) : msg{msg} {}
    const std::string& getMsg() const { return msg; }
};

class Repo {
private:
    std::vector<Tractor> tractoare;
    std::string filename;
    void loadFromFile();
    void saveToFile();
public:
    Repo(const std::string& filename) : filename { filename } { loadFromFile(); }
    void repoAdd(Tractor& t);
    const std::vector<Tractor>& repoGetAll() const;
};