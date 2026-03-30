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

    void insitliaze_amount(int);
    
    void insitiliaze_pincode();

    void handle_interface(std::string);
    
    void check_account_id();

    std::string get_account_id();

    void check_pincode();
        
    std::string get_pin();
    
    void transcation(std::string);

	void transfer(std::string);
};
#endif
extern customer_info customer;