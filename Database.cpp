#include <mysqlx/xdevapi.h>
#include "Database.h"
#include<string>
#include"base_of_details.h"
#include"customer.h"
#include<vector>

void Bank_Database:: access_mysql(mysqlx::Session &ses) {
	std::cout << "Successfully connected to database" << '\n';

	for (auto db_name : ses.getSchemas()) {
		std::cout << db_name.getName() << '\n';
	}
	mysqlx::Schema db = ses.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	std::cout << "Tables in this database:" << '\n';
	for(auto t: db.getTables()) {
		std::cout << t.getName() << '\n';
	}
}
void Bank_Database::insert_account(mysqlx::Session&sess) {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table_1 = db.getTable("accounts");
	table_1.insert("name", "email_id")
		.values(detail.get_name(), detail.get_email_id())
		.execute();
}
void Bank_Database::insert_P_P(mysqlx::Session&sess) {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto row = db.getTable("accounts")
		.select("id", "email_id").
		where("email_id ='"+detail.get_email_id()+"'")
		.execute();
		auto result = row.fetchOne();

	auto table_2 = db.getTable("P_P");
	table_2.insert("id","password", "pin")
		.values(result[0],detail.get_password(), customer.get_pin())
		.execute();
}
void Bank_Database::login_from_db(mysqlx::Session& sess) {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table_1 = db.getTable("accounts")
		.select("email_id")
		.where("email_id ='" + detail.get_email_id() + "'")
		.execute();
	auto table_2 = db.getTable("P_P")
		.select("password")
		.where("password='" + detail.get_password() + "'")
		.execute();
}
void Bank_Database::balance(mysqlx::Session&sess) {
	mysqlx::Schema db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table_1 = db.getTable("accounts");
	auto row = table_1.select("id")
		.where("email_id= '" + detail.get_email_id() + "'")
		.execute();
	auto result = row.fetchOne();
	mysqlx::Table table_2 = db.getTable("transcation_history");
	table_2.insert("id", "mode", "curr_balance")
		.values(result[0], "created_account", 0)
		.execute();
}
void Bank_Database::change_balance(mysqlx::Session& sess,int&new_balance,int&amount,std::string &x) {
	mysqlx::Schema db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table_1 = db.getTable("accounts");
	auto row = table_1.select("id")
		.where("email_id= '" + detail.get_email_id() + "'")
		.execute();
	if (row.count() == 0) {
		std::cout << "could not find account" << '\n';
		return;
	}
	auto result = row.fetchOne();
	mysqlx::Table table_2 = db.getTable("transcation_history");
	table_2.insert("id", "mode","amount", "curr_balance")
		.values(result[0].get<int>(), x,amount, new_balance)
		.execute();
	std::cout<< "Transcation Done" << '\n';
}

void Bank_Database::access_account_id(mysqlx::Session&sess) {
	try {
		auto db = sess.getSchema("Bankkk");
		if (!db.existsInDatabase()) {
			std::cout << " database doesn't exist" << '\n';
			return;
		}
		auto table = db.getTable("accounts");
		auto result = table.select("id")
			.where("id='" + customer.get_account_id() + "'")
			.execute();
	}
	catch (...) {
		std::cout << "error wrong account_Id" << '\n';
		exit(0);
	}
	}
void Bank_Database::access_pincode(mysqlx::Session&sess){
	try {
		auto db = sess.getSchema("Bankkk");
		if (!db.existsInDatabase()) {
			std::cout << " database doesn't exist" << '\n';
			return;
		}
		auto table = db.getTable("P_P");
		auto row = table.select("pin")
			.where("pin='" + customer.get_pin() + "'")
			.execute();
		return;
	}
	catch (...) {
		std::cout << "error wrong pincode" << '\n';
		exit(0);
	}
}
int Bank_Database::Transcation(mysqlx::Session&sess) {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return -1;
	}
	auto table = db.getTable("transcation_history");
	auto row = table.select("curr_balance")
		.where("id='" + customer.get_account_id() + "'")
		.orderBy("curr_dt DESC")
		.execute();
	if (row.count() > 0) {
		auto result = row.fetchOne();
		auto balance = result[0].get<int>();
		return balance;
	}
	return -1;
}
void Bank_Database::Transcation_history(mysqlx::Session& sess) {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table = db.getTable("transcation_history");
	auto result= table.select("mode", "amount", "curr_balance", "CAST(curr_dt AS CHAR)")
		.where("id='" + customer.get_account_id() + "'")
		.orderBy("curr_dt DESC")
		.execute();
	if (result.count() > 0) {
		std::string transcation_time;
		for (auto row : result) {
			 transcation_time = row[3].get<std::string>();
			if(row[1].isNull()) {
				std::cout << row[0].get<std::string>()<< "----" << "current balance" << "----" << row[2].get<int>()<< "----" << transcation_time << '\n';
			}
			
			else {
				std::cout << row[0].get<std::string>() << ":" << row[1].get<int>() << "----" << "current balance" << "----" << row[2].get<int>() << "----" <<transcation_time << '\n';
			}
		}
	}
	else {
		std::cout << "Error related to Transcation history" << '\n';
		exit(0);
	}
}
Bank_Database main_session;