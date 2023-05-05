//
// Created by Andrei on 04.05.2023.
//

#include "RepositoryFileDiscipline.h"
#include "../exceptions/erori_app.h"

#include <iostream>
#include <utility>


void RepositoryFileDiscipline::adauga_disciplina_repo(const Disciplina &disciplina_noua) {
    RepositoryDiscipline::adauga_disciplina_repo(disciplina_noua);
    this->write_to_file();
}

Disciplina RepositoryFileDiscipline::sterge_disciplina_repo(int id_disciplina) {
    auto disc =  RepositoryDiscipline::sterge_disciplina_repo(id_disciplina);
    this->write_to_file();
    return disc;
}

void RepositoryFileDiscipline::modifica_denumire_disciplina(int id_disciplina, string denumire_noua) {
    RepositoryDiscipline::modifica_denumire_disciplina(id_disciplina, denumire_noua);
    this->write_to_file();
}

void RepositoryFileDiscipline::modifica_ore_disciplina(int id_disciplina, int ore_pe_saptamana_nou) {
    RepositoryDiscipline::modifica_ore_disciplina(id_disciplina, ore_pe_saptamana_nou);
    this->write_to_file();
}

void RepositoryFileDiscipline::modifica_tip_disciplina(int id_disciplina, string tip_nou) {
    RepositoryDiscipline::modifica_tip_disciplina(id_disciplina, tip_nou);
    this->write_to_file();
}

void RepositoryFileDiscipline::modifica_cadru_didactic(int id_disciplina, string cadru_didactic_nou) {
    RepositoryDiscipline::modifica_cadru_didactic(id_disciplina, cadru_didactic_nou);
    this->write_to_file();
}

int RepositoryFileDiscipline::transform_string_to_int(string ceva){
    int numar = 0;
    int p = 1;
    char l;
    while(ceva.length() > 0){
        l = ceva[ceva.length()-1];
        l = l - '0';
        if(l < 0 or l > 9){
            throw ui_error("Numarul trebuie sa fie natural!");
        }
        numar = numar + l * p;
        p = p * 10;
        ceva.pop_back();
    }
    return numar;
}

void RepositoryFileDiscipline::read_from_file() {
    char despartire= ';';
    std::ifstream fin;
    fin.open(this->filename);
    if(fin.fail()){
        throw erori_app("Fisierul nu exista!\n");
    }
    while(fin.good()){
        string obiect;
        getline(fin, obiect);
        if(obiect.empty()){
            break;
        }
        int i, j;
        i = 0;
//        string nume_disc, id_str, pret_str, prof_disc, tip_disc;
        std::map<int, std::string> stringuri;
        for(j = 0; j <= 4; ++j) {
            while (obiect[i] != despartire && i < obiect.length()) {
                stringuri[j] += obiect[i];
                ++i;
            }
            ++i;
        }
        auto id_disc = this->transform_string_to_int(stringuri[0]);
        auto nr_ore = this->transform_string_to_int(stringuri[4]);
        Disciplina disciplina = Disciplina(id_disc, stringuri[1], nr_ore, stringuri[2], stringuri[3]);
        this->lista.push_back(disciplina);
        this->lungime++;
    }
    fin.close();
}

void RepositoryFileDiscipline::write_to_file() {
    char despartire= ';';
    std::ofstream fout;
    fout.open(this->filename);
    if(fout.fail()){
        throw erori_app("Fisierul nu exista!\n");
    }
    for(auto i = 0; i < this->lungime; ++i){
        fout<<this->lista[i].scriere_disciplina();
        fout<<"\n";
    }
    fout.close();
}
