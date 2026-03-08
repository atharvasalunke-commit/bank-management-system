#include "customer.h"
#include <fstream>
void customer_info:: signup(){
    std::ofstream file("Accounts.txt",std::ios::app);
    file <<detail.get_email_id()<<'\n';
    file<<detail.get_password()<<'\n';
    std::cout<<"Registered your new account:"<<'\n';
    file.close();
}
void customer_info::login(){
    std::ifstream file("Accounts.txt");
    if(!file.is_open()){
        std::cout<<"error opening the file"<<'\n';
    }
    std::string x;
    std::string y;
    while(getline(file,x)&&getline(file,y)){
        if(detail.get_email_id()==x&&detail.get_string_pd()==y){
            std::cout<<"Welcome:"<<'\n';
            file.close();
            break;
        }
    }
}
void customer_info::login_page(std::string ans){
    if(ans=="LOG_IN"){
        login();
    }
    else if(ans=="REGISTERATION"){
        signup();
    }
    else{
        std::cout<<"TRY AGAIN"<<'\n';
    }
}
customer_info customer;