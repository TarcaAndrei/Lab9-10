//
// Created by Andrei on 05.05.2023.
//

#ifndef LAB9_10_FEREASTRA_H
#define LAB9_10_FEREASTRA_H


#include <QWidget>
#include "../service/ServiceDiscipline.h"

class Fereastra : public QWidget {
private:
    ServiceDiscipline serviceDiscipline;
    void initializare();
    void afisare_discipline();
public:
    Fereastra(ServiceDiscipline serviceDiscipline1);
    ~Fereastra() override =default;
};


#endif //LAB9_10_FEREASTRA_H
