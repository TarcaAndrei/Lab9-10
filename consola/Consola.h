//
// Created by Andrei on 02.04.2023.
//

#ifndef LAB6_7_CONSOLA_H
#define LAB6_7_CONSOLA_H


#include "../service/ServiceDiscipline.h"

class Consola {
private:
    ServiceDiscipline serviceDiscipline;
    void afisare_discipline();
    void adauga_disciplina();
    void afisare_numar_discipline();
    void afisare_cap_tabel();
    void afisare_delimitator_linie();
    void stergere_disciplina();
    void modificare_disciplina();
    void cautare_disciplina();
    void filtrare_disciplina();
    void sortare_discipline();
    void autopopulare();
    void undo();

    ///de aici este submeniul pentru gestiunea contractelor
    void app_contracte();
    void afisare_contracte();
    void creare_contract();
    void adaugare_disciplina_contract();
    void afisare_discipline_contract();
    void generare_contract_nou();
    void golirea_unui_contract();
    void exportul_unui_contract();

public:
    Consola(const ServiceDiscipline& serviceDiscipline);
    ~Consola()=default;
    void run();
};


#endif //LAB6_7_CONSOLA_H
