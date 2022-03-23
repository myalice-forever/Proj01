#pragma once
#ifndef BUYER
#define BUYER
#include "User.h"
using namespace std;
class Buyer :public User {
	users* user=new users;
public:
	Buyer(const char ID[5]) {
		sprintf(user->ID, ID);
	}
	Buyer(users* p) {
		*(user) = *p;
	}
	void buyer_interface();
	string search_goods_on_sale_write_commands(char name[11]);
	void search_goods_on_sale(char name[11]);
	string buy_goods_write_commands(char ID[5],int qua);
	void buy_goods(const char ID[5],int qua);
	string check_all_goods_on_sale_write_commands();
	void check_all_goods_on_sale();
	string check_orders_write_commands();
	void check_orders();
	string check_goods_details_write_commands(char ID[5]);
	void check_goods_details(char ID[5]);
	void read_commands_buyer(const string& strings);
	bool judge_buy_goods(char ID[5], int qua);
	goods* sort_goods();
	//shoppingcart function
	bool judge_goods_ID_cart(const char ID[5]);
	shoppingcarts* create_shoppingcarts();
	void add_shoppingcart(const char ID[5], int quantity);
	void remove_shoppingcart(const char ID[5]);
	void empty_cart();
	void view_all_goods();
	void shoppingcart_interface();
};
void write_shoppingcarts(shoppingcarts* p);
void get_time(shoppingcarts* temp);
void clear(shoppingcarts* head);
void shoppingcart_title();
#endif
