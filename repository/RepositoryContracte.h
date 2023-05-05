//
// Created by Andrei on 19.04.2023.
//

#ifndef LAB6_7_REPOSITORYCONTRACTE_H
#define LAB6_7_REPOSITORYCONTRACTE_H


#include <vector>
#include "../contract/ContractStudiu.h"

class RepositoryContracte {
private:
    std::vector<ContractStudiu> listaContracte;
    int numar_contracte;
public:
    RepositoryContracte();
    ~RepositoryContracte()=default;
    void creeaza_contract(int an_contract);
    void adauga_disciplina_contract(int an_contract, const Disciplina& disciplina_noua);
    void goleste_contract(int an_contract);
    void export_contract(int an_contract, const std::string& filename);
    std::vector<ContractStudiu>::iterator get_contracte_begin();
    std::vector<ContractStudiu>::iterator get_contracte_end();
    int get_numar_contracte();
};


#endif //LAB6_7_REPOSITORYCONTRACTE_H
