#include <iostream>
#include <QApplication>
#include <QLabel>
#include "testing/Teste.h"
#include "repository/RepositoryDiscipline.h"
#include "validator/ValidatorDisciplina.h"
#include "service/ServiceDiscipline.h"
#include "consola/Consola.h"
#include "vector/Teste.h"
#include "repository/RepositoryFileDiscipline.h"
#include "prezentare/Fereastra.h"

int main(int argc, char **argv) {
    Teste teste = Teste();
    teste.ruleaza_toate_testele();
    std::cout << "Toate testele au trecut cu succes!\n";
    teste_template();
    teste_disc();
    std::cout << "Testele pentru vector au trecut cu succes!\n";
    ValidatorDisciplina validatorDisciplina{};
    RepositoryContracte repositoryContracte{};
//    Consola consola{serviceDiscipline};
//    consola.run();
    auto* repositoryFileDiscipline = new RepositoryFileDiscipline("../repository/fisier_date"); //de ce asa
    auto* repositoryDiscipline = new RepositoryDiscipline();
    ServiceDiscipline serviceDiscipline{repositoryDiscipline, repositoryContracte, validatorDisciplina};
    ServiceDiscipline serviceDisciplineFile{repositoryFileDiscipline, repositoryContracte, validatorDisciplina};
    Consola consolaFile{serviceDisciplineFile};
//    consolaFile.run();
    QApplication a(argc, argv);
    Fereastra aplicatie(serviceDisciplineFile);
//    aplicatie.show();
    return a.exec();

}