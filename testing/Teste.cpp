//
// Created by Andrei on 29.03.2023.
//

#include <cassert>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Teste.h"
#include "../domain/Disciplina.h"
#include "../repository/RepositoryDiscipline.h"
#include "../validator/ValidatorDisciplina.h"
#include "../service/ServiceDiscipline.h"
#include "../exceptions/erori_app.h"
#include "../repository/RepositoryContracte.h"


Teste::Teste() = default;

void Teste::ruleaza_toate_testele() const {
    this->ruleaza_teste_domeniu();
    this->ruleaza_teste_erori();
    this->ruleaza_teste_validare();
    this->ruleaza_teste_repository();
    this->ruleaza_teste_contract();
    this->ruleaza_teste_repository_contract();
    this->ruleaza_teste_service();
}


void Teste::ruleaza_teste_domeniu() const{
    Disciplina disciplina1 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina2 = Disciplina(111, "OPOP", 34, "Obligatoriee", "Prof12");
    assert(disciplina1.get_id() == 10);
    assert(disciplina1.get_denumire() == "OOP");
    assert(disciplina1.get_ore_pe_saptamana() == 4);
    assert(disciplina1.get_tip() == "Obligatorie");
    assert(disciplina1.get_cadru_didactic() == "Prof1");
    disciplina1.set_denumire("Object Oriented Programming");
    disciplina1.set_ore_pe_saptamana(3);
    disciplina1.set_tip("OBLIGATORIE");
    disciplina1.set_cadru_didactic("Prof fain");
    assert(disciplina1.get_denumire() == "Object Oriented Programming");
    assert(disciplina1.get_ore_pe_saptamana() == 3);
    assert(disciplina1.get_tip() == "OBLIGATORIE");
    assert(disciplina1.get_cadru_didactic() == "Prof fain");
    auto ceva = disciplina1.afisare_disciplina();
    assert(ceva == "|   10   | Object Oriented Programming  |          Prof fain           |    OBLIGATORIE    |    3h/sapt    |\n");
    auto ceva2 = disciplina2.afisare_disciplina();
    assert(ceva2 == "|  111   |             OPOP             |            Prof12            |   Obligatoriee    |   34h/sapt    |\n");
}

void Teste::ruleaza_teste_validare() const {
    Disciplina disciplina1 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina2 = Disciplina(-10, "P", -4, "O", "");
    ValidatorDisciplina validatorDisciplina{};
    validatorDisciplina.ValidareDisciplina(disciplina1);
    try{
        validatorDisciplina.ValidareDisciplina(disciplina2);
        assert(false);
    }
    catch (validator_error &e){
        assert(e.what() == "ID invalid!\nDenumire disciplina invalida!\nNumar ore pe saptamana invalid!\nTip invalid!\nNume cadru didactic invalid!");
    }
    try {
        validatorDisciplina.ValidareID(-4);
        assert(false);
    }
    catch (validator_error &e){
        assert(e.what() == "ID invalid!");
    }
    validatorDisciplina.ValidareID(10);

}

void Teste::ruleaza_teste_repository() const{
    RepositoryDiscipline repo{};
    Disciplina disciplina1{10, "OOP", 4, "Obligatorie", "Prof1"};
    Disciplina disciplina2 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina3 = Disciplina(11, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina4;

    repo.adauga_disciplina_repo(disciplina1);
    try{
        repo.adauga_disciplina_repo(disciplina2);
        assert(false);
    }
    catch(repository_error &e ){
        assert(e.what() == "Disciplina existenta!");
    }
    assert(repo.get_numar_elemente_repo() == 1);
    repo.adauga_disciplina_repo(disciplina3);
    assert(repo.get_numar_elemente_repo() == 2);
    try{
        repo.sterge_disciplina_repo(15);
        assert(false);
    }
    catch( repository_error& e ){
        assert(e.what() == "Disciplina inexistenta!");
    }
    repo.sterge_disciplina_repo(10);
    assert(repo.get_numar_elemente_repo() == 1);
    disciplina4 = repo.get_disciplina_id(11);
    assert(disciplina4.get_id() == 11);
    assert(disciplina4.get_denumire() == "OOP");
    assert(disciplina4.get_ore_pe_saptamana() == 4);
    assert(disciplina4.get_tip() == "Obligatorie");
    assert(disciplina4.get_cadru_didactic() == "Prof1");
    try{
        repo.modifica_denumire_disciplina(12, "Object Oriented Programming");
        assert(false);
    }
    catch( repository_error& e ){
        assert(e.what() == "Disciplina inexistenta!");
    }
    try{
        repo.modifica_ore_disciplina(12, 3);
        assert(false);
    }
    catch( repository_error& e ){
        assert(e.what() == "Disciplina inexistenta!");
    }
    try{
        repo.modifica_tip_disciplina(12, "OBLIGATORIE");
        assert(false);
    }
    catch( repository_error& e ){
        assert(e.what() == "Disciplina inexistenta!");
    }
    try{
        repo.modifica_cadru_didactic(12, "Prof fain");
        assert(false);
    }
    catch( repository_error& e ){
        assert(e.what() == "Disciplina inexistenta!");
    }
    repo.modifica_denumire_disciplina(11, "Object Oriented Programming");
    repo.modifica_ore_disciplina(11, 3);
    repo.modifica_tip_disciplina(11, "OBLIGATORIE");
    repo.modifica_cadru_didactic(11, "Prof fain");
    disciplina4 = repo.get_disciplina_id(11);
    assert(disciplina4.get_denumire() == "Object Oriented Programming");
    assert(disciplina4.get_ore_pe_saptamana() == 3);
    assert(disciplina4.get_tip() == "OBLIGATORIE");
    assert(disciplina4.get_cadru_didactic() == "Prof fain");
    try{
        repo.get_disciplina_id(15);
        assert(false);
    }
    catch( repository_error& e ) {
        assert(e.what() == "Disciplina inexistenta!");
    }
    //aici ceva cu iteratorul
}

void Teste::ruleaza_teste_service() const{
    ValidatorDisciplina validatorDisciplina{};
    RepositoryDiscipline repositoryDiscipline{};
    RepositoryContracte repositoryContracte{};
    ServiceDiscipline serviceDiscipline{&repositoryDiscipline, repositoryContracte, validatorDisciplina};
    assert(serviceDiscipline.get_numar_discipline() == 0);
    serviceDiscipline.adauga_disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    assert(serviceDiscipline.get_numar_discipline() == 1);
    try{
        serviceDiscipline.adauga_disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
        assert(false);
    }
    catch (repository_error &e){
        assert(e.what() == "Disciplina existenta!");
    }
    try{
        serviceDiscipline.adauga_disciplina(-10, "P", -4, "O", "");
        assert(false);
    }
    catch (validator_error &e){
        assert(e.what() == "ID invalid!\nDenumire disciplina invalida!\n"
                                "Numar ore pe saptamana invalid!\nTip invalid!\n"
                                "Nume cadru didactic invalid!");
    }
    serviceDiscipline.adauga_disciplina(12, "SO", 6, "OBLIGATORIE", "Prof ff fain");
    assert(serviceDiscipline.get_numar_discipline() == 2);
    serviceDiscipline.sterge_disciplina(10);
    assert(serviceDiscipline.get_numar_discipline() == 1);
    try{
        serviceDiscipline.sterge_disciplina(-3);
        assert(false);
    }

    catch (validator_error &e){
        assert(e.what() == "ID invalid!");
    }
    try{
        serviceDiscipline.sterge_disciplina(9);
        assert(false);
    }
    catch (repository_error &e){
        assert(e.what() == "Disciplina inexistenta!");
    }
    assert(serviceDiscipline.get_numar_discipline() == 1);
    serviceDiscipline.modifica_disciplina(12, "Sisteme de operare", 7, "OBLG", "A_B_P");
    try{
        serviceDiscipline.modifica_disciplina(-1, "c", -2, "c", "c");
        assert(false);
    }
    catch (erori_app &e){
        assert(e.what() == "ID invalid!\nDenumire disciplina invalida!\n"
                                "Numar ore pe saptamana invalid!\nTip invalid!\n"
                                "Nume cadru didactic invalid!");
    }
    serviceDiscipline.sterge_disciplina(12);
    serviceDiscipline.autopopulare_teste();
    auto dict1 = serviceDiscipline.filtrare_disciplina(4, "", '1');
    assert(dict1.size() == 3);
    auto dict2 = serviceDiscipline.filtrare_disciplina(4, "", '2');
    assert(dict2.size() == 6);
    auto dict3 = serviceDiscipline.filtrare_disciplina(0, "prof",'3');
    assert(dict3.size() == 5);
    auto vecto1 = serviceDiscipline.sortare_discipline('1', '+');
    assert(vecto1[0].get_id() == 12);
    auto vecto2= serviceDiscipline.sortare_discipline('1', '-');
    assert(vecto2[0].get_id() == 11);
    auto vecto3 = serviceDiscipline.sortare_discipline('2', '+');
    assert(vecto3[0].get_id() == 12);
    auto vecto4 = serviceDiscipline.sortare_discipline('2', '-');
    assert(vecto4[0].get_id() == 10);
    auto vecto5 = serviceDiscipline.sortare_discipline('3', '+');
    assert(vecto5[0].get_id() == 14);
    auto vecto6 = serviceDiscipline.sortare_discipline('3', '-');
    assert(vecto6[0].get_id() == 11);
    auto vecto7 = serviceDiscipline.sortare_discipline('4', '+');
    assert(vecto7[0].get_id() == 10);
    auto vecto8 = serviceDiscipline.sortare_discipline('4', '-');
    assert(vecto8[0].get_id() == 15);
    auto mapceva = serviceDiscipline.cauta_disciplina("alg");
    assert(mapceva.size() == 2);
    auto ceva = serviceDiscipline.get_discipline_begin();
    auto altcv = serviceDiscipline.get_discipline_end();
    ValidatorDisciplina validatorDisciplina1{};
    RepositoryDiscipline repositoryDiscipline1{};
    RepositoryContracte repositoryContracte1{};
    ServiceDiscipline serviceDiscipline1{&repositoryDiscipline1, repositoryContracte1, validatorDisciplina1};
    serviceDiscipline1.autopopulare();
    serviceDiscipline1.autopopulare();
    assert(serviceDiscipline.get_numar_discipline() > 5);
}

void Teste::ruleaza_teste_erori() const {
    try{
        funct1(0);
        assert(false);
    }
    catch(erori_app &e){
        assert(e.what() == "Numar nul!");
    }
    try{
        funct1(1);
        assert(false);
    }
    catch(erori_app &e){
        assert(e.what() == "Numar 1!");
    }
    try{
        this->funct2("");
        assert(false);
    }
    catch(validator_error &e){
        assert(e.what() == "String vid!");
    }
}

void Teste::funct1(int a) const {
    if(a == 0)
        throw repository_error("Numar nul!");
    if(a == 1)
        throw ui_error("Numar 1!");
}

void Teste::funct2(std::string b) const {
    if(b.empty())
        throw validator_error("String vid!");
}

void Teste::ruleaza_teste_contract() const {
    auto contract = ContractStudiu(1);
    assert(contract.get_an() == 1);
    assert(contract.get_numar_discipline() == 0);
    Disciplina disciplina1 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina2 = Disciplina(111, "OPOP", 34, "Obligatoriee", "Prof12");
    contract.adauga_disciplina_contract(disciplina1);
    contract.adauga_disciplina_contract(disciplina2);
    assert(contract.get_numar_discipline() == 2);
    try{
        contract.adauga_disciplina_contract(disciplina1);
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Disciplina existenta!");
    }
    //contract.genereaza_contract("test1"); - merge =))
    int a=0;
    for(auto ceva = contract.get_begin_disc(); ceva < contract.get_end_disc(); ++ceva){
        a++;
    }
    assert(a==2);
    contract.delete_all();
    assert(contract.get_numar_discipline() == 0);
}

void Teste::ruleaza_teste_repository_contract() const {
    auto repositoryContracte = RepositoryContracte();
    repositoryContracte.creeaza_contract(1);
    try{
        repositoryContracte.creeaza_contract(1);
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Acest an are deja un contract!");
    }
    Disciplina disciplina1 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina2 = Disciplina(111, "OPOP", 34, "Obligatoriee", "Prof12");
    repositoryContracte.adauga_disciplina_contract(1, disciplina1);
    repositoryContracte.adauga_disciplina_contract(1, disciplina2);
    try{
        repositoryContracte.adauga_disciplina_contract(4, disciplina1);
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Nu exista niciun contract pentru acest an!");
    }
    try{
        repositoryContracte.goleste_contract(3);
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Nu exista niciun contract pentru acest an!");
    }
    assert(repositoryContracte.get_numar_contracte() == 1);
    for(auto iterator = repositoryContracte.get_contracte_begin(); iterator < repositoryContracte.get_contracte_end(); iterator++){
        assert(iterator->get_numar_discipline()==2);
    }
    repositoryContracte.export_contract(1, "test2");
    try{
        repositoryContracte.export_contract(3, "ceva");
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Nu exista niciun contract pentru acest an!");
    }
    try{
        repositoryContracte.export_contract(1, "");
        assert(false);
    }
    catch (contract_error &e){
        assert(e.what() == "Filenameul nu poate fi vid!");
    }
    repositoryContracte.goleste_contract(1);
}


