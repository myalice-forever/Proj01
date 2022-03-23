#include<iostream>
#include "administrator.h"
#include "function.h"
using namespace std;
bool administrator::log_in(char name[11],char password[21]) {
	if (strcmp(name, "admin") == 0 ) {
		if (strcmp(password, "123456") == 0) {
			return true;
		}
		printf("-----Wrong password entered!	Login failed!	Return to the main menu!-----\n");
	}
	printf("-----Wrong username entered!	Login failed!	Return to the main menu!-----\n");
	return false;
}
string administrator::write_check_all_goods() {
	string str("SELECT * FROM commodity");
	write_commands(str);
	return str;
}
void administrator::check_all_goods() {
	goods* p = create_goods(); goods* head = p;
	if (!p) {
		printf("No goods!\n");
		return;
	}
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-10s %-10s %-14s %-12s %-10s\n", "commodityID", "commodityName", "price", "number", "sellerID", "addedDate", " state  ");
	for (; p; p = p->next)
		printf("%-14s %-14s %-10.1lf %-10d %-14s %-12s %-10s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID,p->time, p->state);
	printf("**************************************************************************************************\n");
	clear(head);
	return;
}
string  administrator::write_check_all_orders() {
	string str("SELECT * FROM order");
	write_commands(str);
	return str;
}
void administrator::check_all_orders() {
	orders* p = create_orders();
	orders* head = p;
	if (!p) {
		printf("No orders!\n");
		return;
	}
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-10s %-10s %-10s %-14s %-14s\n", "orderID", "commodityID", "unitPrice", "number", "date", "sellerID","buyerID");
	for (; p; p = p->next)
		printf("%-14s %-14s %-10.1lf  %-10d %-10s %-14s %-14s\n", p->ID, p->goods_ID, p->currency, p->quantity, p->time, p->seller_ID, p->buyer_ID);
	printf("**************************************************************************************************\n");
	clear(head);
}
string  administrator::write_check_all_users() {
	string str("SELECT * FROM user");
	write_commands(str);
	return str;
}
void administrator::check_all_users() {
	users* p = create_users();
	users* head = p;
	if (!p) {
		printf("No user!\n");
		return;
	}
	printf("************************************************************************************************************************\n");
	printf("%-14s %-10s %-20s %-20s %-40s %-10s %-10s\n", "userID","username","password","phoneNumber","address","balance","userState"	);
	for(;p;p=p->next)
		printf("%-14s %-10s %-20s %-20s %-40s %-10.1lf %-10s\n", p->ID, p->name, p->password, p->contact_details, p->address, p->money_rest, p->state);
	printf("*************************************************************************************************************************\n");
	clear(head);
}
string administrator::write_remove_goods(char ID[5]) {
	string str("UPDATE commodity SET state = removed WHERE commodityID = ");
	str.append(ID);
	write_commands(str);
	return str;
}
void administrator::remove_goods(const char ID[5]) {
	goods* p = create_goods();
	goods* head = p,*tmp=p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	sprintf(p->state, "removed");
	printf("Remove successfully!\n");
	write_goods(head);
	clear(tmp);
}
string administrator::write_block_users(char ID[5]) {
	string str("UPDATE commodity SET state = removed WHERE sellerID = ");
	str.append(ID);
	write_commands(str);
	string new_str("UPDATE user SET userState = inactive WHERE userID = ");
	new_str.append(ID);
	write_commands(new_str);
	string ans(ID);
	return ans;
}
void administrator::block_users(const char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	users* q = create_users();
	users* head1 = q,*tmp=q;
	for (; p && strcmp(p->seller_ID, ID) != 0; p = p->next);
	if (!p) {
		for (; q; q = q->next) {
			if (strcmp(q->ID, ID) == 0)
				sprintf(q->state, "inactive");
		}
		write_users(head1);
		clear(head1);
		return;
	}
	else {
		p = head;
		for (; p; p = p->next) {
			if (strcmp(p->seller_ID, ID) == 0)
				sprintf(p->state, "removed");
		}
		for (; q; q = q->next) {
			if (strcmp(q->ID, ID) == 0)
				sprintf(q->state, "inactive");
		}
		write_users(head1);
		write_goods(head);
		clear(head1); clear(head);
		printf("Block successful\n");
		return;
	}
}
string administrator::write_search_for_goods(char name[11]) {
	string str("SELECT * FROM commodity WHERE commodityName CONTAINS ");
	str.append(name);
	write_commands(str);
	return str;
}
void administrator::search_for_goods(const char name[11]) {
	goods* p = create_goods();
	goods* head = p;
	for (; p && !strstr(p->name, name); p = p->next);
	if (!p) {
		printf("No matching items found!\n");
		return;
	}
	p = head;
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-10s %-10s %-14s %-12s %-14s\n", "commodityID", "commodityName", "price", "number", "sellerID", "addedDate", " state  ");
	for (; p; p = p->next) {
		if(strstr(p->name,name))
			printf("%-14s %-14s %-10.1lf %-10d %-14s %-12s %-14s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID, p->time, p->state);
	}
	printf("**************************************************************************************************\n");
	clear(head);
}
void administrator::read_commands_administrator(const string& strings) {
	if (strcmp(strings.c_str(), "SELECT * FROM commodity") == 0) {
		check_all_goods();
	}
	else if (strcmp(strings.c_str(), "SELECT * FROM order")==0) {
		check_all_orders();
	}
	else if (strcmp(strings.c_str(), "SELECT * FROM user")==0) {
		check_all_users();
	}
	else if (strstr(strings.c_str(), "SELECT * FROM commodity WHERE commodityName CONTAINS ")) {
		int tmp = strings.find("CONTAINS");
		string tp(strings.substr(tmp + 9, 200));
		search_for_goods(tp.c_str());
	}
	else if (strstr(strings.c_str(), "UPDATE commodity SET state = removed WHERE commodityID = ")) {
		int tmp = strings.find("commodityID");
		string tp(strings.substr(tmp + 14, 4));
		remove_goods(tp.c_str());
	}
	else {
		block_users(strings.c_str());
	}
}
void administrator::administrator_interface() {
	int choice;
	char check;
	char ch;
	char temp;
	string str;
	string ID;
	string name;
	string ID1;
	while (true) {
		administrator_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check=getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				cin.clear(); cin.sync();
				continue;
			}
			switch (choice) {
			case 1:
				str = write_check_all_goods();
				read_commands_administrator(str);
				break;
			case 2:
				printf("Please enter the name of the item you want to search for:"); getline(cin,name);
				if (name.size()>11) {
					printf("Invalid input!\nFail to search!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_name_valid((char*)name.c_str())) {
					str = write_search_for_goods((char*)name.c_str());
					read_commands_administrator(str);
				}
				break;
			case 3:
				printf("Please enter the ID of the product you want to remove:"); getline(cin, ID);
				if (ID.size()>4) {
					printf("Invalid input!\nFail to remove!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_ID_valid((char*)ID.c_str())&&judge_goods_ID_exist((char*)ID.c_str())) {
					goods* p = create_goods();
					goods* tmp = p;
					for (; p && strcmp(p->ID, (char*)ID.c_str()) != 0; p = p->next);
					if (strcmp(p->state, "removed") == 0) {
						printf("This product has already been removed!\n");
						break;
					}
					printf("Confirm that if you want to remove the item:\n");
					printf("***********************************************************************************************************************\n");
					printf("%-14s %-14s %-10s %-10s %-14s %-12s %-10s\n", "commodityID", "commodityName", "price", "number", "sellerID", "addedDate", " state");
					printf("%-14s %-14s %-10.1lf %-10d %-14s %-12s %-10s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID, p->time, p->state);
					printf("***********************************************************************************************************************\n");
					printf("Please confirm: (y/n) :");
					scanf("%c", &ch);
					temp = getchar();
					if (temp != 10 && temp != 13) {
						printf("Invalid input!\nFail to remove!\n");
						while ((temp = getchar()) != EOF && temp != '\n');
						cin.clear(); cin.sync();
						break;
					}
					if (ch== 'y') {
						str = write_remove_goods((char*)ID.c_str());
						read_commands_administrator(str);
					}
					else if (ch == 'n') {
						printf("Fail to remove!\n");
					}
					else {
						printf("Invalid input!\n");
					}
					clear(tmp);
				}
				break;
			case 4:
				str = write_check_all_orders();
				read_commands_administrator(str);
				break;
			case 5:
				str = write_check_all_users();
				read_commands_administrator(str);
				break;
			case 6:
				printf("Please enter the ID of the user you want to ban:"); getline(cin,ID1);
				if (ID1.size()>4) {
					printf("Invalid input!\nFail to ban!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_users_ID_valid((char*)ID1.c_str())&&judge_users_ID_exist((char*)ID1.c_str())) {
					users* q = create_users();
					users* tmp = q;
					for (; q && strcmp(q->ID, (char*)ID1.c_str()) != 0; q = q->next);
					if (strcmp(q->state, "inactive") == 0) {
						printf("User has already been blocked!\n");
						break;
					}
					printf("Confirm that if you want to ban this user:\n");
					printf("**************************************************************************************************************************\n");
					printf("%-14s %-10s %-20s %-20s %-40s %-10s %-10s\n", "userID", "username", "password", "phoneNumber", "address", "balance", "userState");
					printf("%-14s %-10s %-20s %-20s %-40s %-10.1lf %-10s\n", q->ID, q->name, q->password, q->contact_details, q->address, q->money_rest, q->state);
					printf("***************************************************************************************************************************\n");
					printf("Please confirm: (y/n) :");
					scanf("%c", &ch);
					temp = getchar();
					if (temp != 10 && temp != 13) {
						printf("Invalid input!\nFail to ban!\n");
						while ((temp = getchar()) != EOF && temp != '\n');
						cin.clear(); cin.sync();
						break;
					}
					if (ch == 'y') {
						str = write_block_users((char*)ID1.c_str());
						read_commands_administrator(str);
					}
					else if(ch=='n') {
						printf("Fail to ban!\n");
					}
					else {
						printf("Invalid input!\n");
					}
				}
				break;
			case 7:
				return;
				break;
			default:
				printf("Invalid input!\n");
			}
		}
		else {
			cin.clear(); cin.sync();
			printf("Invalid input!\n");
			char c;
			while ((c = getchar()) != EOF && c != '\n');
		}
	}
}