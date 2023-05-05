//
// Created by Andrei on 29.03.2023.
//

#ifndef LAB6_7_DISCIPLINA_H
#define LAB6_7_DISCIPLINA_H
#include <string>
using namespace std;

class Disciplina {
private:
    int id_disciplina{};
    std::string denumire_disciplina;
    int ore_pe_saptamana{};
    string tip;
    string cadru_didactic;
public:
    Disciplina(int id_disciplina, string denumire_disciplina, int ore_pe_saptamana, string tip, string cadru_didactic);
    Disciplina() = default;
    Disciplina(const Disciplina& disciplina);
    ~Disciplina() = default;
    [[nodiscard]] int get_id() const;
    [[nodiscard]] string get_denumire() const;
    [[nodiscard]] int get_ore_pe_saptamana() const ;
    [[nodiscard]] string get_tip() const;
    [[nodiscard]] string get_cadru_didactic() const;
    void set_denumire(string denumire_noua);
    void set_ore_pe_saptamana(int ore_pe_saptamana_nou);
    void set_tip(string tip_nou);
    void set_cadru_didactic(string cadru_didactic_nou);
    string afisare_disciplina();
    string scriere_disciplina();
};


#endif //LAB6_7_DISCIPLINA_H
