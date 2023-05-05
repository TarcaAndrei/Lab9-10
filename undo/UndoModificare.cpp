//
// Created by Andrei on 28.04.2023.
//

#include "UndoModificare.h"

UndoModificare::UndoModificare(RepositoryDiscipline &repositoryDiscipline1, const Disciplina& disciplina):
    repositoryDiscipline{repositoryDiscipline1}, disciplinaModificata{disciplina}{
}

void UndoModificare::doUndo() {
    this->repositoryDiscipline.sterge_disciplina_repo(this->disciplinaModificata.get_id());
    this->repositoryDiscipline.adauga_disciplina_repo(this->disciplinaModificata);
}

