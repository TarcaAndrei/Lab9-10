//
// Created by Andrei on 28.04.2023.
//

#ifndef LAB6_7_UNDOMODIFICARE_H
#define LAB6_7_UNDOMODIFICARE_H


#include "ActiuneUndo.h"

class UndoModificare : public ActiuneUndo{
private:
    RepositoryDiscipline &repositoryDiscipline;
    Disciplina disciplinaModificata;
public:
    UndoModificare(RepositoryDiscipline &repositoryDiscipline1, const Disciplina& disciplina);
    ~UndoModificare()=default;
    void doUndo() override;
};


#endif //LAB6_7_UNDOMODIFICARE_H
