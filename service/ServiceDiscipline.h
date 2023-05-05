//
// Created by Andrei on 31.03.2023.
//

#ifndef LAB6_7_SERVICEDISCIPLINE_H
#define LAB6_7_SERVICEDISCIPLINE_H


#include "../repository/RepositoryDiscipline.h"
#include "../validator/ValidatorDisciplina.h"
#include "../contract/ContractStudiu.h"
#include "../repository/RepositoryContracte.h"
#include "../undo/ActiuneUndo.h"
#include <vector>
#include <stack>

class ServiceDiscipline {
private:
    RepositoryDiscipline* repositoryDiscipline;
    RepositoryContracte repositoryContracte;
    std::stack<ActiuneUndo*> undoAction;
//    ActiuneUndo actiuneUndo{};
public:
    ValidatorDisciplina validatorDisciplina;
    ServiceDiscipline(RepositoryDiscipline* repositoryDiscipline1, const RepositoryContracte& repositoryContracte1, const ValidatorDisciplina& validatorDisciplina1);
    ServiceDiscipline() = default;
    ~ServiceDiscipline();
    [[nodiscard]] int get_numar_discipline() const;
    void adauga_disciplina(int id_disciplina, string denumire_disciplina, int ore_pe_saptamana, string tip,
                           string cadru_didactic);
    void sterge_disciplina(int id_disciplina);
    void modifica_disciplina(int id_disciplina, const string& denumire_disciplina, int ore_pe_saptamana, const string& tip,
                             const string& cadru_didactic);
    std::vector<Disciplina>::iterator get_discipline_begin();
    std::vector<Disciplina>::iterator get_discipline_end();
    vector<Disciplina> cauta_disciplina(string nume_disc);
    vector<Disciplina> filtrare_disciplina(int numar_ore, string cadru_did, char optiune);
    Vector<Disciplina> sortare_discipline(char comanda, char ordine);
    void autopopulare();
    void autopopulare_teste();
    void creeaza_contract(int an_contract);
    void adauga_disciplina_contract(int an_contract, Disciplina disciplina_noua);
    int get_numar_elemente_contract(int an_contract);
    void goleste_contract(int an_contract);
    void export_contract(int an_contract, std::string filename);
    std::vector<int> get_ani_contracte();
    std::vector<Disciplina>::iterator get_contracte_begin(int an_contract);
    std::vector<Disciplina>::iterator get_contracte_end(int an_contract);
    int autopopulare_contract(int an_contract, int numar);
    int get_numar_contracte();
    void undo();
};


#endif //LAB6_7_SERVICEDISCIPLINE_H
