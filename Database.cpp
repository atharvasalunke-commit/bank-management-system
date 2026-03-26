#include <mysqlx/xdevapi.h>
#include "Database.h"
#include<iostream>
#include<string>
#include"base_of_details.h"
#include"customer.h"
#include<vector>
void access_mysql() {
	mysqlx::Session ses("localhost", 33060, "root", "00");
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
void insert_account() {
	mysqlx::Session sess("localhost", 33060, "root", "00");
	auto db = sess.getSchema("Bankkk");
	auto table_1 = db.getTable("accounts");
	table_1.insert("name", "email_id")
		.values(detail.get_name(), detail.get_email_id())
		.execute();
}
void insert_P_P() {
	mysqlx::Session sess("localhost", 33060, "root", "00");
	auto db = sess.getSchema("Bankkk");
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
void login_from_db() {
	mysqlx::Session sess("localhost", 33060, "root", "00");
	auto db = sess.getSchema("Bankkk");
	auto table_1 = db.getTable("accounts")
		.select("email_id")
		.where("email_id ='" + detail.get_email_id() + "'")
		.execute();
	auto table_2 = db.getTable("P_P")
		.select("password")
		.where("password='" + detail.get_password() + "'")
		.execute();
}