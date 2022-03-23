#pragma once
#ifndef ADMINISTRATOR
#define ADMINISTRATOR
#include<string>
using namespace std;
class administrator {
	char name[11];
	char password[21];
public:
	administrator() {
		sprintf(name, "admin");
		sprintf(password, "123456");
	}
	bool log_in(char name[11], char password[21]);
	string write_check_all_goods();
	void check_all_goods();
	string  write_check_all_orders();
	void check_all_orders();
	string  write_check_all_users();
	void check_all_users();
	string write_remove_goods(char ID[5]);
	void remove_goods(const char ID[5]);
	string  write_block_users(char ID[5]);
	void block_users(const char ID[5]);
	string write_search_for_goods(char name[11]);
	void search_for_goods(const char name[11]);
	void read_commands_administrator(const string& strings);
	void administrator_interface();
};
#endif