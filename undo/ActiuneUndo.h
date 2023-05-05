//
// Created by Andrei on 28.04.2023.
//

#ifndef LAB6_7_ACTIUNEUNDO_H
#define LAB6_7_ACTIUNEUNDO_H


#include "../repository/RepositoryDiscipline.h"

class ActiuneUndo {
public:
//    RepositoryDiscipline repositoryDiscipline;
//    ActiuneUndo(RepositoryDiscipline repositoryDiscipline1);
    virtual ~ActiuneUndo()= default;
    virtual void doUndo()=0;
};


#endif //LAB6_7_ACTIUNEUNDO_H
