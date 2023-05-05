//
// Created by Andrei on 04.05.2023.
//

#ifndef LAB9_10_REPOSITORYFILEDISCIPLINE_H
#define LAB9_10_REPOSITORYFILEDISCIPLINE_H


#include "RepositoryDiscipline.h"
#include <fstream>

class RepositoryFileDiscipline : public RepositoryDiscipline{
private:
    std::string filename;
    void write_to_file();
    void read_from_file();
    int transform_string_to_int(string ceva);
public:
    explicit RepositoryFileDiscipline(std::string filename1) : RepositoryDiscipline(), filename(filename1){
        this->read_from_file();
    };
    ~RepositoryFileDiscipline() override =default;
    void adauga_disciplina_repo(const Disciplina& disciplina_noua) override;
    Disciplina sterge_disciplina_repo(int id_disciplina) override ;
    void modifica_denumire_disciplina(int id_disciplina, string denumire_noua) override;
    void modifica_ore_disciplina(int id_disciplina, int ore_pe_saptamana_nou) override;
    void modifica_tip_disciplina(int id_disciplina, string tip_nou) override;
    void modifica_cadru_didactic(int id_disciplina, string cadru_didactic_nou) override;

};


#endif //LAB9_10_REPOSITORYFILEDISCIPLINE_H
