#pragma once
#ifndef SELLER
#define SELLER
#include "User.h"
using namespace std;
class Seller:public User{
	users* user = new users;
public:
	Seller(users* p) {
		*(user) = *p;
	}
	string write_check_goods_released();
	void check_goods_released();
	string write_change_goods_information(char ID[5], double price);
	string write_change_goods_information(char ID[5], char description[201]);
	void change_goods_information(const char ID[5],double price);
	void change_goods_information(const char ID[5], const char description[201]);
	string write_delete_goods(char ID[5]);
	void delete_goods(const char ID[5]);
	string write_check_orders();
	void check_orders();
	string write_release_goods(char name[11], char description[201], double price, int quantity);
	void release_goods(goods good);
	void read_commands_seller(const string& strings);
	bool judge_goods_seller(char ID[5]);
	void seller_interface();
};
#endif