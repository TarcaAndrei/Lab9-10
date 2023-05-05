//
// Created by Andrei on 29.03.2023.
//


#include "RepositoryDiscipline.h"
#include "../exceptions/erori_app.h"
#include <iostream>
#include <utility>
RepositoryDiscipline::RepositoryDiscipline() {
    this->lungime = 0;
}

void RepositoryDiscipline::adauga_disciplina_repo(const Disciplina& disciplina_noua) {
    for(const auto& disc : this->lista){
        if(disc.get_id() == disciplina_noua.get_id()) {
            throw repository_error("Disciplina existenta!");
        }
    }
//    for(auto it = this->lista.begin(); it < this->lista.end(); it++){
//        if(disc.get_id() == disciplina_noua.get_id()) {
//            throw repository_error("Disciplina existenta!");
//        }
//    }

    this->lista.push_back(disciplina_noua);
    this->lungime++;
}

Disciplina RepositoryDiscipline::sterge_disciplina_repo(int id_disciplina) {
    bool gasit;
    gasit = false;
    int poz = -1;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        throw repository_error("Disciplina inexistenta!");
    auto disc = this->lista[poz];
    this->lista.erase(this->lista.begin() + poz);
    //this->lista.(poz);
    this->lungime--;
    return disc;
}

int RepositoryDiscipline::get_numar_elemente_repo() const {
    return this->lungime;
}

void RepositoryDiscipline::modifica_denumire_disciplina(int id_disciplina, string denumire_noua) {
    bool gasit;
    gasit = false;
    int poz = -1;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        throw repository_error("Disciplina inexistenta!");
//    auto disc = this->lista[poz];
    this->lista[poz].set_denumire(std::move(denumire_noua));
}

void RepositoryDiscipline::modifica_ore_disciplina(int id_disciplina, int ore_pe_saptamana_nou) {
    bool gasit;
    gasit = false;
    int poz = -1;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        throw repository_error("Disciplina inexistenta!");
    this->lista[poz].set_ore_pe_saptamana(ore_pe_saptamana_nou);
}

void RepositoryDiscipline::modifica_tip_disciplina(int id_disciplina, string tip_nou) {
    bool gasit;
    gasit = false;
    int poz = -1;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        throw repository_error("Disciplina inexistenta!");
    this->lista[poz].set_tip(std::move(tip_nou));
}

void RepositoryDiscipline::modifica_cadru_didactic(int id_disciplina, string cadru_didactic_nou) {
    bool gasit;
    int poz = -1;
    gasit = false;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        throw repository_error("Disciplina inexistenta!");
    this->lista[poz].set_cadru_didactic(std::move(cadru_didactic_nou));
}

Disciplina RepositoryDiscipline::get_disciplina_id(int id_disciplina) {
    bool gasit;
    gasit = false;
    int poz = -1;
    for(const auto& disc : this->lista){
        poz++;
        if(disc.get_id() == id_disciplina) {
            gasit = true;
            break;
        }
    }
    if(not gasit)
        //return Disciplina{};
        throw repository_error("Disciplina inexistenta!");
    return this->lista[poz];
}

std::vector<Disciplina>::iterator RepositoryDiscipline::get_lista_begin() {
    return this->lista.begin();
}

std::vector<Disciplina>::iterator RepositoryDiscipline::get_lista_end() {
    return this->lista.end();
}

//Vector<Disciplina> RepositoryDiscipline::get_lista_raw() {
//    return this->lista;
//}


