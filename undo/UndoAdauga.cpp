//
// Created by Andrei on 28.04.2023.
//

#include "UndoAdauga.h"


UndoAdauga::UndoAdauga(RepositoryDiscipline &repositoryDiscipline1, const Disciplina& disciplina) :
    repositoryDiscipline{repositoryDiscipline1}, disciplinaAdaugata{disciplina} {};

void UndoAdauga::doUndo() {
    repositoryDiscipline.sterge_disciplina_repo(disciplinaAdaugata.get_id());

}
