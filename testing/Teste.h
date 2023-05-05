//
// Created by Andrei on 29.03.2023.
//

#ifndef LAB6_7_TESTE_H
#define LAB6_7_TESTE_H

class Teste {
private:
    void ruleaza_teste_domeniu() const;
    void ruleaza_teste_erori() const;
    void ruleaza_teste_validare() const;
    void ruleaza_teste_repository() const;
    void ruleaza_teste_contract() const;
    void ruleaza_teste_repository_contract() const;
    void ruleaza_teste_service() const;
    void funct1(int a) const;
    void funct2(std::string b) const;

public:
    Teste();
    void ruleaza_toate_testele() const;

};


#endif //LAB6_7_TESTE_H
