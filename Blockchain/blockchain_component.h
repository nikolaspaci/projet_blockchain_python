#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include "../Bloc.h"
#include <vector>
#include <pybind11/pybind11.h>
#include <nlohmann/json.hpp>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
namespace py = pybind11;

class Blockchain
{
private:
    std::vector<Bloc> listeBloc;
    bool verifyPreviousBlock(Bloc,Bloc)
    void from_json(nlohmann::json&);
    /*
    Bloc bloc_from_json(nlohmann::json&);
    TXM txm_from_json(nlohmann::json&);
    TX tx_from_json(nlohmann::json&);
    UTXO utxo_from_json(nlohmann::json&);
    TXI txi_from_json(nlohmann::json&);
    py::object bloc_to_json(Bloc);
    py::object txm_to_json(TXM);
    py::object tx_to_json(TX);
    py::object utxo_to_json(UTXO);
    py::object txi_to_json(TXI);
     */
public:
    Blockchain(nlohmann::json&);
    ~Blockchain();
    int getNbBloc();
    void addBloc(Bloc&);
    Bloc getBloc(int);
    py::object to_json() const;
};
#endif //BLOCKCHAIN_BLOCKCHAIN_H

