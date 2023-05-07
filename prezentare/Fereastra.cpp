//
// Created by Andrei on 05.05.2023.
//
#include "Fereastra.h"

Fereastra::Fereastra(const ServiceDiscipline& serviceDiscipline1) {
    this->serviceDiscipline = serviceDiscipline1;
    this->initializare();
}

void Fereastra::formular() {
    auto formular_disc = new QFormLayout;
    this->layout_dreapta->addLayout(formular_disc);
    auto lbl_id = new QLabel("ID");
    auto lbl_den = new QLabel("Denumire");
    auto lbl_tip = new QLabel("Tip");
    auto lbl_prof = new QLabel("Profesor");
    auto lbl_ore = new QLabel("Numar ore");
    auto txt_id = new QLineEdit;
    txt_id->setPlaceholderText("Introdu ID");
    txt_id->setValidator(new QIntValidator());
    auto txt_den = new QLineEdit;
    txt_den->setPlaceholderText("Introdu Denumirea");
    auto txt_tip = new QLineEdit;
    txt_tip->setPlaceholderText("Introdu Tipul");
    auto txt_prof = new QLineEdit;
    txt_prof->setPlaceholderText("Introdu Profesorul");
    auto txt_ore = new QLineEdit;
    txt_ore->setPlaceholderText("Introdu Numarul de Ore");
    txt_ore->setValidator(new QIntValidator(0, 10));
    formular_disc->addRow(lbl_id, txt_id);
    formular_disc->addRow(lbl_den, txt_den);
    formular_disc->addRow(lbl_tip, txt_tip);
    formular_disc->addRow(lbl_prof, txt_prof);
    formular_disc->addRow(lbl_ore, txt_ore);
    auto buton_salvare = new QPushButton;
    buton_salvare->setText("&Adaugare");
    auto buton_modificare = new QPushButton;
    buton_modificare->setText("&Modifica");
    auto buton_cancel = new QPushButton;
    buton_cancel->setText("&Cancel");
    auto buton_stergere = new QPushButton;
    buton_stergere->setText("&Stergere");
    auto buton_exit = new QPushButton;
    buton_exit->setText("&Exit");
    auto layout_butoane = new QHBoxLayout;
    layout_butoane->addWidget(buton_salvare);
    layout_butoane->addWidget(buton_modificare);
    layout_butoane->addWidget(buton_stergere);
    this->layout_dreapta->addLayout(layout_butoane);
    auto layout_butoane_jos = new QHBoxLayout;
    layout_butoane_jos->addWidget(buton_cancel);
    layout_butoane_jos->addWidget(buton_exit);
    this->layout_dreapta->addLayout(layout_butoane_jos);
}

void Fereastra::incarca_lista() {
    auto lista_discipline = new QListWidget;
    auto denumire = new QLabel;
    denumire->setText("Lista discipline");
    denumire->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    auto font_lista = new QFont;
    font_lista->setStyleHint(QFont::Decorative);
    font_lista->setBold(true);
    denumire->setFont(*font_lista);
    this->layout_stanga->addWidget(denumire);
    this->layout_stanga->addWidget(lista_discipline);
    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
        auto denumire_disciplina = QString::fromStdString(it->get_denumire());
        auto list_item = new QListWidgetItem();
        list_item->setText(denumire_disciplina);
        lista_discipline->addItem(list_item);
    }
}

void Fereastra::initializare() {
    this->layout_principal = new QHBoxLayout;
    this->layout_stanga = new QVBoxLayout;
    this->layout_dreapta = new QVBoxLayout;
    this->setLayout(this->layout_principal);
    this->layout_principal->addLayout(this->layout_stanga);
    this->layout_principal->addLayout(this->layout_dreapta);
    this->incarca_lista();
    this->formular();

//    auto buton_adauga = new QPushButton("Adauga");
//    vlay->addWidget(buton_adauga);
//    auto lista_discipline = new QListView();
//    auto alta_lista_disc = new QStringListModel();
//    auto afisare = new QWidget;
////    auto ceva = new QList<std::string>;
////    auto ceva = new QListWidgetItem();
////    auto ceva2 = new QListWidgetItem();
////    auto ceva3 = new QListWidgetItem();
////    ceva->setText("oda ");
////    ceva2->setText("THE MOTANS");
////    ceva3->setText("pax ");
//    auto lista_discipline_afisare = new QListWidget();              ///aici pun la final denumirile
////    lista_discipline_afisare->addItem(ceva);
////    lista_discipline_afisare->addItem(ceva2);
////    lista_discipline_afisare->addItem(ceva3);
////    m_listWidget->append("ceva");
////    m_listWidget->append("ceva");
////    lista_discipline->addScrollBarWidget(main, );
////    QStringListModel m;
////    QStringList data = QStringList()<<"AAA"<<"BBB"<<"CCC";
////    m.setStringList(data);
////    lv->setModel(&m);
////    lv->show();
//    auto tabel_discipline = new QTableWidget();
//    tabel_discipline->setColumnCount(5);
//    tabel_discipline->setRowCount(this->serviceDiscipline.get_numar_discipline()+25);
//    tabel_discipline->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
//    tabel_discipline->setHorizontalHeaderItem(2, new QTableWidgetItem("DENUMIRE"));
//    tabel_discipline->setHorizontalHeaderItem(3, new QTableWidgetItem("PROFESOR"));
//    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
//        auto de_afisat = it->get_denumire();
//        auto de_afisat_final = QString::fromStdString(de_afisat);
//        auto list_item = new QListWidgetItem();
//        list_item->setText(de_afisat_final);
//        lista_discipline_afisare->addItem(list_item);
////        lista_discipline->addItem(new QListWidgetItem(de_afisat_final));
//
//    }
//    int rand = 0;
//    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
//        auto nume = QString::fromStdString(it->get_denumire());
//        auto id = to_string(it->get_id());
//        auto prof = QString::fromStdString(it->get_cadru_didactic());
//        rand++;
//        auto nume_tabel = new QTableWidgetItem;
//        nume_tabel->setText(nume);
////        nume_tabel->
//        auto id_tabel = new QTableWidgetItem;
//        id_tabel->setText(QString::fromStdString(id));
//        auto prof_tabel = new QTableWidgetItem;
//        prof_tabel->setText(nume);
//        tabel_discipline->setItem(rand, 1, id_tabel);
//        tabel_discipline->setItem(rand, 2, nume_tabel);
//        tabel_discipline->setItem(rand, 3, prof_tabel);
//    }
//    main->setLayout(hlay);
//    main->show();
//    auto layout_lista = new QListView(lista_discipline);
//    hlay->addWidget(lista_discipline_afisare);
////    hlay->addWidget(tabel_discipline);
//    auto details2 = new QWidget;
//    auto adauga_widget = new QWidget;
//    auto fl = new QFormLayout;
//    adauga_widget->setLayout(fl);
//    auto lbl_ID = new QLabel("ID");
//    auto txtID = new QLineEdit;
//    auto lbl_Denumire = new QLabel("Denumire");
//    auto txtDenum = new QLineEdit;
//    auto lbl_Prof = new QLabel("Profesor");
//    auto txtProf = new QLineEdit;
//    txtProf->setPlaceholderText("INTRODU PROFESOR");
//    auto lbl_tip = new QLabel("Tip");
//    auto txt_tip = new QLineEdit;
//    auto lbl_ore = new QLabel("Numar ore");
//    auto txt_ore = new QLineEdit;
//
//    fl->addRow(lbl_ID, txtID);
//    fl->addRow(lbl_Denumire, txtDenum);
//    fl->addRow(lbl_Prof, txtProf);
//    fl->addRow(lbl_tip, txt_tip);
//    fl->addRow(lbl_ore, txt_ore);
//    hlay->addWidget(adauga_widget);
//    auto store = new QPushButton("Salveaza");
//    hlay->addWidget(store);
//    hlay->addLayout(vlay);
////    auto layout1 = new QVBoxLayout(main);
////    auto lbl1 = new QLabel("Nume", main);
////    lbl1->setLayout(layout1);
////    auto lbl2 = new QLabel("Lista", main);
////    lbl2->setLayout(layout1);
////    auto lista = new QList<int>;
////    lista->push_back(10);
////    lista->push_back(10);
////    lista->push_back(10);
////    main->show();
////    auto panou_st = new QWidget;
////    auto panou_dr = new QWidget;
////    auto label1 = new QLabel("Nume", main);
//////    auto label1 = new QVBoxLayout;
//////    auto label2 = new QVBoxLayout;
////    label1->setLayout(label1)
////    panou_st->setLayout(label1);
////    panou_dr->setLayout(label2);
////    label1->addWidget(new QPushButton{"ceva"});
////    label2->addWidget(new QPushButton{"altceva"});
////    panou_st->show();
////    panou_dr->show();
}


