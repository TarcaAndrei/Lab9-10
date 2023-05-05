//
// Created by Andrei on 18.04.2023.
//

#include "ContractStudiu.h"
#include <fstream>
#include "../exceptions/erori_app.h"

ContractStudiu::ContractStudiu(int an_primit) {
    this->dimensiune = 0;
    this->an = an_primit;
}

void ContractStudiu::delete_all() {
    this->dimensiune = 0;
    this->lista.clear();
}

void ContractStudiu::adauga_disciplina_contract(const Disciplina &disciplina_noua) {
    for(const auto& disc : this->lista){
        if(disc.get_id() == disciplina_noua.get_id()) {
            throw contract_error("Disciplina existenta!");
        }
    }
    this->dimensiune++;
    this->lista.push_back(disciplina_noua);
}

int ContractStudiu::get_an() {
    return this->an;
}

int ContractStudiu::get_numar_discipline() {
    return this->dimensiune;
}

void ContractStudiu::genereaza_contract(const string &filename) {
    std::string file_path = "../contracte_export/";
    file_path += filename;
    file_path += ".csv";
    ofstream fout(file_path);
    for(auto item : this->lista){
        fout<<item.get_id()<<','<<item.get_denumire()<<','<<item.get_cadru_didactic()<<',';
        fout<<item.get_tip()<<','<<item.get_ore_pe_saptamana()<<'\n';
    }
    fout.close();
}

std::vector<Disciplina>::iterator ContractStudiu::get_begin_disc() {
    return this->lista.begin();
}

std::vector<Disciplina>::iterator ContractStudiu::get_end_disc() {
    return this->lista.end();
}

