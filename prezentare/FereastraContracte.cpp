//
// Created by Andrei on 09.05.2023.
//

#include "FereastraContracte.h"
#include "../exceptions/erori_app.h"

FereastraContracte::FereastraContracte(ServiceDiscipline &serviceDiscipline1) : serviceDiscipline(serviceDiscipline1) {
    this->initializare();
}

void FereastraContracte::initializare() {
    this->layout_principal = new QHBoxLayout;
    this->layout_mijloc = new QVBoxLayout;
    this->layout_dreapta = new QVBoxLayout;
    this->layout_stanga = new QVBoxLayout;
    this->setLayout(layout_principal);
    this->layout_principal->addLayout(this->layout_stanga);
    this->layout_principal->addLayout(this->layout_mijloc);
    this->layout_principal->addLayout(this->layout_dreapta);
    this->incarca_lista_ani();
    this->formular();
}

void FereastraContracte::incarca_lista_ani() {
    this->lista_contracte = new QListWidget;
    this->lista_contracte->setSelectionMode(QAbstractItemView::SingleSelection);
    auto denumire = new QLabel;
    denumire->setText("Contracte");
    denumire->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    auto font_lista = new QFont;
    font_lista->setStyleHint(QFont::Decorative);
    font_lista->setBold(true);
    denumire->setFont(*font_lista);
//    this->lista_contracte->setBaseSize(5, 6);
    this->lista_contracte->setMaximumWidth(60);
//    this->lista_contracte->setBaseSize(100, 50);
    this->layout_stanga->addWidget(denumire);
    this->layout_stanga->addWidget(this->lista_contracte);
    auto vector_ani = serviceDiscipline.get_ani_contracte();
    for(auto it : vector_ani){
        auto list_item = new QListWidgetItem();
        list_item->setText(QString::fromStdString(to_string(it)));
        this->lista_contracte->addItem(list_item);
    }

    QObject::connect(this->lista_contracte, &QListWidget::itemSelectionChanged, [this](){
        auto sel = this->lista_contracte->selectedItems();
        if(sel.empty()){
            this->clear_fields();
        }
        else{
            auto sel_item = sel.at(0);
            auto anul = sel_item->text().toInt();
            this->an_txt->setText(QString::fromStdString(to_string(anul)));
            this->incarca_lista_contract(anul);
        }
    });



    this->lista_discipline = new QListWidget;
    lista_discipline->setSelectionMode(QAbstractItemView::SingleSelection);
    auto denumire_alta = new QLabel;
    denumire_alta->setText("Lista Discipline");
    denumire_alta->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    font_lista->setStyleHint(QFont::Decorative);
    font_lista->setBold(true);
    denumire_alta->setFont(*font_lista);
    this->layout_mijloc->addWidget(denumire_alta);
    this->layout_mijloc->addWidget(lista_discipline);
}

void FereastraContracte::reload_lista_ani() {
    this->lista_contracte->clear();
    auto vector_ani = serviceDiscipline.get_ani_contracte();
    for(auto it : vector_ani){
        auto list_item = new QListWidgetItem();
        list_item->setText(QString::fromStdString(to_string(it)));
        this->lista_contracte->addItem(list_item);
    }
}

void FereastraContracte::formular() {
    auto formular = new QFormLayout;
    this->layout_dreapta->addLayout(formular);
    auto lbl_an = new QLabel("An");
    auto lbl_den = new QLabel("Denumire");
    auto lbl_fisier = new QLabel("Nume fisier");
    auto lbl_numar = new QLabel("Numar discipline");
    this->an_txt = new QLineEdit;
    this->an_txt->setPlaceholderText("Introdu Anul");
    this->an_txt->setValidator(new QIntValidator());
    this->denumire_txt = new QLineEdit;
    this->denumire_txt->setPlaceholderText("Introdu Denumirea");
    this->file_txt = new QLineEdit;
    this->file_txt->setPlaceholderText("Introdu Numele Fisierulul");
    this->numar_txt = new QLineEdit;
    this->numar_txt->setPlaceholderText("Introdu Numarul de Discipline");
    this->numar_txt->setValidator(new QIntValidator());
    formular->addRow(lbl_an, this->an_txt);
    formular->addRow(lbl_den, this->denumire_txt);
    formular->addRow(lbl_fisier, this->file_txt);
    formular->addRow(lbl_numar, this->numar_txt);
    auto buton_creare = new QPushButton;
    buton_creare->setText("&Creare contract");
    auto buton_adaugare = new QPushButton;
    buton_adaugare->setText("&Adaugare disciplina");
    auto buton_generare = new QPushButton;
    buton_generare->setText("&Generare Contract");
    auto buton_export = new QPushButton;
    buton_export->setText("&Export Contract");
    auto lay_but = new QHBoxLayout;
    auto lay_but2 = new QHBoxLayout;
    this->layout_dreapta->addLayout(lay_but);
    this->layout_dreapta->addLayout(lay_but2);
    lay_but->addWidget(buton_creare);
    lay_but->addWidget(buton_adaugare);
    lay_but2->addWidget(buton_export);
    lay_but2->addWidget(buton_generare);
    QObject::connect(buton_creare, &QPushButton::clicked, [&](){
        try {
            this->serviceDiscipline.creeaza_contract(this->an_txt->text().toInt());
            this->clear_fields();
            this->reload_lista_ani();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_adaugare, &QPushButton::clicked, [&](){
        try {
            auto disc = this->serviceDiscipline.cauta_disciplina(this->denumire_txt->text().toStdString()).front();
            this->serviceDiscipline.adauga_disciplina_contract(this->an_txt->text().toInt(), disc);
            this->clear_fields();
            this->reload_lista_ani();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_export, &QPushButton::clicked, [&](){
        try {
            this->serviceDiscipline.export_contract(this->an_txt->text().toInt(), this->file_txt->text().toStdString());
            this->clear_fields();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_generare, &QPushButton::clicked, [&](){
        if(this->an_txt->text().isEmpty()){
            QMessageBox::information(nullptr, "Eroare", "Nu ai introdus anul!");
            return;
        }
        if(this->numar_txt->text().isEmpty()){
            QMessageBox::information(nullptr, "Eroare", "Nu ai introdus numarul!");
            return;
        }
        try {
            this->serviceDiscipline.autopopulare_contract(this->an_txt->text().toInt(), this->numar_txt->text().toInt());
            this->clear_fields();
            this->reload_lista_ani();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }
    });

}

void FereastraContracte::clear_fields() {
    this->an_txt->clear();
    this->file_txt->clear();
    this->denumire_txt->clear();
    this->numar_txt->clear();
}

void FereastraContracte::incarca_lista_contract(int an) {
    this->lista_discipline->clear();
    for(auto it = this->serviceDiscipline.get_contracte_begin(an); it < this->serviceDiscipline.get_contracte_end(an); it++){
        auto list_item = new QListWidgetItem();
        list_item->setText(QString::fromStdString(it->get_denumire()));
        this->lista_discipline->addItem(list_item);
    }
}
