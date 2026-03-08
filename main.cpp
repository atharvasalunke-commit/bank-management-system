#include "customer.h"
int main(){
    try{
    std::string ans;
    std::cout<<"DO u wanna login or register new account, select 'LOG_IN'or'REGISTERATION':";
    std::cin>>ans;
    std::string email;
    std::cout<<"enter your email id:";
    std::cin>>email;
    detail.insitialize_emaild_id(email);
    int password;
    std::cout<<"enter your password:";
    std::cin>>password;
    detail.insitialize_password(password);
    customer.login_page(ans);
    }
    catch(...){
        std::cout<<"error related to login_page!"<<'\n';
    }
}