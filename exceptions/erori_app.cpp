//
// Created by Andrei on 18.04.2023.
//

#include "erori_app.h"


//erori_app::erori_app(std::string mesaj) : message(mesaj){
//
//}
//
//const std::string &erori_app::what() const {
//    return this->message;
//}
erori_app::erori_app(std::string mesaj) : message(mesaj) {

}

std::string erori_app::what(){
    return this->message;
}

//const char *&domain_error::what() {
//    return this->message;
//}
//
//domain_error::domain_error(char *mesaj) : message(mesaj) {
//
//}


//const char *&repository_error::what() {
//    return e;
//}
//
//validator_error::validator_error(char *mesaj) : message(mesaj) {
//
//}
//
//const char *&validator_error::what() {
//    return this->message;
//}
