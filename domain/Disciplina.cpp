//
// Created by Andrei on 29.03.2023.
//

#include "Disciplina.h"
#include <cstring>
#include <string>
#include <utility>
#include <iostream>

Disciplina::Disciplina(int id_disciplina, string denumire_disciplina, int ore_pe_saptamana, string tip,
                       string cadru_didactic) {
    this->id_disciplina = id_disciplina;
    this->denumire_disciplina = std::move(denumire_disciplina);
    this->ore_pe_saptamana = ore_pe_saptamana;
    this->tip = std::move(tip);
    this->cadru_didactic = std::move(cadru_didactic);
}

int Disciplina::get_id() const {
    return this->id_disciplina;
}

string Disciplina::get_denumire() const {
    return this->denumire_disciplina;
}

int Disciplina::get_ore_pe_saptamana() const {
    return this->ore_pe_saptamana;
}

string Disciplina::get_tip() const {
    return this->tip;
}

string Disciplina::get_cadru_didactic() const {
    return this->cadru_didactic;
}

void Disciplina::set_denumire(string denumire_noua) {
    this->denumire_disciplina = std::move(denumire_noua);
}

void Disciplina::set_ore_pe_saptamana(int ore_pe_saptamana_nou) {
    this->ore_pe_saptamana = ore_pe_saptamana_nou;
}

void Disciplina::set_tip(string tip_nou) {
    this->tip = std::move(tip_nou);
}

void Disciplina::set_cadru_didactic(string cadru_didactic_nou) {
    this->cadru_didactic = std::move(cadru_didactic_nou);
}

string Disciplina::afisare_disciplina() {
    string printare;     // nu da return la asta ca asa o zis istvan
    string ore_str;
    string id_str;
    int cifre_id;
    int nr_spatiu_1;
    int nr_spatiu_2;
    int i;
    // pentru ID am 8
    // pnetru TIP am 13
    // pentru Destinatie am 20
    // pentru Data de plecare am 19
    // pentru pret am 12
    id_str = to_string(this->id_disciplina);
    ore_str = to_string(this->ore_pe_saptamana);
    ore_str += "h/sapt";
    cifre_id = (int)id_str.length();
    cifre_id = 8 - cifre_id;
    if(cifre_id % 2 == 0){
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = cifre_id/2;
    } else{
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = nr_spatiu_1 + 1;
    }
    printare = "|";
    for(i = 1; i<=nr_spatiu_1; i++)
        printare +=  " ";
    printare +=  id_str;
    for(i = 1; i<=nr_spatiu_2; i++)
        printare +=  " ";

    printare +=  "|";

    cifre_id = (int)this->denumire_disciplina.length();
    cifre_id = 30 - cifre_id;
    if(cifre_id % 2 == 0){
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = cifre_id/2;
    } else{
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = nr_spatiu_1 + 1;
    }
    for(i = 1; i<=nr_spatiu_1; i++)
        printare +=  " ";
    printare +=  this->denumire_disciplina;
    for(i = 1; i<=nr_spatiu_2; i++)
        printare +=  " ";
    printare +=  "|";

    cifre_id = (int) this->cadru_didactic.length();
    cifre_id = 30 - cifre_id;
    if(cifre_id % 2 == 0){
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = cifre_id/2;
    } else{
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = nr_spatiu_1 + 1;
    }

    for(i = 1; i<=nr_spatiu_1; i++)
        printare +=  " ";
    printare +=  this->cadru_didactic;
    for(i = 1; i<=nr_spatiu_2; i++)
        printare +=  " ";
    printare +=  "|";

    cifre_id = (int)this->tip.length();
    cifre_id = 19 - cifre_id;
    if(cifre_id % 2 == 0){
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = cifre_id/2;
    } else{
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = nr_spatiu_1 + 1;
    }
    for(i = 1; i<=nr_spatiu_1; i++)
        printare +=  " ";
    printare +=  this->tip;
    for(i = 1; i<=nr_spatiu_2; i++)
        printare +=  " ";
    printare +=  "|";

    cifre_id = (int) ore_str.length();
    cifre_id = 15 - cifre_id;
    if(cifre_id % 2 == 0){
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = cifre_id/2;
    } else{
        nr_spatiu_1 = cifre_id/2;
        nr_spatiu_2 = nr_spatiu_1 + 1;
    }
    for(i = 1; i<=nr_spatiu_1; i++)
        printare +=  " ";
    printare +=  ore_str;
    for(i = 1; i<=nr_spatiu_2; i++)
        printare +=  " ";
    printare +=  "|\n";
    //std::cout<<printare;
    return printare;
}

Disciplina::Disciplina(const Disciplina &disciplina) {
    this->cadru_didactic = disciplina.cadru_didactic;
    this->tip = disciplina.tip;
    this->denumire_disciplina = disciplina.denumire_disciplina;
    this->id_disciplina = disciplina.id_disciplina;
    this->ore_pe_saptamana = disciplina.ore_pe_saptamana;
}

string Disciplina::scriere_disciplina() {
    std::string final;
    final+=std::to_string(this->get_id());
    final+=";";
    final+=this->denumire_disciplina;
    final+=";";
    final+=this->get_cadru_didactic();
    final+=";";
    final+=this->tip;
    final+=";";
    final+=std::to_string(this->get_ore_pe_saptamana());
    return final;
}


