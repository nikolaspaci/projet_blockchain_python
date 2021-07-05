#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include "../bloc_component/Bloc.h"
#include <vector>
#include <pybind11/pybind11.h>
#include <nlohmann/json.hpp>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
namespace py = pybind11;

class Blockchain
{
public:
    std::vector<Bloc> listeBloc;
    bool verifyPreviousBlock(Bloc,Bloc);
    void from_json(const nlohmann::json& json);
    Blockchain(const nlohmann::json&);
    ~Blockchain();
    int getNbBloc();
    void addBloc(Bloc&);
    Bloc getBloc(int);
    py::object to_json() const;
    const char* getVersion();
};
#endif //BLOCKCHAIN_BLOCKCHAIN_H

