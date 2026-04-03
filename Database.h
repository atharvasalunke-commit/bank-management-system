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
	void access_mysql(mysqlx::Session&);

	void insert_account(mysqlx::Session&);

	void login_from_db (mysqlx::Session&);

	void insert_P_P(mysqlx::Session&);

	void access_account_details(mysqlx::Session&);

	void initial_balance(mysqlx::Session&);

	int Transcation(mysqlx::Session&);

	void change_balance(mysqlx::Session&,int&,int&,std::string&,int&);

	void Transcation_history(mysqlx::Session&);

	void sender(mysqlx::Session&,std::string&,int&);
};
extern Bank_Database main_session;
#endif
