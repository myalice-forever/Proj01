#pragma once
#include<string>
using namespace std;
#ifndef STRUCT
#define STRUCT
struct goods {
	char ID[5];
	char name[11];
	double price;
	int items_number;
	char description[201];
	char seller_ID[5];
	char time[11];
	char state[8];
	goods* next;
};
struct orders {
	char ID[5];
	char goods_ID[5];
	double currency;
	int quantity;
	char time[11];
	char seller_ID[5];
	char buyer_ID[5];
	orders* next;
};
struct rechargements {
	char ID[5];
	double money;
	char time[11];
	rechargements* next;
};
struct commands {
	char time[20];
};
struct users {
	char ID[5];
	char name[11];
	char password[21];
	char contact_details[21];
	char address[41];
	double money_rest;
	char state[9];
	users* next;
};
struct shoppingcarts{
	char goods_ID[5];
	char seller_ID[5];
	char buyer_ID[5];
	int quantity;
	double price;
	char time[11];
	char state[7];//done,failed,undone
	shoppingcarts* next;
};
struct messages {
	string time;
	string other_name;
	string self_name;
	string context;
	string state;
	messages* next;
};
#endif
