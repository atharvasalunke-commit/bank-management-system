#include "base_of_details.h"


void details::insitialize_emaild_id(std::string x){
    email_id=x;
}

void details::insitialize_name(std::string y){
    name=y;
}

void details::insitialize_password(int k){
    password=k;
}
std::string details::get_email_id(){
    return email_id;
}
std::string details::get_name(){
    return name;
}
int details::get_password(){
    return password;
}

std::string details::get_string_pd(){
    std::string a=std::to_string(password);
    return a;
}

details detail;