//
// Created by Andrei on 31.03.2023.
//
#include <algorithm>
#include <chrono>
#include <random>
#include "ServiceDiscipline.h"
#include "../vector/Iterator.h"
#include "../exceptions/erori_app.h"
#include "../undo/UndoAdauga.h"
#include "../undo/UndoStergere.h"
#include "../undo/UndoModificare.h"

ServiceDiscipline::ServiceDiscipline(RepositoryDiscipline* repositoryDiscipline1,
                                     const RepositoryContracte& repositoryContracte1,
                                     const ValidatorDisciplina& validatorDisciplina1) {
    this->validatorDisciplina = validatorDisciplina1;
    this->repositoryDiscipline = repositoryDiscipline1;
    this->repositoryContracte = repositoryContracte1;
}

int ServiceDiscipline::get_numar_discipline() const{
    return this->repositoryDiscipline->get_numar_elemente_repo();
}

void
ServiceDiscipline::adauga_disciplina(int id_disciplina, string denumire_disciplina, int ore_pe_saptamana, string tip,
                                     string cadru_didactic) {
    Disciplina disciplina_noua = Disciplina(id_disciplina, std::move(denumire_disciplina), ore_pe_saptamana, std::move(tip), std::move(cadru_didactic));
    validatorDisciplina.ValidareDisciplina(disciplina_noua);
    repositoryDiscipline->adauga_disciplina_repo(disciplina_noua);
    this->undoAction.push(new UndoAdauga{*this->repositoryDiscipline, disciplina_noua});
}

void ServiceDiscipline::sterge_disciplina(int id_disciplina) {
    validatorDisciplina.ValidareID(id_disciplina);
    auto disc_stearsa = repositoryDiscipline->sterge_disciplina_repo(id_disciplina);
    this->undoAction.push(new UndoStergere{*this->repositoryDiscipline, disc_stearsa});
}
void
ServiceDiscipline::modifica_disciplina(int id_disciplina, const string& denumire_disciplina, int ore_pe_saptamana, const string& tip,
                                       const string& cadru_didactic) {
    string erori;
    try {
        validatorDisciplina.ValidareID(id_disciplina);
    }
    catch (validator_error &e) {
        erori += e.what();
        erori += '\n';
    }
    if(not denumire_disciplina.empty()) {
        try{
            validatorDisciplina.ValidareDenumire(denumire_disciplina);
        }
        catch (validator_error &e){
            erori += e.what();
            erori += '\n';
        }
    }
    if(ore_pe_saptamana != 0) {
        try{
            validatorDisciplina.ValidareOre(ore_pe_saptamana);
        }
        catch (validator_error &e){
            erori += e.what();
            erori += '\n';
        }
    }
    if(not tip.empty()) {
        try{
            validatorDisciplina.ValidareTip(tip);
        }
        catch (validator_error &e){
            erori += e.what();
            erori += '\n';
        }
    }
    if(not cadru_didactic.empty()) {
        try{
            validatorDisciplina.ValidareCadruDidactic(cadru_didactic);
        }
        catch (validator_error &e){
            erori += e.what();
            erori += '\n';
        }
    }
    if(!erori.empty()) {
        erori.pop_back();
        throw validator_error(erori);
    }
    Disciplina disciplina{};
    try{
        disciplina = repositoryDiscipline->get_disciplina_id(id_disciplina);
    }
    catch (...){

    }
    if(not denumire_disciplina.empty())
        repositoryDiscipline->modifica_denumire_disciplina(id_disciplina, denumire_disciplina);
    if(ore_pe_saptamana != 0)
        repositoryDiscipline->modifica_ore_disciplina(id_disciplina, ore_pe_saptamana);
    if(not tip.empty())
        repositoryDiscipline->modifica_tip_disciplina(id_disciplina, tip);
    if(not cadru_didactic.empty())
        repositoryDiscipline->modifica_cadru_didactic(id_disciplina, cadru_didactic);
    this->undoAction.push(new UndoModificare{*this->repositoryDiscipline, disciplina});
}


std::vector<Disciplina>::iterator ServiceDiscipline::get_discipline_begin() {
    return this->repositoryDiscipline->get_lista_begin();
}

vector<Disciplina> ServiceDiscipline::cauta_disciplina(string nume_disc) {
    std::vector<Disciplina> dictionar_final;
    string copie;
    transform(nume_disc.begin(), nume_disc.end(), nume_disc.begin(), ::tolower);
    for(auto it = this->repositoryDiscipline->get_lista_begin(); it < this->repositoryDiscipline->get_lista_end(); it++){
        copie = (*it).get_denumire();
        transform(copie.begin(), copie.end(), copie.begin(), ::tolower);
        if(copie.find(nume_disc)!=string::npos)
            dictionar_final.push_back(*it);
    }
    return dictionar_final;
}

void ServiceDiscipline::autopopulare(){
    try {
        this->adauga_disciplina(10, "Programare orientata obiect", 4, "Obligatorie", "Istvan");
        this->adauga_disciplina(11, "Structuri de date si algoritmi", 3, "Obligatorie", "Czibula");
        this->adauga_disciplina(12, "Algoritmica grafurilor", 2, "Obligatorie", "Suciu");
        this->adauga_disciplina(13, "Geometrie", 2, "Obligatorie", "Blaga");
        this->adauga_disciplina(14, "Sisteme dinamice", 5, "Obligatorie", "Serban");
        this->adauga_disciplina(15, "Sisteme de operare", 5, "Obligatorie", "Boian");
        this->adauga_disciplina(16, "Metode avansate", 2, "Optionala", "Gabi");
        this->adauga_disciplina(17, "Analiza", 3, "Obligatorie", "Berinde");
        this->adauga_disciplina(18, "Algebra", 4, "Obligatorie", "Modoi");
        this->adauga_disciplina(19, "Programare in C", 1, "Facultativa", "Bota");
        this->adauga_disciplina(20, "Logica", 2, "Obligatorie", "Pop");
        this->adauga_disciplina(21, "ASC", 6, "OBLIGATORIE", "dr. Vancea");
    }
    catch (...) {

    }
}

//bool ore_mai_putine(Disciplina d1, Disciplina d2){
//    return d1.get_ore_pe_saptamana() >= d2.get_ore_pe_saptamana();
//}

std::vector<Disciplina>
ServiceDiscipline::filtrare_disciplina(int numar_ore, string cadru_did, char optiune) {
    std::vector<Disciplina> dictionar_final;
    string copie;
    transform(cadru_did.begin(), cadru_did.end(), cadru_did.begin(), ::tolower);
    if(optiune == '1'){
        std::copy_if(this->repositoryDiscipline->get_lista_begin(), this->repositoryDiscipline->get_lista_end(), std::back_inserter(dictionar_final),
                     [numar_ore](Disciplina disc){return disc.get_ore_pe_saptamana() >= numar_ore;});
//        for(auto it = this->repositoryDiscipline.get_lista_begin(); it < this->repositoryDiscipline.get_lista_end(); it++){
//            if((*it).get_ore_pe_saptamana() >= numar_ore)
//                dictionar_final.push_back(*it);
//        }
    }
    else if(optiune == '2'){
        std::copy_if(this->repositoryDiscipline->get_lista_begin(), this->repositoryDiscipline->get_lista_end(), std::back_inserter(dictionar_final),
                     [numar_ore](Disciplina disc){return disc.get_ore_pe_saptamana() <= numar_ore;});
//        for(auto it = this->repositoryDiscipline.get_lista_begin(); it < this->repositoryDiscipline.get_lista_end(); it++){
//            if((*it).get_ore_pe_saptamana() <= numar_ore)
//                dictionar_final.push_back(*it);
//        }
    }
    else{
        std::copy_if(this->repositoryDiscipline->get_lista_begin(), this->repositoryDiscipline->get_lista_end(), std::back_inserter(dictionar_final), [cadru_did](Disciplina disc){auto copie = disc.get_cadru_didactic(); transform(copie.begin(), copie.end(), copie.begin(), ::tolower); return copie.find(cadru_did)!=string::npos;});
//        for(auto it = this->repositoryDiscipline.get_lista_begin(); it < this->repositoryDiscipline.get_lista_end(); it++){
//            copie = (*it).get_cadru_didactic();
//            transform(copie.begin(), copie.end(), copie.begin(), ::tolower);
//            if(copie.find(cadru_did)!=string::npos)
//                dictionar_final.push_back(*it);
//        }
    }
    return dictionar_final;
}

Vector<Disciplina> ServiceDiscipline::sortare_discipline(char comanda, char ordine) {
    Vector<Disciplina> vectorfinal;
    for(auto it = this->repositoryDiscipline->get_lista_begin(); it < this->repositoryDiscipline->get_lista_end(); it++){
        vectorfinal.push_back(*it);
    }
    switch (comanda) {
        case '1':
            if(ordine == '+')
                //vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_denumire() < b.get_denumire(); });
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_denumire() < b.get_denumire(); });
                //std::sort(vectorfinal.begin(), vectorfinal.end(), [](Disciplina a, Disciplina b) {return a.get_denumire() < b.get_denumire(); });
            else
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_denumire() > b.get_denumire(); });
            break;
        case '2':
            if(ordine == '+')
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_ore_pe_saptamana() < b.get_ore_pe_saptamana();} );
            else
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_ore_pe_saptamana() > b.get_ore_pe_saptamana();} );
            break;
        case '3':
            if(ordine == '+')
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_cadru_didactic() < b.get_cadru_didactic();} );
            else
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_cadru_didactic() > b.get_cadru_didactic();} );
            break;
        case '4':
            if(ordine == '+')
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_tip() < b.get_tip();} );
            else
                vectorfinal.sort([](Disciplina a, Disciplina b) {return a.get_tip() > b.get_tip();} );
            break;
        default:
            return vectorfinal;
    }
    return vectorfinal;

}

std::vector<Disciplina>::iterator ServiceDiscipline::get_discipline_end() {
    return this->repositoryDiscipline->get_lista_end();
}

void ServiceDiscipline::creeaza_contract(int an_contract) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!\n");
    this->repositoryContracte.creeaza_contract(an_contract);
}

void ServiceDiscipline::goleste_contract(int an_contract) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!\n");
    this->repositoryContracte.goleste_contract(an_contract);
}

int ServiceDiscipline::get_numar_contracte() {
    return this->repositoryContracte.get_numar_contracte();
}

void ServiceDiscipline::export_contract(int an_contract, std::string filename) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!");
    if(filename.empty())
        throw contract_error("Filenameul nu poate fi vid!");
    this->repositoryContracte.export_contract(an_contract, filename);

}

void ServiceDiscipline::adauga_disciplina_contract(int an_contract, Disciplina disciplina_noua) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!");
    this->repositoryContracte.adauga_disciplina_contract(an_contract, disciplina_noua);

}

std::vector<int> ServiceDiscipline::get_ani_contracte() {
    vector<int> ani_contracte;
    for(auto it = this->repositoryContracte.get_contracte_begin(); it < this->repositoryContracte.get_contracte_end(); it++){
        ani_contracte.push_back(it->get_an());
    }
    return ani_contracte;
}

std::vector<Disciplina>::iterator ServiceDiscipline::get_contracte_begin(int an_contract) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!");
    for(auto iterator = this->repositoryContracte.get_contracte_begin(); iterator < this->repositoryContracte.get_contracte_end(); ++iterator){
        if(iterator->get_an() == an_contract)
            return iterator->get_begin_disc();
    }
    throw contract_error("Contract inexistent!");
}

std::vector<Disciplina>::iterator ServiceDiscipline::get_contracte_end(int an_contract) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!");
    for(auto iterator = this->repositoryContracte.get_contracte_begin(); iterator < this->repositoryContracte.get_contracte_end(); ++iterator){
        if(iterator->get_an() == an_contract)
            return iterator->get_end_disc();
    }
    throw contract_error("Contract inexistent!");
}

int ServiceDiscipline::get_numar_elemente_contract(int an_contract) {
    if(an_contract <= 0)
        throw contract_error("An contract invalid!");
    for(auto iterator = this->repositoryContracte.get_contracte_begin(); iterator < this->repositoryContracte.get_contracte_end(); ++iterator){
        if(iterator->get_an() == an_contract)
            return iterator->get_numar_discipline();
    }
    throw contract_error("Contract inexistent!");
}

int ServiceDiscipline::autopopulare_contract(int an_contract, int numar) {
    this->repositoryContracte.creeaza_contract(an_contract);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<Disciplina> vectorfinal;
    std::copy(this->repositoryDiscipline->get_lista_begin(), this->repositoryDiscipline->get_lista_end(), back_inserter(vectorfinal));
    std::shuffle(vectorfinal.begin(),vectorfinal.end(), std::default_random_engine(seed));
    if(numar >= this->repositoryDiscipline->get_numar_elemente_repo()){
        numar = this->repositoryDiscipline->get_numar_elemente_repo() - 1;
    }
    for(int i = 0; i < numar; ++i){
        this->repositoryContracte.adauga_disciplina_contract(an_contract, vectorfinal[i]);
    }
    return numar;
}

void ServiceDiscipline::autopopulare_teste() {
    try {
        this->adauga_disciplina(10, "Programare orientata obiect", 4, "Obligatorie", "Prof OOP");
        this->adauga_disciplina(11, "Structuri de date si algoritmi", 3, "Obligatorie", "Profa SDA");
        this->adauga_disciplina(12, "Algoritmica grafurilor", 2, "Obligatorie", "Prof grafuri");
        this->adauga_disciplina(13, "Geometrie", 4, "Obligatorie", "Prof geome");
        this->adauga_disciplina(14, "Sisteme dinamice", 4, "Obligatorie", "Pro SD");
        this->adauga_disciplina(15, "Metode avansate", 2, "Optionala", "Prof Gabi");
    }
    catch (...) {

    }
}

void ServiceDiscipline::undo() {
    if(this->undoAction.empty()){
        throw erori_app("Nu se mai poate face undo!");
    }
    ActiuneUndo* actiuneUndo = this->undoAction.top();
    this->undoAction.pop();
    actiuneUndo->doUndo();
    delete actiuneUndo;
}

ServiceDiscipline::~ServiceDiscipline() {
    while(not this->undoAction.empty()){
        ActiuneUndo* actiuneUndo = this->undoAction.top();
        this->undoAction.pop();
        delete actiuneUndo;

    }
}

Disciplina ServiceDiscipline::get_disciplina_id_srv(int id_disciplina) {
    return this->repositoryDiscipline->get_disciplina_id(id_disciplina);
}




