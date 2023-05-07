//
// Created by Andrei on 05.05.2023.
//

#ifndef LAB9_10_FEREASTRA_H
#define LAB9_10_FEREASTRA_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QFormLayout>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include "../service/ServiceDiscipline.h"

class Fereastra : public QWidget {
private:
    ServiceDiscipline serviceDiscipline;
    QHBoxLayout* layout_principal;
    QVBoxLayout* layout_stanga;
    QVBoxLayout* layout_dreapta;
    void initializare();
    void incarca_lista();
    void formular();
public:
    Fereastra(const ServiceDiscipline& serviceDiscipline1);
    ~Fereastra() override =default;
};


#endif //LAB9_10_FEREASTRA_H
