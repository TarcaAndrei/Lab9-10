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

    QObject::connect(buton_exit, &QPushButton::clicked,[](){
        qDebug() << "Buton exit apasat!";
//        QMessageBox::information(nullptr, "GET HACKED", "GET HACKED");
    });
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

}



