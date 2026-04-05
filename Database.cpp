#include "Database.h"
#include"customer.h"
#include"bcrypt.h"
void Bank_Database:: access_mysql() {
	std::cout << "Successfully connected to database" << '\n';

	for (auto db_name : sess.getSchemas()) {
		std::cout << db_name.getName() << '\n';
	}
	mysqlx::Schema db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	std::cout << "Tables in this database:" << '\n';
	for(auto t: db.getTables()) {
		std::cout << t.getName() << '\n';
	}
}
void Bank_Database::insert_account() {
	auto db = sess.getSchema("Bankkk");

	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table = db.getTable("accounts");
	auto result=table.select("email_id")
		.where("email_id= :email")
		.bind("email",detail.get_email_id())
		.execute();
	if (result.count() > 0)  {
			std::cout << "This email_id already exists" << '\n';
			return;
	}
	auto table_1 = db.getTable("accounts");
	table_1.insert("name", "email_id")
		.values(detail.get_name(), detail.get_email_id())
		.execute();
}
void  Bank_Database::insert_P_P() {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto row = db.getTable("accounts")
		.select("id").
		where("email_id = :email")
		.bind("email",detail.get_email_id())
		.execute();
		auto result = row.fetchOne();
		std::string hash_password = bcrypt::generateHash(detail.get_password());
		std::string hash_pin = bcrypt::generateHash(customer.get_pin());
	auto table_2 = db.getTable("P_P");
	table_2.insert("id","password", "pin")
		.values(result[0],hash_password,hash_pin)
		.execute();	
	std::string id = std::to_string(result[0].get<int>());
	customer.instialize_account_id(id);
}
void Bank_Database::login_from_db() {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table_1 = db.getTable("accounts");
	auto result_1=table_1.select("id")
	.where("email_id = :email")
	.bind("email",detail.get_email_id())
	.execute();
	if (result_1.count() > 0) {
	
		auto row = result_1.fetchOne();
		auto table_2 = db.getTable("P_P");
		auto result_2 = table_2.select("password")
			.where("id= :idd")
			.bind("idd", row[0].get<int>())
			.execute();

		if (result_2.count() > 0) {
			auto row_2 = result_2.fetchOne();
			std::string hash_Password = row_2[0].get<std::string>();
			if (bcrypt::validatePassword(detail.get_password(),hash_Password) ){
				std::cout << "LOG IN SUCCESSFULLY" << '\n';
				return;
			}
			else {
				std::cout << "wrong email id or password" << '\n';
				exit(0);
			}
		}
		else {
			std::cout << "wrong email id or password" << '\n';
			exit(0);
		}
	}
	else {
		std::cout << "wrong email id or password" << '\n';
		exit(0);
	}
}
void Bank_Database::initial_balance() {
	mysqlx::Schema db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	mysqlx::Table table_2 = db.getTable("transcation_history");
	table_2.insert("id", "mode","amount","curr_balance")
		.values(stoi(customer.get_account_id()), "created_account",0, 0)
		.execute();
}
void Bank_Database::change_balance(int&new_balance,int&amount,std::string &x,int &id) {
	mysqlx::Schema db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	mysqlx::Table table_2 = db.getTable("transcation_history");
	table_2.insert("id", "mode","amount", "curr_balance")
		.values(id, x, amount, new_balance)
		.execute();
	std::cout<< "Transcation Done" << '\n';
}

void Bank_Database::access_account_details() {
	try {
		auto db = sess.getSchema("Bankkk");
		if (!db.existsInDatabase()) {
			std::cout << " database doesn't exist" << '\n';
			return;
		}
		auto table = db.getTable("P_P");
		auto result = table.select("pin")
			.where("id= :idd")
			.bind("idd",stoi(customer.get_account_id()))
			.execute();
		if (result.count() > 0) {
			auto row = result.fetchOne();
			std::string hashpin = row[0].get<std::string>();
			if (bcrypt::validatePassword(customer.get_pin(),hashpin)) {
				std::cout << "Welcome" << '\n';
				return;
			}
			else {
				std::cout << "error wrong account_id or pincode" << '\n';
				exit(0);
			}
		}
		else {
			std::cout << "wrong  account_id or pincode" << '\n';
			exit(0);
		}
	}
	catch (std::exception&e) {
		std::cout << "error:"<<e.what()<< '\n';
		exit(0);
	}
}
int Bank_Database::Transcation() {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return -1;
	}
	auto table = db.getTable("transcation_history");
	auto row = table.select("curr_balance")
		.where("id= :idd")
		.orderBy("curr_dt DESC")
		.bind("idd",stoi(customer.get_account_id()))
		.execute();
	if (row.count() > 0) {
		auto result = row.fetchOne();
		auto balance = result[0].get<int>();
		return balance;
	}
	return -1;
}
void Bank_Database::Transcation_history() {
	auto db = sess.getSchema("Bankkk");
	if (!db.existsInDatabase()) {
		std::cout << " database doesn't exist" << '\n';
		return;
	}
	auto table = db.getTable("transcation_history");
	auto result= table.select("mode", "amount", "curr_balance", "CAST(curr_dt AS CHAR)")
		.where("id= :idd")
		.orderBy("curr_dt DESC")
		.bind("idd", stoi(customer.get_account_id()))
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
void Bank_Database::sender(std::string&id_receiver,int &amount) {
	mysqlx::Schema db = sess.getSchema("Bankkk");
	mysqlx::Table table =db.getTable("transcation_history");
	auto result = table.select("curr_balance")
		.where("id= :idd")
		.orderBy("curr_dt DESC")
		.bind("idd",stoi(id_receiver))
		.execute();
	auto row = result.fetchOne();
	int x = amount + row[0].get<int>();
	table.insert("id", "mode", "amount", "curr_balance")
		.values(id_receiver, "received amount from '" + customer.get_account_id() + "'", amount, x)
		.execute();
}
Bank_Database main_session;