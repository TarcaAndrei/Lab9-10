//
// Created by Andrei on 28.04.2023.
//

#include "UndoStergere.h"

UndoStergere::UndoStergere(RepositoryDiscipline &repositoryDiscipline1, const Disciplina& disciplina) :
    repositoryDiscipline{repositoryDiscipline1}, disciplinaStearsa{disciplina}{}

void UndoStergere::doUndo() {
    this->repositoryDiscipline.adauga_disciplina_repo(disciplinaStearsa);
};
