#ifndef customer_H
#define customer_H
#include "base_of_details.h"
#include <vector>
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

    void create_account_id();
    
    void insitliaze_amount(int);

    void insitiliaze_balance();

    void insitiliaze_pincode();

    void transcation_history();

    void handle_interface(std::string);
    
    void check_account_id();

    void check_pincode();

    void transfer();
    
    void store();

    void instialize_pincode();

    void insitialize_account_id();

    void deposit();
    
    void change_balance();

    void check_balance();
    
    void withdraw();

};
#endif
extern std::vector<std::string>store_info_customer;
extern customer_info customer;