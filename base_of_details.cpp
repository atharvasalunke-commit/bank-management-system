#include "base_of_details.h"


void details::insitialize_emaild_id(std::string x){
    email_id=x;
}

void details::insitialize_name(std::string y){
    name=y;
}

void details::insitialize_password(std::string k){
    password=k;
}
std::string details::get_email_id(){
    return email_id;
}
std::string details::get_name(){
    return name;
}
std::string details::get_password(){
    return password;
}

details detail;