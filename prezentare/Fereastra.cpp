//
// Created by Andrei on 05.05.2023.
//

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QStringListModel>
#include "Fereastra.h"

Fereastra::Fereastra(ServiceDiscipline serviceDiscipline1) {
    this->serviceDiscipline = serviceDiscipline1;
    this->initializare();
}

void Fereastra::initializare() {
    auto main = new QWidget();
    auto hlay = new QHBoxLayout();  //orizontal
    auto vlay = new QVBoxLayout();  //vertical
    auto buton_adauga = new QPushButton("Adauga");
    vlay->addWidget(buton_adauga);
    auto lista_discipline = new QListView();
    auto alta_lista_disc = new QStringListModel();
    auto afisare = new QWidget;
//    auto ceva = new QList<std::string>;
//    auto ceva = new QListWidgetItem();
//    auto ceva2 = new QListWidgetItem();
//    auto ceva3 = new QListWidgetItem();
//    ceva->setText("oda ");
//    ceva2->setText("THE MOTANS");
//    ceva3->setText("pax ");
    auto lista_discipline_afisare = new QListWidget();              ///aici pun la final denumirile
//    lista_discipline_afisare->addItem(ceva);
//    lista_discipline_afisare->addItem(ceva2);
//    lista_discipline_afisare->addItem(ceva3);
//    m_listWidget->append("ceva");
//    m_listWidget->append("ceva");
//    lista_discipline->addScrollBarWidget(main, );
//    QStringListModel m;
//    QStringList data = QStringList()<<"AAA"<<"BBB"<<"CCC";
//    m.setStringList(data);
//    lv->setModel(&m);
//    lv->show();
    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
        auto de_afisat = it->get_denumire();
        auto de_afisat_final = QString::fromStdString(de_afisat);
        auto list_item = new QListWidgetItem();
        list_item->setText(de_afisat_final);
        lista_discipline_afisare->addItem(list_item);
//        lista_discipline->addItem(new QListWidgetItem(de_afisat_final));

    }
    main->setLayout(hlay);
    main->show();
    auto layout_lista = new QListView(lista_discipline);
    hlay->addWidget(lista_discipline_afisare);
    auto details2 = new QWidget;
    auto adauga_widget = new QWidget;
    auto fl = new QFormLayout;
    adauga_widget->setLayout(fl);
    auto lbl_ID = new QLabel("ID");
    auto txtID = new QLineEdit;
    auto lbl_Denumire = new QLabel("Denumire");
    auto txtDenum = new QLineEdit;
    auto lbl_Prof = new QLabel("Profesor");
    auto txtProf = new QLineEdit;
    txtProf->setPlaceholderText("INTRODU PROFESOR");
    auto lbl_tip = new QLabel("Tip");
    auto txt_tip = new QLineEdit;
    auto lbl_ore = new QLabel("Numar ore");
    auto txt_ore = new QLineEdit;

    fl->addRow(lbl_ID, txtID);
    fl->addRow(lbl_Denumire, txtDenum);
    fl->addRow(lbl_Prof, txtProf);
    fl->addRow(lbl_tip, txt_tip);
    fl->addRow(lbl_ore, txt_ore);
    hlay->addWidget(adauga_widget);
    auto store = new QPushButton("Salveaza");
    hlay->addWidget(store);
    hlay->addLayout(vlay);
//    auto layout1 = new QVBoxLayout(main);
//    auto lbl1 = new QLabel("Nume", main);
//    lbl1->setLayout(layout1);
//    auto lbl2 = new QLabel("Lista", main);
//    lbl2->setLayout(layout1);
//    auto lista = new QList<int>;
//    lista->push_back(10);
//    lista->push_back(10);
//    lista->push_back(10);
//    main->show();
//    auto panou_st = new QWidget;
//    auto panou_dr = new QWidget;
//    auto label1 = new QLabel("Nume", main);
////    auto label1 = new QVBoxLayout;
////    auto label2 = new QVBoxLayout;
//    label1->setLayout(label1)
//    panou_st->setLayout(label1);
//    panou_dr->setLayout(label2);
//    label1->addWidget(new QPushButton{"ceva"});
//    label2->addWidget(new QPushButton{"altceva"});
//    panou_st->show();
//    panou_dr->show();
}

void Fereastra::afisare_discipline() {

}
