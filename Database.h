#ifndef Database_H
#define Database_H
#include<mysqlx/xdevapi.h>
#include<iostream>
class Bank_Database {
private:
	mysqlx::Session sess;
public:
	Bank_Database() :sess("localhost", 33060, "root", "00"){
		std::cout << "connected database succesfully" << '\n';
	 }
	mysqlx::Session&get_sess() {
		return sess;
	}
	void access_mysql();

	void insert_account();

	void login_from_db ();

	void insert_P_P();

	void access_account_details();

	void initial_balance();

	int Transcation();

	void change_balance(int&,int&,std::string&,int&);

	void Transcation_history();

	void sender(std::string&,int&);
};
extern Bank_Database main_session;
#endif
