//
// Created by Andrei on 09.04.2023.
//

#include "Teste.h"

#include <cassert>
#include "Vector.h"
#include "Iterator.h"
#include "../domain/Disciplina.h"

//
// Created by Andrei on 09.04.2023.
//
void teste_template(){
    Vector <int>vector;
    assert(vector.size()== 0);
    vector.push_back(5);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(9);
    assert(vector.find(0) == 5);
    assert(vector.size()== 4);
    assert(vector.remove(2) == 3);
    assert(vector.size()== 3);
    auto it = vector.iterator();
    assert(it.valid());
    assert(it.element() == 5);
    it.next();
    assert(it.valid());
    assert(it.element() == 2);
    assert(it.valid());
    it.next();
    assert(it.element() == 9);
    it.next();
    it.next();
    it.next();
    it.next();
    it.next();
    auto x = it.element();
    assert(x == 0);
    assert(not it.valid());
    vector.find(-4);
    vector.remove(-4);
    for(int i = 0; i < 101; i++)
        vector.push_back(5);
    it.end();

}

void teste_disc(){
    Vector <Disciplina> vector;
    assert(vector.size()== 0);
    Disciplina disciplina1 = Disciplina(10, "OOP", 4, "Obligatorie", "Prof1");
    Disciplina disciplina2 = Disciplina(111, "OPOP", 34, "Obligatoriee", "Prof12");
    Disciplina disciplina3 = Disciplina(12, "OPOP", 34, "Obligatoriee", "Prof12");
    Disciplina disciplina4 = Disciplina(13, "OPOP", 34, "Obligatoriee", "Prof12");
    vector.push_back(disciplina1);
    vector.push_back(disciplina2);
    assert(vector.size()== 2);
    assert(vector.find(0).get_id() == disciplina1.get_id());
    assert(vector.find(1).get_id() == disciplina2.get_id());
    assert(vector.remove(0).get_id() == disciplina1.get_id());
    assert(vector.size()== 1);
    auto it = vector.iterator();
    assert(it.valid());
    assert(it.element().get_id() == disciplina2.get_id());
    it.next();
    assert(not it.valid());
    assert(vector[0].get_id() == disciplina2.get_id());
    vector.push_back(disciplina1);
    vector.push_back(disciplina3);
    vector.push_back(disciplina4);
    int a = 0;
    for(auto it = vector.begin(); it < vector.end(); it++){
        ++a;
    }
    auto it2 = vector.begin();
    assert((*it2).get_id() == 111);
    assert(a==4);
}