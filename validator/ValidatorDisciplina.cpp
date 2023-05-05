//
// Created by Andrei on 31.03.2023.
//

#include "ValidatorDisciplina.h"
#include "../exceptions/erori_app.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

ValidatorDisciplina::ValidatorDisciplina() {

}

void ValidatorDisciplina::ValidareDisciplina(const Disciplina& disciplina) const {
    string erori;
    if(disciplina.get_id() <= 0)
        erori += "ID invalid!\n";
    if(disciplina.get_denumire().length() <= 1)
        erori += "Denumire disciplina invalida!\n";
    if(disciplina.get_ore_pe_saptamana() <= 0)
        erori += "Numar ore pe saptamana invalid!\n";
    if(disciplina.get_tip().length() <= 2)
        erori += "Tip invalid!\n";
    if(disciplina.get_cadru_didactic().length() <= 2)
        erori += "Nume cadru didactic invalid!\n";
    if(erori.length() == 0)
        return;
    erori.pop_back();
    throw validator_error(erori);

}

void ValidatorDisciplina::ValidareID(int id_disciplina) const {
    if(id_disciplina <= 0)
        throw validator_error("ID invalid!");

}

void ValidatorDisciplina::ValidareDenumire(const string &denumire_disciplina) const {
    if(denumire_disciplina.length() <= 1)
        throw validator_error("Denumire disciplina invalida!");
}

void ValidatorDisciplina::ValidareOre(const int &ore_pe_saptamana) const {
    if(ore_pe_saptamana <= 0)
        throw validator_error("Numar ore pe saptamana invalid!");
}

void ValidatorDisciplina::ValidareTip(const string &tip_disciplina) const{
    if(tip_disciplina.length() <= 2)
        throw validator_error("Tip invalid!");
}

void ValidatorDisciplina::ValidareCadruDidactic(const string &cadru_didactic) const{
    if(cadru_didactic.length() <= 2)
        throw validator_error("Nume cadru didactic invalid!");
}
