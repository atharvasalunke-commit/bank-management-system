#ifndef customer_H
#define customer_H
#include "base_of_details.h"
class customer_info:protected details{
    private:
    int amount;
    int balance;
    int pincode;
    public:
    void login_page(std::string);
    
    void login();
    
    void signup();
    
    void insitliaze_amount();

    void insitiliaze_balance();

    void insitiliaze_pincode();
    
    void transfer(std::string,int,int);
    
    void deposit(std::string,int,int);
    
    void check_balacne(std::string,int,int);
    
    void withdraw(std::string,int,int);

};
#endif
extern customer_info customer;