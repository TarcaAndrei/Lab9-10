//
// Created by Andrei on 19.04.2023.
//

#include <algorithm>
#include "RepositoryContracte.h"
#include "../exceptions/erori_app.h"

void RepositoryContracte::creeaza_contract(int an_primit) {
    if(find_if(this->listaContracte.begin(), this->listaContracte.end(),[an_primit](ContractStudiu contractStudiu){
        return contractStudiu.get_an() == an_primit;}) != this->listaContracte.end()){
        throw contract_error("Acest an are deja un contract!");
    }
    auto contract_nou = ContractStudiu(an_primit);
    this->listaContracte.push_back(contract_nou);
}

void RepositoryContracte::adauga_disciplina_contract(int an_contract, const Disciplina& disciplina_noua) {
    auto ceva = find_if(this->listaContracte.begin(), this->listaContracte.end(),[an_contract](ContractStudiu contractStudiu)
    {return contractStudiu.get_an() == an_contract;});
    if(ceva == this->listaContracte.end()){
        throw contract_error("Nu exista niciun contract pentru acest an!");
    }
    ceva->adauga_disciplina_contract(disciplina_noua);
}

void RepositoryContracte::goleste_contract(int an_contract) {
    auto ceva = find_if(this->listaContracte.begin(), this->listaContracte.end(),[an_contract](ContractStudiu contractStudiu){return contractStudiu.get_an() == an_contract;});
    if(ceva == this->listaContracte.end()){
        throw contract_error("Nu exista niciun contract pentru acest an!");
    }
    ceva->delete_all();
}

std::vector<ContractStudiu>::iterator RepositoryContracte::get_contracte_begin() {
    return this->listaContracte.begin();
}

std::vector<ContractStudiu>::iterator RepositoryContracte::get_contracte_end() {
    return this->listaContracte.end();
}

int RepositoryContracte::get_numar_contracte() {
    return (int)this->listaContracte.size();
}

RepositoryContracte::RepositoryContracte() {
    this->numar_contracte = 0;
}

void RepositoryContracte::export_contract(int an_contract, const std::string& filename) {
    auto ceva = find_if(this->listaContracte.begin(), this->listaContracte.end(),[an_contract](ContractStudiu contractStudiu){return contractStudiu.get_an() == an_contract;});
    if(ceva == this->listaContracte.end()){
        throw contract_error("Nu exista niciun contract pentru acest an!");
    }
    if(filename.empty())
        throw contract_error("Filenameul nu poate fi vid!");
    ceva->genereaza_contract(filename);
}
