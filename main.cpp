#include"Database.h"
#include"customer.h"
#include "bcrypt.h"
int main(){
    bool indicator;
	 main_session.access_mysql();
    try{
    std::string ans;
    std::cout<<"DO u wanna login or register new account, select 'LOG_IN'or'REGISTERATION':";
    std::cin>>ans;
    if (ans != "LOG_IN" && ans != "REGISTERATION") {
        std::cout << "ERROR! TRY AGAIN" << '\n';
        return  1;
    }
    std::cout << "enter your email id:";
    std::string email;
    std::cin>>email;
    detail.insitialize_email_id(email);
    std::cout << "enter your password:";
     std::string pd;
    std::cin>>pd;
    detail.insitialize_password(pd);
    indicator=customer.login_page(ans);
    }
    catch(std::exception&e){
        std::cout << e.what() << '\n';
        std::cout<<"error related to login_page!"<<'\n';
        return 1;
    }
    if (!indicator) {
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
        if (money <= 0) {
            std::cout << "Invalid amount" << '\n';
            exit(0);
        }
        customer.insitliaze_amount(money);
        }
        customer.handle_interface(option);
    }
    catch(...){
        std::cout<<"error related to inteface!"<<'\n';
    }
}