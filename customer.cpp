#include "customer.h"
#include"Database.h"
void customer_info::transcation(std::string mode_of_payment){
    customer.balance = main_session.Transcation();
    int id = std::stoi(customer.get_account_id());
    if (mode_of_payment == "DEPOSIT") {
        int new_balance = customer.balance + customer.amount;
        main_session.change_balance( new_balance,customer.amount,mode_of_payment,id);
    }
    else if (mode_of_payment == "WITHDRAW") {
        if (customer.balance < customer.amount) {
            std::cout << "Insufficient balance" << '\n';
            return;
            }
        int new_balance = customer.balance - amount;
		main_session.change_balance( new_balance,customer.amount, mode_of_payment,id);
    }
    else if (mode_of_payment == "CHECK_BALANCE") {
        std::cout << "CURRENT BALANCE:" << customer.balance << '\n';
    }
    else if (mode_of_payment == "TRANSCATION_HISTORY") {
        main_session.Transcation_history();
    }
    else if (mode_of_payment == "TRANSFER") {
        std::cout << "HOW much amount do u wanna transfer:";
        int amount;
        std::cin >> amount;
        std::cout << "enter account id of receiver:";
        std::string x;
        std::cin >> x;
        if (amount <= 0) {
            std::cout << "Invalid amount" << '\n';
            exit(0);
        }
        if (customer.balance <amount) {
            std::cout << "NOT enough balance" << '\n';
            exit(0);
        }
        mode_of_payment = "TRANSFERED to other account";
        customer.balance -= amount;
        main_session.change_balance(customer.balance, amount, mode_of_payment,id);
        main_session.sender( x, amount);
    }
}
void customer_info::insitliaze_amount(int money) {
    customer.amount = money;
}
void customer_info::instialize_account_id(std::string& id) {
    customer.account_id = id;
}

void customer_info::insitiliaze_pincode() {
    std::string pc;
    std::cout << "enter you're new PINCODE for new account:";
    std::getline(std::cin, pc);
    customer.pincode = pc;
}

std::string customer_info::get_account_id(){
    return customer.account_id;
}
std::string customer_info::get_pin() {
    return customer.pincode;
}

void customer_info::check_account(){
    std::string id;
    std::cout<<"Enter your account_id:";
    std::cin>>id;
    std::string pc;
    std::cout << "Enter your Pincode:";
    std::cin >> pc;
    customer.pincode = pc;
    customer.account_id=id;
	main_session.access_account_details();
}
void customer_info:: signup(){
    try {
        if (std::cin.peek() == '\n') {
                std::cin.ignore();
            }
        std::cout << "enter your name:";
        std::string name;
        std::getline(std::cin, name);
        detail.insitialize_name(name);
        main_session.insert_account();
        customer.insitiliaze_pincode();
        main_session.insert_P_P();
        main_session.initial_balance();
        std::cout << "account created successfully!" << '\n';
    }
    catch (std::exception& s) {
        std::cout << "ERROR:" << s.what() << '\n';
    }
}
void customer_info::login(){
    try {
		main_session.login_from_db();
    }
	catch (std::exception& q) {
        std::cerr << "Error: " << q.what() << '\n';
    }
}
bool customer_info::login_page(std::string ans){
    if(ans=="LOG_IN"){
        login();
        return true;
    }
    else if(ans=="REGISTERATION"){
        signup();
        return false;
    }
    else{
        std::cout<<"TRY AGAIN"<<'\n';
    }
    return false;
}
void customer_info::handle_interface(std::string option){
    if(option=="DEPOSIT"){
        check_account();
        transcation(option);
    }
    else if(option=="WITHDRAW"){
        check_account();
        transcation(option);
    }
    else if(option=="CHECK_BALANCE"){
        check_account();
		transcation(option);
    }
    else if(option=="TRANSFER"){
        check_account();
        transcation(option);
        std::cout << "Amount is transfered" << '\n';
    }
    else if(option=="TRANSCATION_HISTORY") {
        check_account();
        transcation(option);
    }
    else{
        std::cout<<"error interface wouldn't work"<<'\n';
    }
}

customer_info customer;