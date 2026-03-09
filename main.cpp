#include "customer.h"
int main(){
    bool indicator;
    try{
    std::string ans;
    std::cout<<"DO u wanna login or register new account, select 'LOG_IN'or'REGISTERATION':";
    std::cin>>ans;
    std::string email;
    std::cout<<"enter your email id:";
    std::cin>>email;
    detail.insitialize_emaild_id(email);
     std::string pd;
    std::cout<<"enter your password:";
    std::cin>>pd;
    detail.insitialize_password(pd);
    indicator=customer.login_page(ans);
    }
    catch(...){
        std::cout<<"error related to login_page!"<<'\n';
    }
    if(!indicator){
        return 0;
    }
    try{
        std::string option;
        std::cout<<"select option:WITHDRAW--------DEPOSIT--------TRANSCATION_HISTORY--------CHECK_BALANCE--------TRANSFER--------"<<'\n';
        std::cin>>option;
        if(option=="WITHDRAW"||option=="DEPOSIT"){
        int money;
        std::cout<<"Enter amount to"<<option<<":";
        std::cin>>money;
        customer.insitliaze_amount(money);
        }
        customer.handle_interface(option);
    }
    catch(...){
        std::cout<<"error related to inteface!"<<'\n';
    }
}