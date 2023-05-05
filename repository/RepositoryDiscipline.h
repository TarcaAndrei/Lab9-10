//
// Created by Andrei on 29.03.2023.
//

#ifndef LAB6_7_REPOSITORYDISCIPLINE_H
#define LAB6_7_REPOSITORYDISCIPLINE_H
#include <map>
#include "../domain/Disciplina.h"
#include "../vector/Vector.h"

class RepositoryDiscipline {
protected:
    std::vector<Disciplina> lista;
    int lungime;
public:
    RepositoryDiscipline();
    virtual ~RepositoryDiscipline() = default;
    virtual void adauga_disciplina_repo(const Disciplina& disciplina_noua);
    virtual Disciplina sterge_disciplina_repo(int id_disciplina);
    [[nodiscard]] int get_numar_elemente_repo() const;
    virtual void modifica_denumire_disciplina(int id_disciplina, string denumire_noua);
    virtual void modifica_ore_disciplina(int id_disciplina, int ore_pe_saptamana_nou);
    virtual void modifica_tip_disciplina(int id_disciplina, string tip_nou);
    virtual void modifica_cadru_didactic(int id_disciplina, string cadru_didactic_nou);
    Disciplina get_disciplina_id(int id_disciplina);
    std::vector<Disciplina>::iterator get_lista_begin();      // dar pe viitor doar iteratorul
    std::vector<Disciplina>::iterator get_lista_end();      // dar pe viitor doar iteratorul

//    Vector<Disciplina> get_lista_raw();
};



#endif //LAB6_7_REPOSITORYDISCIPLINE_H
