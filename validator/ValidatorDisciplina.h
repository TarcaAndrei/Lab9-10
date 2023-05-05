//
// Created by Andrei on 31.03.2023.
//

#ifndef LAB6_7_VALIDATORDISCIPLINA_H
#define LAB6_7_VALIDATORDISCIPLINA_H


#include "../domain/Disciplina.h"

class ValidatorDisciplina {
public:
    ValidatorDisciplina();
    ~ValidatorDisciplina() = default;
    void ValidareDisciplina(const Disciplina& disciplina) const;
    void ValidareID(int id_disciplina) const;
    void ValidareDenumire(const string &denumire_disciplina) const;
    void ValidareOre(const int &ore_pe_saptamana) const;
    void ValidareTip(const string &tip_disciplina) const;
    void ValidareCadruDidactic(const string &cadru_didactic) const;
};


#endif //LAB6_7_VALIDATORDISCIPLINA_H
