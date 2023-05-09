//
// Created by Andrei on 05.05.2023.
//
#include "Fereastra.h"
#include "../exceptions/erori_app.h"
#include "../vector/Iterator.h"
#include "FereastraContracte.h"

Fereastra::Fereastra(const ServiceDiscipline& serviceDiscipline1) {
    this->serviceDiscipline = serviceDiscipline1;
//    this->serviceDiscipline.autopopulare();
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
    this->txt_id = new QLineEdit;
    txt_id->setPlaceholderText("Introdu ID");
    txt_id->setValidator(new QIntValidator());
    this->txt_den = new QLineEdit;
    txt_den->setPlaceholderText("Introdu Denumirea");
    this->txt_tip = new QLineEdit;
    txt_tip->setPlaceholderText("Introdu Tipul");
    this->txt_prof = new QLineEdit;
    txt_prof->setPlaceholderText("Introdu Profesorul");
    this->txt_ore = new QLineEdit;
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

    QObject::connect(buton_cancel, &QPushButton::clicked, [this](){
        this->clear_fields();
        this->reload_lista();
    });

    QObject::connect(buton_salvare, &QPushButton::clicked, [this](){
        auto id_disciplina = txt_id->text().toInt();
        auto denumire_disciplina = txt_den->text().toStdString();
        auto prof = txt_prof->text().toStdString();
        auto nr_ore = txt_ore->text().toInt();
        auto tip = txt_tip->text().toStdString();

        try{
            this->serviceDiscipline.adauga_disciplina(id_disciplina, denumire_disciplina, nr_ore, tip, prof);
            this->reload_lista();
            this->clear_fields();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_modificare, &QPushButton::clicked, [this](){
        auto id_disciplina = txt_id->text().toInt();
        auto denumire_disciplina = txt_den->text().toStdString();
        auto prof = txt_prof->text().toStdString();
        auto nr_ore = txt_ore->text().toInt();
        auto tip = txt_tip->text().toStdString();
//        qDebug() << id_disciplina<<denumire_disciplina<<prof<<nr_ore<<tip;
        try{
            this->serviceDiscipline.modifica_disciplina(id_disciplina, denumire_disciplina, nr_ore, tip, prof);
            this->reload_lista();
            this->clear_fields();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(buton_stergere, &QPushButton::clicked, [this](){
        auto id_disciplina = txt_id->text().toInt();
//        qDebug() << id_disciplina;
        try{
            this->serviceDiscipline.sterge_disciplina(id_disciplina);
            this->reload_lista();
            this->clear_fields();
        }
        catch (erori_app &e){
            QMessageBox::information(nullptr, "EROARE", QString::fromStdString(e.what()));
        }
    });

    auto buton_undo = new QPushButton;
    buton_undo->setText("&Undo");
    this->layout_mijloc->addWidget(buton_undo);
    QObject::connect(buton_undo, &QPushButton::clicked, [&](){
        try {
            this->serviceDiscipline.undo();
            this->reload_lista();
        }
        catch(erori_app &e){
            QMessageBox::information(nullptr, "Eroare", QString::fromStdString(e.what()));
        }

    });

    QObject::connect(this->lista_discipline, &QListWidget::itemSelectionChanged, [this](){
        auto sel = this->lista_discipline->selectedItems();
        if(sel.empty()){
            this->clear_fields();
        }
        else{
            auto sel_item = sel.at(0);
//            qDebug()<<sel_item->data(Qt::UserRole)<<' '<<sel_item->text();
            auto idk = sel_item->data(Qt::UserRole);
            auto id_disc = idk.toInt();
//            qDebug()<<"ceva";
            auto disciplina = this->serviceDiscipline.get_disciplina_id_srv(id_disc);
//            qDebug()<<"ceva";
            txt_id->setText(QString::fromStdString(to_string(disciplina.get_id())));
//            qDebug()<<"ceva";
            txt_ore->setText(QString::fromStdString(to_string(disciplina.get_ore_pe_saptamana())));
            txt_den->setText(QString::fromStdString(disciplina.get_denumire()));
            txt_tip->setText(QString::fromStdString(disciplina.get_tip()));
            txt_prof->setText(QString::fromStdString(disciplina.get_cadru_didactic()));
        }
//        qDebug()<<"Selectie modificata";
    });
}

void Fereastra::incarca_lista() {
    this->lista_discipline = new QListWidget;
    this->lista_discipline->setSelectionMode(QAbstractItemView::SingleSelection);
    auto denumire = new QLabel;
    denumire->setText("Lista discipline");
    denumire->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    auto font_lista = new QFont;
    font_lista->setStyleHint(QFont::Decorative);
    font_lista->setBold(true);
    denumire->setFont(*font_lista);
    this->layout_stanga->addWidget(denumire);
    this->layout_stanga->addWidget(lista_discipline);
//    this->lista_discipline->setItemAlignment(Qt::Alignment::enum_type::AlignCenter);
    for(auto it = this->serviceDiscipline.get_discipline_begin(); it< this->serviceDiscipline.get_discipline_end(); it++){
//        auto denumire_disciplina = QString::fromStdString(it->get_denumire());
        auto afisare_disciplina = QString::fromStdString(it->get_denumire());
        auto list_item = new QListWidgetItem();
        list_item->setText(afisare_disciplina);
        list_item->setData(Qt::UserRole, it->get_id());
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
        list_item->setData(Qt::UserRole, it->get_id());
        list_item->setText(afisare_disciplina);
        lista_discipline->addItem(list_item);
    }
}

void Fereastra::butoane_generice() {
    auto layout_butoane_dreapta = new QVBoxLayout;
    this->layout_dreapta->addLayout(layout_butoane_dreapta);

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

    QObject::connect(buton_cos, &QPushButton::clicked, [this](){
        //aloc pe heap noua clasa si ii dau show
        auto contracte_window = new FereastraContracte(this->serviceDiscipline);
        contracte_window->show();
    });
}

void Fereastra::butoane_sortari_filtrari(QVBoxLayout* layout_butoane) {
//    std::unordered_map<char, QRadioButton*> lista_butoane_optiuni;
    QMap<char, QRadioButton*> lista_butoane_optiuni;
    QMap<char, QRadioButton*> lista_butoane_ordine;
    auto lbl = new QLabel;
    lbl->setText("Ordine Sortare");
    layout_butoane->addWidget(lbl);
    auto group_box_ord = new QButtonGroup;
    auto layout_check_buttons = new QHBoxLayout;
    layout_butoane->addLayout(layout_check_buttons);
    auto optiune_cresc = new QRadioButton;
    optiune_cresc->setText("&Crescator");
    layout_check_buttons->addWidget(optiune_cresc);
    optiune_cresc->setChecked(true);
    lista_butoane_ordine['+'] = optiune_cresc;
    auto optiune_desc = new QRadioButton;
    optiune_desc->setText("&Descrescator");
    optiune_desc->setChecked(false);
    lista_butoane_ordine['-'] = optiune_desc;
    layout_check_buttons->addWidget(optiune_desc);
    group_box_ord->addButton(optiune_cresc);
    group_box_ord->addButton(optiune_desc);


    auto lb2l = new QLabel;
    lb2l->setText("Tip sortare");
    layout_butoane->addWidget(lb2l);
    auto group_box_optiuni = new QButtonGroup;
    auto layout_butoane_optiune = new QVBoxLayout;
    auto layout_butoane_optiune1 = new QHBoxLayout;
    auto layout_butoane_optiune2 = new QHBoxLayout;
    layout_butoane_optiune->addLayout(layout_butoane_optiune1);
    layout_butoane_optiune->addLayout(layout_butoane_optiune2);
    layout_butoane->addLayout(layout_butoane_optiune);
    auto optiune_denumire = new QRadioButton;
    optiune_denumire->setText("&Denumire");
    layout_butoane_optiune1->addWidget(optiune_denumire);
    optiune_denumire->setChecked(true);
    lista_butoane_optiuni['1'] = optiune_denumire;
    auto optiune_numar_ore = new QRadioButton;
    optiune_numar_ore->setText("&Numar ore");
    optiune_numar_ore->setChecked(false);
    layout_butoane_optiune1->addWidget(optiune_numar_ore);
    lista_butoane_optiuni['2'] = optiune_numar_ore;
    auto optiune_cadru = new QRadioButton;
    optiune_cadru->setText("&Cadru didactic");
    optiune_cadru->setChecked(false);
    layout_butoane_optiune2->addWidget(optiune_cadru);
    lista_butoane_optiuni['3'] = optiune_cadru;
    auto optiune_tip = new QRadioButton;
    optiune_tip->setText("&Tip");
    optiune_tip->setChecked(false);
    lista_butoane_optiuni['4'] = optiune_tip;
    layout_butoane_optiune2->addWidget(optiune_tip);
    group_box_optiuni->addButton(optiune_denumire);
    group_box_optiuni->addButton(optiune_numar_ore);
    group_box_optiuni->addButton(optiune_cadru);
    group_box_optiuni->addButton(optiune_tip);

    auto buton_sortare = new QPushButton;
    buton_sortare->setText("&Sortare");
    layout_butoane->addWidget(buton_sortare);

    QObject::connect(buton_sortare, &QPushButton::clicked, [=](){
        auto comanda = ' ';
        for(auto it = lista_butoane_optiuni.constKeyValueBegin(); it != lista_butoane_optiuni.constKeyValueEnd(); it++){
            if(it->second->isChecked()){
                comanda = it->first;
//                qDebug()<<comanda;
            }
        }
        auto ordine = ' ';
        for(auto it = lista_butoane_ordine.constKeyValueBegin(); it != lista_butoane_ordine.constKeyValueEnd(); it++){
            if(it->second->isChecked()){
                ordine = it->first;
//                qDebug()<<ordine;
            }
        }
        auto vector_final = this->serviceDiscipline.sortare_discipline(comanda, ordine);
        this->lista_discipline->clear();
        for(auto it = vector_final.begin(); it < it.end(); it++){
//        auto denumire_disciplina = QString::fromStdString(it->get_denumire());
            auto afisare_disciplina = QString::fromStdString((*it).get_denumire());
            auto list_item = new QListWidgetItem();
            list_item->setData(Qt::UserRole, (*it).get_id());
            list_item->setText(afisare_disciplina);
            lista_discipline->addItem(list_item);
        }
    });
    auto butoane_filtr = new QHBoxLayout;

    auto buton_filtrare_cadru = new QPushButton;
    buton_filtrare_cadru->setText("&Filtrare Cadru Didactic");
    auto buton_filtrare_ore_cresc = new QPushButton;
    auto buton_filtrare_ore_desc = new QPushButton;
    buton_filtrare_ore_cresc->setText("&Filtrare Ore +");
    buton_filtrare_ore_desc->setText("&Filtrare Ore -");

    butoane_filtr->addWidget(buton_filtrare_cadru);
    butoane_filtr->addWidget(buton_filtrare_ore_cresc);
    butoane_filtr->addWidget(buton_filtrare_ore_desc);
    layout_butoane->addLayout(butoane_filtr);

    QObject::connect(buton_filtrare_cadru, &QPushButton::clicked, [&](){
        if(this->txt_id->text().isEmpty()){
            return;
        }
        auto lista = this->serviceDiscipline.filtrare_disciplina(this->txt_id->text().toInt(), this->txt_prof->text().toStdString(), '3');
        this->reload_lista();
        for(const auto& it : lista){
            auto id_disc = it.get_id();
            for(auto i = 0; i < this->lista_discipline->count(); ++i){
                auto item = this->lista_discipline->item(i);
                if(item->data(Qt::UserRole).toInt() == id_disc){
                    this->lista_discipline->item(i)->setBackground(QBrush{Qt::darkGreen});
                }
            }
        }
    });
    QObject::connect(buton_filtrare_ore_desc, &QPushButton::clicked, [&](){
        if(this->txt_id->text().isEmpty()){
            return;
        }
        auto lista = this->serviceDiscipline.filtrare_disciplina(this->txt_ore->text().toInt(), this->txt_prof->text().toStdString(), '2');
        this->reload_lista();
        for(const auto& it : lista){
            auto id_disc = it.get_id();
            for(auto i = 0; i < this->lista_discipline->count(); ++i){
                auto item = this->lista_discipline->item(i);
                if(item->data(Qt::UserRole).toInt() == id_disc){
                    this->lista_discipline->item(i)->setBackground(QBrush{Qt::darkGreen});
                }
            }
        }
    });
    QObject::connect(buton_filtrare_ore_cresc, &QPushButton::clicked, [&](){
        if(this->txt_id->text().isEmpty()){
            return;
        }
        auto lista = this->serviceDiscipline.filtrare_disciplina(this->txt_ore->text().toInt(), this->txt_prof->text().toStdString(), '1');
        this->reload_lista();
        for(const auto& it : lista){
            auto id_disc = it.get_id();
            for(auto i = 0; i < this->lista_discipline->count(); ++i){
                auto item = this->lista_discipline->item(i);
                if(item->data(Qt::UserRole).toInt() == id_disc){
                    this->lista_discipline->item(i)->setBackground(QBrush{Qt::darkGreen});
                }
            }
        }
    });
}

void Fereastra::clear_fields() {
    this->txt_ore->clear();
    this->txt_id->clear();
    this->txt_den->clear();
    this->txt_prof->clear();
    this->txt_tip->clear();
}


