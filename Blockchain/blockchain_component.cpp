#include "blockchain_component.h"
#include <string>

char version[]="1.1.1";

Blockchain::Blockchain(const nlohmann::json& json) {
    from_json(json);
}

Blockchain::~Blockchain() {

}

const char* getVersion(){
    return version;
}

bool Blockchain::verifyPreviousBlock(Bloc b, Bloc bPrev){
    for(int i=0;i<HASH_SIZE;++i){
        if(bPrev.hash[i]!=b.previous_hash[i]){
            return false;
        }
    }
    return true;
}

int Blockchain::getNbBloc() {
    return this->listeBloc.size();
}

void Blockchain::addBloc(Bloc& bloc) {
    if(verifyPreviousBlock(bloc,this->listeBloc.back())){
        this->listeBloc.push_back(bloc);
    }
}

Bloc Blockchain::getBloc(int index) {
    return this->listeBloc.at(index);
}

py::object Blockchain::to_json() const{
    nlohmann::json jsonBlochain;

    nlohmann::json jsonListeBlocs;
    for(int i=0;i<this->listeBloc.size();++i){
        jsonListeBlocs.push_back(listeBloc.at(i).to_json());
    }
    jsonBlochain["blocs"]=jsonListeBlocs;

    return jsonBlochain;
}

void Blockchain::from_json(const nlohmann::json& json){
    nlohmann::json jsonListeBloc = json["blocs"];
    for (nlohmann::json::const_iterator it=jsonListeBloc.begin(); it !=jsonListeBloc.end(); ++it) {
        Bloc bloc(*it);
        this->listeBloc.push_back(bloc);
    }
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(blochain_component, m) {
m.doc()="blockchain object";
m.def("getVersion", &getVersion, "a function returning the version");

py::class_<Blockchain>(m, "Blockchain")
.def(py::init<const nlohmann::json &>())
.def("to_json", &Blockchain::to_json)
.def("from_json", &Blockchain::from_json)
.def("getBloc", &Blockchain::getBloc)
.def("addBloc", &Blockchain::addBloc)
.def("getNbBloc", &Blockchain::getNbBloc)
.def("verifyPreviousBlock", &Blockchain::verifyPreviousBlock);
}
