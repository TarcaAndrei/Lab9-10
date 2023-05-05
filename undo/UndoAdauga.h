//
// Created by Andrei on 28.04.2023.
//

#ifndef LAB6_7_UNDOADAUGA_H
#define LAB6_7_UNDOADAUGA_H


#include "ActiuneUndo.h"

class UndoAdauga : public ActiuneUndo{
    Disciplina disciplinaAdaugata;
    RepositoryDiscipline &repositoryDiscipline;
public:
    UndoAdauga(RepositoryDiscipline &repositoryDiscipline1, const Disciplina& disciplina);
    void doUndo() override;
    ~UndoAdauga() override =default;

};


#endif //LAB6_7_UNDOADAUGA_H
