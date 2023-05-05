//
// Created by Andrei on 18.04.2023.
//

#ifndef LAB6_7_CONTRACTSTUDIU_H
#define LAB6_7_CONTRACTSTUDIU_H

#include "../domain/Disciplina.h"
#include <vector>


class ContractStudiu {
private:
    std::vector<Disciplina> lista;
    int dimensiune;
    int an;
public:
    ContractStudiu(int an);
    ~ContractStudiu()=default;
    void delete_all();
    int get_an();
    int get_numar_discipline();
    void adauga_disciplina_contract(const Disciplina& disciplina_noua);
    void genereaza_contract(const string& filename);
    std::vector<Disciplina>::iterator get_begin_disc();
    std::vector<Disciplina>::iterator get_end_disc();
};


#endif //LAB6_7_CONTRACTSTUDIU_H
