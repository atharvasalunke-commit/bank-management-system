#include "customer.h"
#include <fstream>
void customer_info::create_account_id(){
    std::ifstream file1 ("account_id.txt");
    std::string x;
    std::string line;
    while(getline(file1,x)){
        if(!x.empty()){line=x;}
    }
    file1.close();
    std::ofstream file2("account_id.txt",std::ios::app);
    int y=stoi(line);
    y=y+1;
    line=std::to_string(y);
    customer.account_id=line;
    file2<<line<<'\n';
}
void customer_info::check_account_id(){
      std::string id;
    std::cout<<"Enter your account_id:";
    std::cin>>id;
    customer.account_id=id;
    std::ifstream file ("accounts.txt");
    std::string x;
    while(getline(file,x)){
        if(x==customer.account_id){
            return;
        }
    }
    std::cout<<"Wrong account_id"<<'\n';
}
void customer_info::insitliaze_amount(int money){
    customer.amount=money;
}


void customer_info::check_pincode(){
    std::string pc;
    std::cout<<"Enter your Pincode:";
    std::cin>>pc;
    customer.pincode=pc;
    std::ifstream file ("accounts.txt");
    std::string x;
    while(getline(file,x)){
        if(x==customer.pincode){
            return;
        }
    }
    std::cout<<"Wrong pincode"<<'\n';
}
void customer_info::store(){
    std::string x;
    std::string y;
    bool indicator=false;
    std::ifstream file("accounts.txt");
    while(getline(file,x)&&getline(file,y)){
        if(x==customer.account_id&& y==customer.pincode){
            indicator=true;
            break;
        }
    }
    if(!indicator){
        std::cout<<"Wrong account_id or password"<<'\n';
        return;
    }
        getline(file,x);
        int bal=stoi(x);
        customer.balance=bal;
    
}
void customer_info::insitiliaze_pincode(){
    std::string pc;
    std::cout<<"enter you're new PINCODE for new account:";
    std::cin>>pc;
    customer.pincode=pc;
}
void customer_info:: signup(){
    std::ofstream file("Accounts.txt",std::ios::app);
     if(!file.is_open()){
        std::cout<<"error opening the file"<<'\n';
        exit(0);
    }
    customer.create_account_id();
    customer.insitiliaze_pincode();
    file<<detail.get_email_id()<<'\n';
    file<<detail.get_password()<<'\n';
    file<<customer.account_id<<'\n';
    file<<customer.pincode<<'\n';
    file<<"0"<<'\n';
    std::cout<<"Registered your new account:"<<'\n';
    file.close();
}
void customer_info::login(){
    std::ifstream file("Accounts.txt");
    if(!file.is_open()){
        std::cout<<"error opening the file"<<'\n';
        exit(0);
    }
    std::string x;
    std::string y;
    while(getline(file,x)&&getline(file,y)){
        if(detail.get_email_id()==x&&detail.get_password()==y){
            std::cout<<"Welcome:"<<'\n';
            file.close();
            break;
        }
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
void customer_info::check_balance(){
  std::cout<<"Current Balance:"<<customer.balance<<'\n';
}
void customer_info::deposit(){
    long long x=customer.balance;
    x=x+customer.amount;
    customer.balance=x;
    std::cout<<"Current Balance:"<<customer.balance<<'\n';
}
void customer_info::withdraw(){
     long long x=customer.balance;
    x=x-customer.amount;
    if(x<0){
        std::cout<<"NOT ENOUGH BALANCE TO WITHDRAW!"<<'\n';
        return;
    }
    customer.balance=x;
    std::cout<<"Current Balance:"<<customer.balance<<'\n';
}
void customer_info::handle_interface(std::string option){
    if(option=="DEPOSIT"){
        check_account_id();
        check_pincode();
        store();
        deposit();
    }
    else if(option=="WITHDRAW"){
        check_account_id();
        check_pincode();
        store();
        withdraw();
    }
    else if(option=="CHECK_BALANCE"){
        check_account_id();
        check_pincode();
        store();
        check_balance();
    }
    else if(option=="TRANSFER"){
        std::cout<<"work in progress"<<'\n';
    }
    else if(option=="TRANSCATION_HISTORY") {
               std::cout<<"work in progress"<<'\n';

    }
    else{
        std::cout<<"error interface wouldn't work"<<'\n';
    }
}

std::vector<std::string>store_info_customer;
customer_info customer;