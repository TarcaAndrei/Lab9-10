//
// Created by Andrei on 02.04.2023.
//

#include "Consola.h"
#include "../vector/Iterator.h"
#include "../exceptions/erori_app.h"
#include<iostream>
#include <utility>
#include <string>


Consola::Consola(const ServiceDiscipline& serviceDiscipline) {
    this->serviceDiscipline = std::move(serviceDiscipline);
}

void Consola::run() {
    std::cout<<"Salut!\nBine ai venit la aplicatia de gestiune a contractelor de studii\n";
    while(true){
        std::cout<<"Introdu una dintre comenzile de mai jos:\n";
        std::cout<<"1. Afisarea disciplinelor\n";
        std::cout<<"2. Adaugarea unei noi discipline\n";
        std::cout<<"3. Modificarea unei discipline\n";
        std::cout<<"4. Stergerea unei discipline\n";
        std::cout<<"5. Cautare disciplina\n";
        std::cout<<"6. Filtrare discipline\n";
        std::cout<<"7. Sortare discipline\n";
        std::cout<<"8. Autopopulare\n";
        std::cout<<"9. Contracte de studiu\n";
        std::cout<<"U. Undo\n";
        std::cout<<"Q. Iesire\n";
        std::cout<<">>>";
        char comanda;
        char comanda_brut[10];
        fgets(comanda_brut, 5, stdin);
        comanda = comanda_brut[0];
        switch (comanda) {
            case '1':
                this->afisare_discipline();
                break;
            case '2':
                this->adauga_disciplina();
                break;
            case '3':
                this->modificare_disciplina();
                break;
            case '4':
                this->stergere_disciplina();
                break;
            case '5':
                this->cautare_disciplina();
                break;
            case '6':
                this->filtrare_disciplina();
                break;
            case '7':
                this->sortare_discipline();
                break;
            case '8':
                this->autopopulare();
                break;
            case '9':
                this->app_contracte();
                break;
            case 'u':
                this->undo();
                break;
            case 'U':
                this->undo();
                break;
            case 'Q':                       /// aici de gandit un submeniul la consola...poate o alta clasa de consola?
                return;
            case 'q':
                return;
            case '\n':
                break;
            default:
                cout<<"Comanda invalida!\n";
                break;
        }
    }
}

void Consola::afisare_numar_discipline() {
    std::cout<<"Numarul de discipline este: "<<serviceDiscipline.get_numar_discipline()<<'\n';
}

void Consola::afisare_discipline() {
    if(serviceDiscipline.get_numar_discipline() == 0){
        cout<<"Lista de discipline este vida!\n";
        return;
    }
    this->afisare_cap_tabel();
    for(auto iterator = serviceDiscipline.get_discipline_begin(); iterator < serviceDiscipline.get_discipline_end(); iterator++){
        std::cout<<(*iterator).afisare_disciplina();
        this->afisare_delimitator_linie();
        std::cout<<'\n';
    }
}

int transform_string_to_int(string ceva){
    int numar = 0;
    int p = 1;
    char l;
    while(ceva.length() > 0){
        l = ceva[ceva.length()-1];
        l = l - '0';
        if(l < 0 or l > 9){
            throw ui_error("Numarul trebuie sa fie natural!");
        }
        numar = numar + l * p;
        p = p * 10;
        ceva.pop_back();
    }
    return numar;
}

string strip_string(string buff){
    //ceva idk...
    if(buff.empty())
        return "";
    string dest;
    int j = 0;
    unsigned long i = buff.length() - 1;
    unsigned long k;
    int ok = 1;
    while(i > 0 && ok){
        if(buff[i] == '\n' || buff[i] == ' ' || buff[i]=='\t'){
            --i;               //should work i guess
        }
        else{
            ok = 0;
        }
    }
    k = i;
    i = 0;
    ok = 1;
    while(i <= k && ok){
        if(buff[i] == '\n' || buff[i] == ' ' || buff[i]=='\t'){
            ++i;               //should work i guess
        }
        else{
            ok = 0;
        }
    }
    while (i <= k){
        dest += buff[i];
        ++i;
    }
    return dest;
}

void Consola::adauga_disciplina() {
    int id_disc, nr_ore_disc;
    bool ok = false;
    std::string str_id_disc, str_nr_disc;
    std::string denumire_disc, cadru_disc, tip_disc;
    while(not ok) {
        std::cout << "Introdu ID:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << e.what() <<'\n';
            ok = false;
        }
    }
    ok = false;
    while(not ok) {
        std::cout << "Introdu denumirea:";
        std::getline(std::cin, denumire_disc);
        denumire_disc = strip_string(denumire_disc);
        try{
            this->serviceDiscipline.validatorDisciplina.ValidareDenumire(denumire_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << e.what() <<'\n';
            ok = false;
        }
    }
    ok = false;
    while(not ok) {
        std::cout << "Introdu cadrul didactic:";
        std::getline(std::cin, cadru_disc);
        cadru_disc = strip_string(cadru_disc);
        try{
            this->serviceDiscipline.validatorDisciplina.ValidareCadruDidactic(cadru_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << e.what() <<'\n';
            ok = false;
        }
    }
    ok = false;
    while(not ok) {
        std::cout << "Introdu tipul:";
        std::getline(std::cin, tip_disc);
        tip_disc = strip_string(tip_disc);
        try{
            this->serviceDiscipline.validatorDisciplina.ValidareTip(tip_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << e.what() <<'\n';
            ok = false;
        }
    }
    ok = false;
    while(not ok) {
        std::cout << "Introdu numarul de ore:";
        std::getline(std::cin, str_nr_disc);
        str_nr_disc = strip_string(str_nr_disc);
        try {
            nr_ore_disc = transform_string_to_int(str_nr_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareOre(nr_ore_disc);
            ok = true;
        }
        catch (erori_app &e) {
                std::cout << e.what() <<'\n';
                ok = false;
            }
        }
    try {
        serviceDiscipline.adauga_disciplina(id_disc, denumire_disc, nr_ore_disc, tip_disc, cadru_disc);
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
        return;
    }
    std::cout<<"Disciplina adaugata cu succes!\n";
}

void Consola::stergere_disciplina() {
    int id_disc;
    std::string str_id_disc;
    std::string denumire_disc, cadru_disc, tip_disc;
    std::cout<<"Introdu ID:";
    std::getline(std::cin, str_id_disc);
    str_id_disc = strip_string(str_id_disc);
    try{
        id_disc = transform_string_to_int(str_id_disc);
    }
    catch (...){
        std::cout<<"ID-ul trebuie sa fie natural!\n";
        return;
    }
    try {
        serviceDiscipline.sterge_disciplina(id_disc);
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
        return;
    }
    std::cout<<"Disciplina stearsa cu succes!\n";
}

void Consola::modificare_disciplina() {
    int id_disc, nr_ore_disc;
    std::string str_id_disc, str_nr_disc;
    std::string denumire_disc, cadru_disc, tip_disc;
    std::cout<<"Introdu ID:";
    std::getline(std::cin, str_id_disc);
    str_id_disc = strip_string(str_id_disc);
    try{
        id_disc = transform_string_to_int(str_id_disc);
    }
    catch (...){
        std::cout<<"ID-ul trebuie sa fie natural!\n";
        return;
    }
    std::cout<<"Introdu denumirea:";
    std::getline(std::cin, denumire_disc);
    denumire_disc = strip_string(denumire_disc);
    std::cout<<"Introdu cadrul didactic:";
    std::getline(std::cin, cadru_disc);
    cadru_disc = strip_string(cadru_disc);
    std::cout<<"Introdu tipul:";
    std::getline(std::cin, tip_disc);
    tip_disc = strip_string(tip_disc);
    std::cout<<"Introdu numarul de ore:";
    std::getline(std::cin, str_nr_disc);
    str_nr_disc = strip_string(str_nr_disc);
    try{
        nr_ore_disc = transform_string_to_int(str_nr_disc);
    }
    catch (...){
        std::cout<<"Numarul de ore trebuie sa fie natural!\n";
        return;
    }
    try {
        serviceDiscipline.modifica_disciplina(id_disc, denumire_disc, nr_ore_disc, tip_disc, cadru_disc);
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
        return;
    }
    std::cout<<"Disciplina modificata cu succes!\n";
}

void Consola::afisare_cap_tabel() {
    this->afisare_delimitator_linie();
    printf("\n");
    printf("|");
    for(int j=0; j<3; j++)
        printf(" ");
    printf("ID");
    for(int j=0; j<3; j++)
        printf(" ");
    printf("|");
    for(int j=0; j<11; j++)
        printf(" ");
    printf("DENUMIRE");
    for(int j=0; j<11; j++)
        printf(" ");
    printf("|");
    for(int j=0; j<8; j++)
        printf(" ");
    printf("CADRU DIDACTIC");
    for(int j=0; j<8; j++)
        printf(" ");
    printf("|");
    for(int j=0; j<8; j++)
        printf(" ");
    printf("TIP");
    for(int j=0; j<8; j++)
        printf(" ");
    printf("|");
    for(int j=0; j<3; j++)
        printf(" ");
    printf("NUMAR ORE");
    for(int j=0; j<3; j++)
        printf(" ");
    printf("|");
    printf("\n");
    this->afisare_delimitator_linie();
    printf("\n");
}

void Consola::afisare_delimitator_linie() {
    printf("+");
    for(int j=0; j<8; j++)
        printf("-");
    printf("+");
    for(int j=0; j<30; j++)
        printf("-");
    printf("+");
    for(int j=0; j<30; j++)
        printf("-");
    printf("+");
    for(int j=0; j<19; j++)
        printf("-");
    printf("+");
    for(int j=0; j<15; j++)
        printf("-");
    printf("+");
}

void Consola::cautare_disciplina() {
    string denumire_disc;
    std::cout<<"Introdu denumirea dupa care cauti:";
    std::getline(std::cin, denumire_disc);
    denumire_disc = strip_string(denumire_disc);
    auto dictionar = this->serviceDiscipline.cauta_disciplina(denumire_disc);
    std::cout<<'\n';
    this->afisare_cap_tabel();
    for(auto iterator = dictionar.begin(); iterator < dictionar.end(); iterator++){
        std::cout<<(*iterator).afisare_disciplina();
        this->afisare_delimitator_linie();
        std::cout<<'\n';
    }
}

void Consola::autopopulare() {
    this->serviceDiscipline.autopopulare();
    cout<<"Lista de discipline a fost autopopulata cu succes!\n";
}

void Consola::filtrare_disciplina() {
    string denumire_disc;
    string str_id_disc;
    int numar = 0;
    char comanda;
    char comanda_brut[10];
    std::cout<<"Introdu optiunea pe care o doresti:\n";
    std::cout<<"1 - filtrare discipline cu mai multe ore decat cea introdusa\n";
    std::cout<<"2 - filtrare discipline cu mai putine ore decat cea introdusa\n";
    std::cout<<"3 - filtrare cadru didactic\n";
    fgets(comanda_brut, 5, stdin);
    comanda = comanda_brut[0];
    if(comanda == '1' or comanda == '2' or comanda == '3'){
        if(comanda == '3') {
            std::cout << "Introdu cadrul didactic dupa care cauti:";
            std::getline(std::cin, denumire_disc);
            denumire_disc = strip_string(denumire_disc);
        }else{
            std::cout<<"Introdu numarul de ore:";
            std::getline(std::cin, str_id_disc);
            str_id_disc = strip_string(str_id_disc);
            try{
                numar = transform_string_to_int(str_id_disc);
            }
            catch (...){
                std::cout<<"ID-ul trebuie sa fie natural!\n";
                return;
            }
        }
    }
    else{
        std::cout<<"Nu ai introdus o optiune valida!\n";
        return;
    }
    auto dictionar = this->serviceDiscipline.filtrare_disciplina(numar, denumire_disc, comanda);
    std::cout<<'\n';
    this->afisare_cap_tabel();
    for(auto iterator = dictionar.begin(); iterator < dictionar.end(); iterator++){
        std::cout<<(*iterator).afisare_disciplina();
        this->afisare_delimitator_linie();
        std::cout<<'\n';
    }
}

void Consola::sortare_discipline() {
    char comanda;
    char ordine;
    char comanda_brut[10];
    std::cout<<"Introdu optiunea pe care o doresti:\n";
    std::cout<<"1 - sortare dupa denumire\n";
    std::cout<<"2 - sortare dupa numarul de ore\n";
    std::cout<<"3 - sortare dupa cadrul didactic\n";
    std::cout<<"4 - sortare dupa tip\n";
    fgets(comanda_brut, 5, stdin);
    comanda = comanda_brut[0];
    if(comanda == '1' or comanda == '2' or comanda == '3' or comanda == '4'){
        std::cout<<"Introdu '+' pentru sortare crescatoare sau '-' pentru descrescatoare\n";
        fgets(comanda_brut, 5, stdin);
        ordine = comanda_brut[0];
        if(ordine == '+' or ordine == '-') {
            auto vector_final = this->serviceDiscipline.sortare_discipline(comanda, ordine);
            std::cout<<'\n';
            this->afisare_cap_tabel();
            for(auto iterator = vector_final.begin(); iterator < iterator.end(); iterator++){
                std::cout<<(*iterator).afisare_disciplina();
                this->afisare_delimitator_linie();
                std::cout<<'\n';
            }
        }
        else{
            std::cout<<"Nu ai introdus o optiune valida!\n";
            return;
        }
    }
    else{
        std::cout<<"Nu ai introdus o optiune valida!\n";
        return;
    }
}

void Consola::afisare_contracte() {
    if(this->serviceDiscipline.get_numar_contracte() == 0){
        std::cout<<"Nu exista niciun contract!\n";
        return;
    }
    std::cout<<"Exista contracte pentru anii:\n";
    auto lista = this->serviceDiscipline.get_ani_contracte();
    for(auto item : lista){
        std::cout<<item<<'\t';
    }
    std::cout<<'\n';
}

void Consola::creare_contract() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    try{
        this->serviceDiscipline.creeaza_contract(id_disc);
        std::cout<<"Contract creat cu succes!\n";
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

void Consola::app_contracte() {
    std::cout<<"Acum te afli in submeniul cu gestiunea contractelor\n";
    while (true) {
        std::cout << "Introdu una dintre comenzile de mai jos:\n";
        std::cout << "1. Afisarea anilor pentru care exista un contract\n";
        std::cout << "2. Afisarea disciplinelor dintr-un contract\n";
        std::cout << "3. Crearea unui contract nou\n";
        std::cout << "4. Adaugarea unei discipline intr-un contract\n";
        std::cout << "5. Generarea unui contract nou\n";
        std::cout << "6. Golirea unui contract\n";
        std::cout << "7. Exportul unui contract\n";
        std::cout << "Q. Iesire\n";
        std::cout << ">>>";
        char comanda;
        char comanda_brut[10];
        fgets(comanda_brut, 5, stdin);
        comanda = comanda_brut[0];
        switch (comanda) {
            case '1':
                this->afisare_contracte();
                break;
            case '2':
                this->afisare_discipline_contract();
                break;
            case '3':
                this->creare_contract();
                break;
            case '4':
                this->adaugare_disciplina_contract();
                break;
            case '5':
                this->generare_contract_nou();
                break;
            case '6':
                this->golirea_unui_contract();
                break;
            case '7':
                this->exportul_unui_contract();
                break;
            case 'Q':
                return;
            case 'q':
                return;
            case '\n':
                break;
            default:
                cout<<"Comanda invalida!\n";
                break;
        }
    }
}

void Consola::afisare_discipline_contract() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    auto an_contract = id_disc;
    try{
        int a = 0;
        for(auto ceva = this->serviceDiscipline.get_contracte_begin(an_contract); ceva < this->serviceDiscipline.get_contracte_end(an_contract); ++ceva){
            a++;
            break;
        }
        if(a == 0){
            std::cout<<"Nu exista nicio disciplina in acest contract inca!\n";
            return;
        }
        this->afisare_cap_tabel();
        auto it = this->serviceDiscipline.get_contracte_begin(an_contract);
        for(it; it < this->serviceDiscipline.get_contracte_end(an_contract); ++it){
            std::cout<<it->afisare_disciplina();
            this->afisare_delimitator_linie();
            std::cout<<'\n';
        }
        std::cout<<"Numarul de discipline din contract este: "<< this->serviceDiscipline.get_numar_elemente_contract(an_contract)<<'\n';
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

void Consola::adaugare_disciplina_contract() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    auto an_contract = id_disc;
    std::string denumire_disc;
    ok = false;
    while(not ok) {
        std::cout << "Introdu denumirea:";
        std::getline(std::cin, denumire_disc);
        denumire_disc = strip_string(denumire_disc);
        try{
            this->serviceDiscipline.validatorDisciplina.ValidareDenumire(denumire_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << e.what() <<'\n';
            ok = false;
        }
    }
    auto vector_discipline = this->serviceDiscipline.cauta_disciplina(denumire_disc);
    if(vector_discipline.empty()){
        std::cout<<"Nu a fost gasita nicio disciplina cu acest nume!\n";
        return;
    }
    else if(vector_discipline.size() == 1){
        auto disc = vector_discipline[0];
        try{
            this->serviceDiscipline.adauga_disciplina_contract(an_contract, disc);
            std::cout<<"Disciplina adaugata cu succes!\n";
            std::cout<<"Numarul de discipline din contract este: "<< this->serviceDiscipline.get_numar_elemente_contract(an_contract)<<'\n';
        }
        catch (erori_app &e){
            std::cout<<e.what()<<'\n';
        }
    }
    else{
        std::cout<<"Am gasit mai multe discipline cu acest nume:\n";
        this->afisare_cap_tabel();
        for(auto item : vector_discipline){
            std::cout<<item.afisare_disciplina();
            this->afisare_delimitator_linie();
            std::cout<<'\n';
        }
        std::cout<<"Te rugam alege care care dintre discipline doresti s-o alegi prin indicarea pozitiei acesteia:\n";
        ok = false;
        while(not ok) {
            std::cout<<">>>";
            std::getline(std::cin, str_id_disc);
            str_id_disc = strip_string(str_id_disc);
            try {
                id_disc = transform_string_to_int(str_id_disc);
                if(1 <= id_disc and id_disc <= vector_discipline.size()) {
                    ok = true;
                }
                else{
                    std::cout << "Pozitie invalida!" <<'\n';
                    ok = false;
                }
            }
            catch (erori_app &e) {
                std::cout << "Pozitie invalida!" <<'\n';
                ok = false;
            }
        }
        auto disc = vector_discipline[id_disc-1];
        try{
            this->serviceDiscipline.adauga_disciplina_contract(an_contract, disc);
            std::cout<<"Disciplina adaugata cu succes!\n";
            std::cout<<"Numarul de discipline din contract este: "<< this->serviceDiscipline.get_numar_elemente_contract(an_contract)<<'\n';
        }
        catch (erori_app &e){
            std::cout<<e.what()<<'\n';
            //std::cout<<"Numarul de discipline din contract este: "<< this->serviceDiscipline.get_numar_elemente_contract(an_contract)<<'\n';
        }
    }
}

void Consola::golirea_unui_contract() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    auto an_contract = id_disc;
    try{
        this->serviceDiscipline.goleste_contract(an_contract);
        std::cout<<"Contract golit cu succes!\n";
        std::cout<<"Numarul de discipline din contract este: "<< this->serviceDiscipline.get_numar_elemente_contract(an_contract)<<'\n';
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

void Consola::exportul_unui_contract() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    auto an_contract = id_disc;
    std::string denumire_disc;
    ok = false;
    std::cout << "Introdu numele fisierului:";
    while(not ok) {
        std::cout<<">>>";
        std::getline(std::cin, denumire_disc);
        denumire_disc = strip_string(denumire_disc);
        if(not denumire_disc.empty())
            ok = true;
        else{
            std::cout<<"Nume fisier invalid!\n";
        }
    }
    auto nume_fisier = denumire_disc;
    try{
        this->serviceDiscipline.export_contract(an_contract, nume_fisier);
        std::cout<<"Contractul a fost exportat cu succes in folderul dedicat!\n";
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

void Consola::generare_contract_nou() {
    bool ok = false;
    string str_id_disc;
    int id_disc;
    while(not ok) {
        std::cout << "Introdu anul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "An invalid!" <<'\n';
            ok = false;
        }
    }
    auto an_contract = id_disc;
    ok = false;
    while(not ok) {
        std::cout << "Introdu numarul:";
        std::getline(std::cin, str_id_disc);
        str_id_disc = strip_string(str_id_disc);
        try {
            id_disc = transform_string_to_int(str_id_disc);
            this->serviceDiscipline.validatorDisciplina.ValidareID(id_disc);
            ok = true;
        }
        catch (erori_app &e) {
            std::cout << "Numar de discipline invalid!" <<'\n';
            ok = false;
        }
    }
    auto numar = id_disc;
    try{
        numar = this->serviceDiscipline.autopopulare_contract(an_contract, numar);
        std::cout<<"Contract creat si autopopulat cu succes cu "<<numar<<" discipline!\n";
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

void Consola::undo() {
    try{
        this->serviceDiscipline.undo();
        std::cout<<"Undo facut cu succes!\n";
    }
    catch (erori_app &e){
        std::cout<<e.what()<<'\n';
    }
}

