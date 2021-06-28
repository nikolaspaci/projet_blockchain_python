#include "blockchain_component.h"
#include <string>

Blockchain::Blockchain(nlohmann::json& json) {
    importFromJson(json);
}

Blockchain::~Blockchain() {

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

py::object Blockchain::to_json(){
    nlohmann::json jsonBlochain;

    nlohmann::json jsonListeBlocs;
    for(int i=0;i<this->listeBloc.size();++i){
        jsonListeBlocs.push_back(listeBloc.at(i).to_json());
    }
    jsonBlochain["blocs"]=jsonListeBlocs;

    return jsonBlochain;
}

void Blockchain::from_json(nlohmann::json json){
    nlohmann::json jsonListeBloc = j["blocs"];
    for (nlohmann::json::const_iterator it=jsonListeBloc.begin(); it !=jsonListeBloc.end(); ++it) {
        Bloc *bloc=new Bloc(*it);
        this->listeBloc.push_back(bloc);
    }
}

/*
py::object Blockchain::bloc_to_json(Bloc bloc){
    nlohmann::json jsonBloc;

    jsonBloc["nonce"]=bloc.nonce;
    jsonBloc["num"]=bloc.num;

    std::string hash="";
    for(int i=0;i<HASH_SIZE;++i){
        hash=hash+bloc.hash[i];
    }
    jsonBloc["hash"]=hash;

    std::string prevHash="";
    for(int i=0;i<HASH_SIZE;++i){
        prevHash=prevHash+bloc.previous_hash[i];
    }
    jsonBloc["previous_hash"]=prevHash;

    jsonBloc["tx0"]=txm_to_json(bloc.tx0);

    nlohmann::json jsonListeTx;
    for (std::listlist<TX*>::const_iterator it=bloc.txs.begin(); it != bloc.txs.end(); ++it) {
        jsonListeTx.push_back(tx_to_json((**it)));
    }
    jsonBloc["txs"]=jsonListeTx;

    return jsonBloc;
}

py::object Blockchain::txm_to_json(TXM txm){
    nlohmann::json jsonTxm;

    nlohmann::json jsonListeUtxo;
    unsigned  int tailleTabUtxo=(sizeof(txm.utxo)/sizeof(*txm.utxo));
    for(int i=0;i<tailleTabUtxo;++i){
        jsonListeUtxo.push_back(utxo_to_json(txm.utxo[i]));
    }
    jsonTxm["utxo"]=jsonListeUtxo;

    return jsonTxm;
}

py::object Blockchain::tx_to_json(TX tx){
    nlohmann::json jsonTx;

    nlohmann::json jsonListeTxi;
    for (std::listlist<TXI*>::const_iterator it=tx.TXIs.begin(); it != tx.TXIs.end(); ++it) {
        jsonListeTxi.push_back(txi_to_json((**it)));
    }
    jsonBloc["TXIs"]=jsonListeTxi;

    nlohmann::json jsonListeUtxo;
    for (std::listlist<UTXO*>::const_iterator it=tx.UTXOs.begin(); it != tx.UTXOs.end(); ++it) {
        jsonListeUtxo.push_back(utxo_to_json((**it)));
    }
    jsonBloc["UTXOs"]=jsonListeUtxo;

    return jsonTx;
}

py::object Blockchain::utxo_to_json(UTXO utxo){
    nlohmann::json jsonUtxo;

    jsonUtxo["nBloc"]=utxo.nBloc;
    jsonUtxo["nTx"]=utxo.nTx;
    jsonUtxo["nUTX0"]=utxo.nUTX0;
    jsonUtxo["montant"]=utxo.montant;

    std::string owner="";
    for(int i=0;i<PUBLIC_KEY_SIZE;++i){
        owner=owner+utxo.owner[i];
    }
    jsonUtxo["owner"]=owner;

    std::string hash="";
    for(int i=0;i<HASH_SIZE;++i){
        hash=hash+utxo.hash[i];
    }
    jsonUtxo["hash"]=hash;

    return jsonUtxo;
}

py::object Blockchain::txi_to_json(TXI txi){
    nlohmann::json jsonTxi;

    jsonTxi["nBloc"]=txi.nBloc;
    jsonTxi["nTx"]=txi.nTx;
    jsonTxi["nUtxo"]=txi.nUtxo;

    unsigned  int tailleTabSignature=(sizeof(txi.signature)/sizeof(*txi.signature));
    std::string signature="";
    for(int i=0;i<tailleTabSignature;++i){
        signature=signature+txi.signature[i];
    }
    jsonTxi["signature"]=signature;

    return jsonTxi;
}

void Blockchain::from_json(nlohmann::json json){
    nlohmann::json jsonListeBloc = j["blocs"];
    for (nlohmann::json::const_iterator it=jsonListeBloc.begin(); it !=jsonListeBloc.end(); ++it) {
        this->listeBloc.push_back(bloc_from_json((*it)));
    }
}

Bloc Blockchain::bloc_from_json(nlohmann::json& json){
    Bloc bloc;

}
*/