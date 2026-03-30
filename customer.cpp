#include "customer.h"
#include <fstream> 
#include"Database.h"

void customer_info::transcation(std::string mode_of_payment){
    customer.balance = main_session.Transcation(main_session.get_sess());
    int id = stoi(customer.get_account_id());
    if (mode_of_payment == "DEPOSIT") {
        int new_balance = customer.balance + customer.amount;
        main_session.change_balance(main_session.get_sess(), new_balance,customer.amount,mode_of_payment,id);
    }
    else if (mode_of_payment == "WITHDRAW") {
        if (customer.balance < customer.amount) {
            std::cout << "Insufficient balance" << '\n';
            return;
            }
        int new_balance = customer.balance - amount;
		main_session.change_balance(main_session.get_sess(), new_balance,customer.amount, mode_of_payment,id);
    }
    else if (mode_of_payment == "CHEK_BALANCE") {
        std::cout << "CURRENT BALANCE:" << customer.balance << '\n';
    }
    else if (mode_of_payment == "TRANSCATION_HISTORY") {
        main_session.Transcation_history(main_session.get_sess());
    }
    else if (mode_of_payment == "TRANSFER") {
        if (customer.balance < customer.amount) {
            std::cout << "NOT enough balance" << '\n';
            exit(0);
        }
        mode_of_payment = "TRANSFERED to other account";
        customer.balance -= customer.amount;
        main_session.change_balance(main_session.get_sess(), customer.balance, customer.amount, mode_of_payment,id);
    }
}

std::string customer_info::get_account_id(){
    return customer.account_id;
}
void customer_info::check_account_id(){
      std::string id;
    std::cout<<"Enter your account_id:";
    std::cin>>id;
    customer.account_id=id;
	main_session.access_account_id(main_session.get_sess());
}
void customer_info::insitliaze_amount(int money){
    customer.amount=money;
}

void customer_info::check_pincode(){
    std::string pc;
    std::cout<<"Enter your Pincode:";
    std::cin>>pc;
    customer.pincode=pc;
	main_session.access_pincode(main_session.get_sess());
   
}
void customer_info::insitiliaze_pincode(){
    std::string pc;
    std::cout<<"enter you're new PINCODE for new account:";
    std::getline(std::cin, pc);
    customer.pincode=pc;
}
std::string customer_info::get_pin(){
    return customer.pincode;
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
        main_session.insert_account(main_session.get_sess());
        customer.insitiliaze_pincode();
        main_session.insert_P_P(main_session.get_sess());
        main_session.balance(main_session.get_sess());
        std::cout << "account created successfully!" << '\n';
    }
    catch (std::exception& s) {
        std::cout << "ERROR:" << s.what() << '\n';
    }
}
void customer_info::login(){
    try {
		main_session.login_from_db(main_session.get_sess());
		std::cout << "Logged in successfully!" << '\n';
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
void customer_info::transfer(std::string option) {
    std::cout << "HOW much amount do u wanna transfer:";
    int amount;
    std::cin >> amount;
    customer.insitliaze_amount(amount);
	std::cout << "enter account id of receiver:";
    std::string x;
    std::cout << "enter receiver's account id:";
    std::cin >> x;
    customer.transcation(option);
    main_session.sender(main_session.get_sess(),x,amount);
}
void customer_info::handle_interface(std::string option){
    if(option=="DEPOSIT"){
        check_account_id();
        check_pincode();
        transcation(option);
    }
    else if(option=="WITHDRAW"){
        check_account_id();
        check_pincode();
        transcation(option);
    }
    else if(option=="CHECK_BALANCE"){
        check_account_id();
        check_pincode();
		transcation(option);
    }
    else if(option=="TRANSFER"){
        check_account_id();
        check_pincode();
		transfer(option);
        std::cout << "Amount is transfered" << '\n';
    }
    else if(option=="TRANSCATION_HISTORY") {
        check_account_id();
        check_pincode();
        transcation(option);
    }
    else{
        std::cout<<"error interface wouldn't work"<<'\n';
    }
}

customer_info customer;