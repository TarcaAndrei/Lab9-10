//
// Created by Andrei on 28.04.2023.
//

#ifndef LAB6_7_UNDOSTERGERE_H
#define LAB6_7_UNDOSTERGERE_H


#include "ActiuneUndo.h"

class UndoStergere : public ActiuneUndo{
private:
    RepositoryDiscipline &repositoryDiscipline;
    Disciplina disciplinaStearsa;
public:
    UndoStergere(RepositoryDiscipline &repositoryDiscipline, const Disciplina& disciplina);
    void doUndo() override;
    ~UndoStergere() override =default;
};


#endif //LAB6_7_UNDOSTERGERE_H
