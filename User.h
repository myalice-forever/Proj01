#pragma once
#ifndef USER
#define USER
#include<string>
#include "struct.h"
using namespace std;
class User {
	users* user = new users;
public:
	User() {
		sprintf(user->state, "active");
		user->money_rest = 0.0;
	}
	User(const char ID[5]) {
		sprintf(user->ID, ID);
		sprintf(user->state, "active");
		user->money_rest = 0;
	}
	User(users* p) {
		*user = *p;
	}
	users get_users() {
		return *user;
	}
	friend User& sign_up(users* temp);
	void check_personal_information();
	void recharge(double rechargement);
	void change_personal_information();
	friend bool judge_user_name_when_sign_up(const char name[11]);
	friend rechargements* create_rechargements_specific(users* user);
	friend orders* sort_quantity_first(users* user);
	friend orders* sort_quantity_second(orders* head);
	friend string form_expressions(users* user);
	friend string simplify_expressions(const string& strings);
	friend string get_answer(const string& strings);
	friend void get_new_ID_users(users* user);
	void user_interface();
	void personal_interface();
	void change_password();
	//message system
	messages* create_messages();
	void write_messages(messages* p);
	void leave_messages(string ID);
	void check_messages_unread();
	void check_all_messages();
	void check_other_messages(string ID);
	void message_interface();
};
#endif