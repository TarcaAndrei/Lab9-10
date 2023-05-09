//
// Created by Andrei on 09.05.2023.
//

#ifndef LAB9_10_FEREASTRACONTRACTE_H
#define LAB9_10_FEREASTRACONTRACTE_H

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
#include <QImageReader>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QMessageBox>
#include "../service/ServiceDiscipline.h"

class FereastraContracte : public QWidget {
private:
    ServiceDiscipline& serviceDiscipline;
    QHBoxLayout* layout_principal;
    QVBoxLayout* layout_stanga;
    QVBoxLayout* layout_mijloc;
    QVBoxLayout* layout_dreapta;
    QListWidget* lista_contracte;
    QListWidget* lista_discipline;
    QLineEdit* an_txt;
    QLineEdit* file_txt;
    QLineEdit* denumire_txt;
    QLineEdit* numar_txt;

    void initializare();
    void incarca_lista_ani();
    void reload_lista_ani();
    void incarca_lista_contract(int an);
    void formular();
    void butoane_generice();
    void clear_fields();
public:
    explicit FereastraContracte(ServiceDiscipline& serviceDiscipline1);
    ~FereastraContracte() override = default;
};


#endif //LAB9_10_FEREASTRACONTRACTE_H
