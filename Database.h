#ifndef Database_H
#define Database_H
#include<iostream>
#include<mysqlx/xdevapi.h>
class Bank_Database {
private:
	mysqlx::Session sess;
	mysqlx::Schema db;
public:
	Bank_Database() :sess("localhost", 33060, "root", "00"),
		db(sess.getSchema("Bankkk")) {
		std::cout << "connected database succesfully" << '\n';
	 }
	mysqlx::Session&get_sess() {
		return sess;
	}
	void access_mysql(mysqlx::Session&);

	void insert_account(mysqlx::Session&);

	void login_from_db (mysqlx::Session&);

	void insert_P_P(mysqlx::Session&);

	void access_account_id(mysqlx::Session&);

	void access_pincode(mysqlx::Session&);

	void balance(mysqlx::Session&);

	int Transcation(mysqlx::Session&);

	void change_balance(mysqlx::Session&,int&,int&,std::string&);

	void Transcation_history(mysqlx::Session&);

};
#endif
extern Bank_Database main_session;