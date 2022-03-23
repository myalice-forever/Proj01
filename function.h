#pragma once
#ifndef FUNCTION
#define FUNCTION
#include "struct.h"
#include<string>
#include "User.h"
using namespace std;
void user_title();
void administrator_title();
void buyer_title();
void seller_title();
void personal_center_title();
void main_title();
void get_time(goods* good);
void get_time(orders* order);
void get_time(rechargements* rechargement);
void get_time(commands* command);
void get_time(messages* temp);
void get_new_ID_orders(orders* order);
void get_new_ID_goods(goods* good);
void get_new_ID_users(users* user);
void user_title();
void message_title();
orders* create_orders();
goods* create_goods();
users* create_users();
rechargements* create_rechargements();
rechargements* create_rechargements_specific(users* user);
orders* sort_quantity_first(users* user);
orders* sort_quantity_second(orders* head);
void write_goods(goods* p);
void write_users(users* p);
void write_orders(orders* p);
void write_rechargements(rechargements* p);
void write_commands(const string& strings);
int judge_priority(const char ch1, const char ch2);
string form_expressions(users* user);
string simplify_expressions(const string& strings);
string judge_expressions_remake(const string& strings);
bool judge_expressions(const string& strings);
string get_answer(const string& strings);
string calculator(const string& strings);
void clear(goods* p);
void clear(users* p);
void clear(orders* p);
void clear(rechargements* p);
void clear(messages* p);
bool judge_goods_name_valid(char name[11]);
bool judge_goods_name_exist(char name[11]);
bool judge_goods_ID_valid(char ID[5]);
bool judge_goods_ID_exist(char ID[5]);
bool judge_users_ID_valid(char ID[5]);
bool judge_users_ID_exist(char ID[5]);
bool judge_description(char des[201]);
bool judge_user_name_exist(char name[11]);
bool judge_phoneNumber(char contact_details[20]);
bool judge_user_name_exist(string name);
//User function
bool judge_user_name_when_sign_up(const char name[11]);
User& sign_up(users* temp);
bool sign_in(char name[11]);
bool judge_address(const char address[41]);
bool judge_name(const char name[11]);
bool judge_password(const char password[21]);
bool judge_goods_ID_buyer(char ID[5]);
bool judge_context(string context);
//Buyer function
#endif