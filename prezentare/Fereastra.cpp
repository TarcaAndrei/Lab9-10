//
// Created by Andrei on 05.05.2023.
//
#include "Fereastra.h"
#include "../exceptions/erori_app.h"

Fereastra::Fereastra(const ServiceDiscipline& serviceDiscipline1) {
    this->serviceDiscipline = serviceDiscipline1;
    this->initializare();
}

void Fereastra::formular() {
    auto formular_disc = new QFormLayout;
    this->layout_mijloc->addLayout(formular_disc);
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
    auto layout_butoane = new QHBoxLayout;
    layout_butoane->addWidget(buton_salvare);
    layout_butoane->addWidget(buton_modificare);
    layout_butoane->addWidget(buton_stergere);
    this->layout_mijloc->addLayout(layout_butoane);
    auto layout_butoane_jos = new QHBoxLayout;
    layout_butoane_jos->addWidget(buton_cancel);

    this->layout_mijloc->addLayout(layout_butoane_jos);

    QObject::connect(buton_cancel, &QPushButton::clicked, [txt_ore, txt_id, txt_den, txt_prof, txt_tip](){
        txt_ore->clear();
        txt_id->clear();
        txt_den->clear();
        txt_prof->clear();
        txt_tip->clear();
    });

    QObject::connect(buton_salvare, &QPushButton::clicked, [this, txt_ore, txt_id, txt_den, txt_prof, txt_tip](){
        auto id_disciplina = txt_id->text().toInt();
        auto denumire_disciplina = txt_den->text().toStdString();
        auto prof = txt_prof->text().toStdString();
        auto nr_ore = txt_ore->text().toInt();
        auto tip = txt_tip->text().toStdString();

        try{
            this->serviceDiscipline.adauga_disciplina(id_disciplina, denumire_disciplina, nr_ore, tip, prof);
            this->reload_lista();
            txt_ore->clear();
            txt_id->clear();
            txt_den->clear();
            txt_prof->clear();
            txt_tip->clear();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_modificare, &QPushButton::clicked, [this, txt_ore, txt_id, txt_den, txt_prof, txt_tip](){
        auto id_disciplina = txt_id->text().toInt();
        auto denumire_disciplina = txt_den->text().toStdString();
        auto prof = txt_prof->text().toStdString();
        auto nr_ore = txt_ore->text().toInt();
        auto tip = txt_tip->text().toStdString();
//        qDebug() << id_disciplina<<denumire_disciplina<<prof<<nr_ore<<tip;
        try{
            this->serviceDiscipline.modifica_disciplina(id_disciplina, denumire_disciplina, nr_ore, tip, prof);
            this->reload_lista();
            txt_ore->clear();
            txt_id->clear();
            txt_den->clear();
            txt_prof->clear();
            txt_tip->clear();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_stergere, &QPushButton::clicked, [this, txt_ore, txt_id, txt_den, txt_prof, txt_tip](){
        auto id_disciplina = txt_id->text().toInt();
//        qDebug() << id_disciplina;
        try{
            this->serviceDiscipline.sterge_disciplina(id_disciplina);
            this->reload_lista();
            txt_ore->clear();
            txt_id->clear();
            txt_den->clear();
            txt_prof->clear();
            txt_tip->clear();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });
}

void Fereastra::incarca_lista() {
    this->lista_discipline = new QListWidget;
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
//        auto denumire_disciplina = QString::fromStdString(it->get_denumire());
        auto afisare_disciplina = QString::fromStdString(it->get_denumire());
        auto list_item = new QListWidgetItem();
        list_item->setText(afisare_disciplina);
        lista_discipline->addItem(list_item);
    }
}

void Fereastra::initializare() {
    this->layout_principal = new QHBoxLayout;
    this->layout_stanga = new QVBoxLayout;
    this->layout_mijloc = new QVBoxLayout;
    this->layout_dreapta = new QVBoxLayout;
    this->setLayout(this->layout_principal);
    this->layout_principal->addLayout(this->layout_stanga);
    this->layout_principal->addLayout(this->layout_mijloc);
    this->layout_principal->addLayout(this->layout_dreapta);
    this->incarca_lista();
    this->formular();
    this->butoane_generice();

}

void Fereastra::reload_lista() {        //altfel reloadul
    this->lista_discipline->clear();
    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
//        auto denumire_disciplina = QString::fromStdString(it->get_denumire());
        auto afisare_disciplina = QString::fromStdString(it->get_denumire());
        auto list_item = new QListWidgetItem();
        list_item->setText(afisare_disciplina);
        lista_discipline->addItem(list_item);
    }
}

void Fereastra::butoane_generice() {
    auto layout_butoane_dreapta = new QVBoxLayout;
    this->layout_dreapta->addLayout(layout_butoane_dreapta);
    auto buton_undo = new QPushButton;
    buton_undo->setText("&Undo");
    layout_butoane_dreapta->addWidget(buton_undo);
    QObject::connect(buton_undo, &QPushButton::clicked, [&](){
        try {
            this->serviceDiscipline.undo();
            this->reload_lista();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }

    });

    this->butoane_sortari_filtrari(layout_butoane_dreapta);
    auto buton_cos = new QPushButton;
    buton_cos->setText("&Contracte");
    layout_butoane_dreapta->addWidget(buton_cos);
    auto buton_exit = new QPushButton;
    buton_exit->setText("&Exit");
    layout_butoane_dreapta->addWidget(buton_exit);
    QObject::connect(buton_exit, &QPushButton::clicked,[this](){
        qDebug() << "Buton exit apasat!";
//        QMessageBox::information(nullptr, "EXIT", "Aplicatia se va inchide!");
        close();
    });
}

void Fereastra::butoane_sortari_filtrari(QVBoxLayout* layout_butoane) {
    auto buton_sortare_cresc_denumire = new QPushButton;
    buton_sortare_cresc_denumire->setText("&Sortare");
    layout_butoane->addWidget(buton_sortare_cresc_denumire);

    auto lbl = new QLabel;
    lbl->setText("Ceva");
    layout_butoane->addWidget(lbl);
    auto group_box_ord = new QButtonGroup;
    auto layout_check_buttons = new QHBoxLayout;
    layout_butoane->addLayout(layout_check_buttons);
    auto optiune_cresc = new QRadioButton;
    optiune_cresc->setText("&Crescator");
    layout_check_buttons->addWidget(optiune_cresc);
    optiune_cresc->setChecked(true);
    auto optiune_desc = new QRadioButton;
    optiune_desc->setText("&Descrescator");
    optiune_desc->setChecked(false);
    layout_check_buttons->addWidget(optiune_desc);
    group_box_ord->addButton(optiune_cresc);
    group_box_ord->addButton(optiune_desc);


    auto lb2l = new QLabel;
    lb2l->setText("Ceva2");
    layout_butoane->addWidget(lb2l);
    auto group_box_optiuni = new QButtonGroup;
    auto layout_butoane_optiune = new QVBoxLayout;
    layout_butoane->addLayout(layout_butoane_optiune);
    auto optiune_denumire = new QRadioButton;
    optiune_denumire->setText("&Denumire");
    layout_butoane_optiune->addWidget(optiune_denumire);
    optiune_denumire->setChecked(true);
    auto optiune_numar_ore = new QRadioButton;
    optiune_numar_ore->setText("&Numar ore");
    optiune_numar_ore->setChecked(false);
    layout_butoane_optiune->addWidget(optiune_numar_ore);
    auto optiune_cadru = new QRadioButton;
    optiune_cadru->setText("&Cadru didactic");
    optiune_cadru->setChecked(false);
    layout_butoane_optiune->addWidget(optiune_cadru);
    auto optiune_tip = new QRadioButton;
    optiune_tip->setText("&Tip");
    optiune_tip->setChecked(false);
    layout_butoane_optiune->addWidget(optiune_tip);
    group_box_optiuni->addButton(optiune_denumire);
    group_box_optiuni->addButton(optiune_numar_ore);
    group_box_optiuni->addButton(optiune_cadru);
    group_box_optiuni->addButton(optiune_tip);
//    QObject::connect(optiune_cresc, &QRadioButton::clicked, [&](){
//       optiune_desc->setChecked(false);
//    });


//    auto check_box_cresc = new QCheckBox;
//    check_box_cresc->setText("&Crescator");
//    auto check_box_desc = new QCheckBox;
//    check_box_desc->setText("&Descrescator");
//    layout_check_buttons->addWidget(check_box_cresc);
//    check_box_cresc->setCheckState(Qt::CheckState::Checked);
//    layout_check_buttons->addWidget(check_box_desc);
//    check_box_desc->setCheckState(Qt::CheckState::Unchecked);
//
//    QObject::connect(check_box_cresc, &QCheckBox::stateChanged, [](){
//
//    });
}



