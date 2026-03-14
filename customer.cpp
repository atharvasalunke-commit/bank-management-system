#include "customer.h"
#include <fstream>
void customer_info::transcation(std::string mode_of_payment){
    std::string ss=customer.account_id;
    ss=ss+".txt";
    std::ofstream file(ss,std::ios::app);
    if(mode_of_payment=="DEPOSIT"){
    file<<"-------------------------"<<'\n';
    file<<mode_of_payment<<":"<<customer.amount<<'\n';
    customer.balance=balance+customer.amount;
    file<<"Current balance:"<<customer.balance<<"----"<<detail.time_now()<<'\n'; 
    }
    else if(mode_of_payment=="WITHDRAW"){
    long long x=customer.balance;
    x=x-customer.amount;
    if(x<0){
        std::cout<<"NOT ENOUGH BALANCE TO WITHDRAW!"<<'\n';
        return;
    }
    customer.balance=x;
    file<<"-------------------------"<<'\n';
    file<<mode_of_payment<<":"<<customer.amount<<'\n';
    file<<"Current balance:"<<customer.balance<<"----"<<detail.time_now()<<'\n'; 
    }
    
    else {
        std::cout<<"error related to transcation function"<<'\n';
    }
     file.close();
}
void customer_info::transcation_history(){
    std::string t=customer.account_id;
    t=t+".txt";
    std::ifstream file(t);
    while(getline(file,t)){
        std::cout<<t<<'\n';
    }
}
void customer_info::change_balance(){
    std::string p=customer.account_id;
    p=p+".txt";
    std::string s;
    std::string k;
    std::ifstream file(p);
    while(getline(file,k)){
        if(k.empty()){
            continue;
        }
        else{
            s=k;
        }
    }
    bool indicator=false;
    int y=0;
    for(int i=0;i<s.size();i++){
        if(s[i]==':'){
            indicator=true;
            i=i+1;
        }
        if(indicator&&isdigit(s[i])){
            int x=s[i]-'0';
            y+=x;
            y=y*10;
        }
        else if(indicator){
            break;
        }
    }
    y=y/10;
    customer.balance=y;
}
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
    exit(0);
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
    exit(0);
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
    std::string s=customer.account_id;
    s=s+".txt";
    std::ofstream file2 (s,std::ios::app);
    file2<<"-------------------------"<<'\n';
    file2<<"Current balance:"<<"0"<<"----"<<detail.time_now()<<'\n';
    file<<"0"<<'\n';
    std::cout<<"Registered your new account:"<<'\n';
    file.close();
    file2.close();
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
void customer_info::handle_interface(std::string option){
    if(option=="DEPOSIT"){
        check_account_id();
        check_pincode();
        change_balance();
        transcation(option);
    }
    else if(option=="WITHDRAW"){
        check_account_id();
        check_pincode();
        change_balance();
        transcation(option);
    }
    else if(option=="CHECK_BALANCE"){
        check_account_id();
        check_pincode();
        change_balance();
        check_balance();
    }
    else if(option=="TRANSFER"){
        std::cout<<"work in progress"<<'\n';
    }
    else if(option=="TRANSCATION_HISTORY") {
        check_account_id();
        check_pincode();
        transcation_history();
    }
    else{
        std::cout<<"error interface wouldn't work"<<'\n';
    }
}

std::vector<std::string>store_info_customer;
customer_info customer;