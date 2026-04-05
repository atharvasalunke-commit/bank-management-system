#ifndef customer_H
#define customer_H
#include "base_of_details.h"
class customer_info:protected details{
    private:
    int amount;
    int balance;
    std::string account_id;
    std::string pincode;
    public:
    bool login_page(std::string);
    
    void login();
    
    void signup();

    void insitliaze_amount(int);
    
    void insitiliaze_pincode();

    void handle_interface(std::string);
    
    void check_account();

    std::string get_account_id();

        
    std::string get_pin();
    
    void transcation(std::string);

    void instialize_account_id(std::string&);
};
extern customer_info customer;
#endif
