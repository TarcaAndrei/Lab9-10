//
// Created by Andrei on 18.04.2023.
//

#ifndef LAB6_7_ERORI_H
#define LAB6_7_ERORI_H


#include <string>
#include <utility>


//class erori_app {
//public:
//    erori_app(std::string mesaj);
//    const std::string& what() const;
//private:
//    std::string message;
//
//};


//class erori_app : public std::exception{
//public:
//    erori_app(char * mesaj);
//    erori_app()=default;
//    const char*& what();
//private:
//    const char * message;
//};

class erori_app : public std::exception{
public:
    explicit erori_app(std::string mesaj);
    erori_app()=default;
    ~erori_app()=default;

    std::string what();
private:
    std::string message;
};

//class domain_error : erori_app{
//public:
//    domain_error(char * mesaj);
//    const char*& what();
//private:
//    const char * message;
//};

class repository_error : public erori_app{
public:
    explicit repository_error(std::string mesaj) : erori_app(std::move(mesaj)){};
    ~repository_error()=default;
};

class validator_error : public erori_app{
public:
    explicit validator_error(std::string mesaj) :erori_app(std::move(mesaj)){};
    ~validator_error()=default;
};

class ui_error : public erori_app{
public:
    explicit ui_error(std::string mesaj) :erori_app(std::move(mesaj)){};
    ~ui_error()=default;
};

class contract_error : public erori_app{
public:
    explicit contract_error(std::string mesaj) :erori_app(std::move(mesaj)){};
    ~contract_error()=default;
};

//class repository_error : public erori_app{
//public:
//    repository_error(char * mesaj) : erori_app(mesaj){};
//};
//
//class validator_error : public erori_app{
//public:
//    validator_error(char * mesaj) :erori_app(mesaj){};
//};


#endif //LAB6_7_ERORI_H
