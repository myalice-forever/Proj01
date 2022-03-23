#include<iostream>
#include<iomanip>
#include <sstream> 
#include "Seller.h"
#include "User.h"
#include "function.h"
#include "struct.h"
using namespace std;
string Seller::write_check_goods_released() {
	string str("SELECT * FROM commodity");
	write_commands(str);
	return str;
}
void Seller::check_goods_released() {
	goods* p = create_goods();
	goods* head = p;
	if (!p) {
		printf("No listings yet!\n");
		return;
	}
	printf("%-14s %-14s %-10s %-10s %-12s %-10s\n", "commodityID", "commodityName", "price", "number", "addedDate"," state  ");
	for (; p; p = p->next)
		if(strcmp(p->seller_ID,user->ID)==0)
			printf("%-14s %-14s %-10.1lf %-10d %-12s %-10s\n", p->ID, p->name, p->price, p->items_number, p->time, p->state);
	clear(head);
	return;
}
string Seller::write_change_goods_information(char ID[5],double price) {
	string str("UPDATE commodity SET price = ");
	char prices[200];
	sprintf(prices, "%.1lf", price);
	str.append(prices).append(" WHERE commodityID = ").append(ID);
	write_commands(str);
	return str;
}
string Seller::write_change_goods_information(char ID[5], char description[201]) {
	string str("UPDATE commodity SET description = ");
	string tmp(description);
	str.append(description).append(" WHERE commodityID = ").append(ID);
	write_commands(str);
	return str;
}
void Seller::change_goods_information(const char ID[5], double price) {
	goods* p = create_goods();
	goods* head = p;
	goods* head2 = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	p->price = price;
	printf("Successful change!\n");
	write_goods(head);
	clear(head2);
}
void Seller::change_goods_information(const char ID[5], const char description[201]) {
	goods* p = create_goods();
	goods* head = p;
	goods* head2 = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	sprintf(p->description, description);
	printf("Successful change!\n");
	write_goods(head);
	clear(head2);
}
string Seller::write_delete_goods(char ID[5]) {
	string str("UPDATE commodity SET state = removed WHERE commodityID = ");
	str.append(ID);
	write_commands(str);
	return str;
}
void Seller::delete_goods(const char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	goods* head2 = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	sprintf(p->state, "removed");
	printf("The product was successfully removed from the shelves!\n");
	write_goods(head);
	clear(head2);
}
string Seller::write_check_orders() {
	string str("SELECT * FROM order");
	write_commands(str);
	return str;
}
void Seller::check_orders() {
	orders* p = create_orders();
	orders* head = p;
	if (!p) {
		printf("No orders yet!\n");
		return;
	}
	int count = 0;
	for (; p; p = p->next) {
		if (strcmp(p->seller_ID, user->ID)==0)
			count++;
	}
	p = head;
	if (count == 0) {
		printf("No orders yet!\n");
		return;
	}
	printf("%-14s %-14s %-10s %-10s %-10s %-14s\n", "orderID","commodityID", "unitPrice", "number", "date","buyerID");
	for (; p; p = p->next)
		if(strcmp(p->seller_ID,user->ID)==0)
			printf("%-14s %-14s %-10.1lf %-10d %-10s %-14s\n", p->ID, p->goods_ID, p->currency, p->quantity, p->time, p->buyer_ID);
	clear(head);
}
string Seller::write_release_goods(char name[11],char description[201],double price,int quantity) {
	string str("INSERT INTO commodity VALUES (");
	ostringstream ss, s;
	ss << fixed << setprecision(1) << price;
	s << quantity;
	str.append(name).append(",").append(ss.str()).append(",").append(s.str()).append(",").append(description).append(")");
	return str;
}
void Seller::release_goods(goods good) {
	goods* p = create_goods();
	goods* head = p, * head2 = p;
	if (!p) {
		goods* q = new goods;
		*q = good;
		write_goods(q);
		printf("The product was released successfully!\n\n");
		return;
	}
	for (; p->next; p = p->next);
	goods* q = new goods;
	*q = good;
	p->next = q;
	write_goods(head);
	clear(head2);
	printf("The product was released successfully!\n\n");
	return;
}
void Seller::read_commands_seller(const string& strings) {
	if (strcmp("SELECT * FROM commodity", strings.c_str()) == 0) {
		check_goods_released();
	}
	else if (strcmp("SELECT * FROM order", strings.c_str()) == 0) {
		check_orders();
	}
	else if (strstr(strings.c_str(), "UPDATE commodity SET state = removed WHERE commodityID = ")) {
		int tmp = strings.find("commodityID");
		string tp = strings.substr(tmp + 14, 4);
		delete_goods(tp.c_str());
	}
	else if (strstr(strings.c_str(), "UPDATE commodity SET price = ")) {
		int tmp = strings.find("=");
		int tmp2 = strings.find("WHERE");
		string price = strings.substr(tmp + 2, tmp2 - tmp - 3);
		tmp = strings.find("commodityID");
		string tp = strings.substr(tmp + 14, 4);
		double p = stod(price);
		change_goods_information(tp.c_str(), p);
	}
	else if (strstr(strings.c_str(), "UPDATE commodity SET description = ")) {
		int tmp = strings.find("=");
		int tmp2 = strings.find("WHERE");
		string des = strings.substr(tmp + 2, tmp2 - tmp - 3);
		tmp = strings.find("commodityID");
		string tp = strings.substr(tmp + 14, 4);
		change_goods_information(tp.c_str(), des.c_str());
	}
	else {
		int tmp0 = strings.find("(");
		int tmp1 = strings.find(",");
		string name(strings.substr(tmp0 + 1, tmp1 - 1 - tmp0));
		string tp = strings.substr(tmp1 + 1, 400);
		tmp0 = tp.find(",");
		string price = tp.substr(0, tmp0);
		tp = tp.substr(tmp0 + 1, 400);
		tmp0 = tp.find(",");
		string qua = tp.substr(0, tmp0);
		tp = tp.substr(tmp0+1, 400);
		tp.pop_back();
		string des = tp;
		goods* q = new goods;
		get_new_ID_goods(q);
		sprintf(q->name, name.c_str());
		q->next = nullptr;
		q->price = stod(price);
		q->items_number = stoi(qua);
		sprintf(q->description, des.c_str());
		sprintf(q->seller_ID, user->ID);
		sprintf(q->state, "onSale");
		get_time(q);
		release_goods(*q);
	}
}
bool Seller::judge_goods_seller(char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	if (!p) {
		printf("No good on sale yet!\n");
		return false;
	}
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	if (!p) {
		printf("No matching good found!\n");
		return false;
	}
	if(strcmp(p->seller_ID, user->ID) == 0 && strcmp(p->state," onSale")==0)
		return true;
	printf("No matching good found!\n");
	return false;
}
void Seller::seller_interface() {
	int choice;
	int flag = 0; int count = 0; double price_temp;
	char check;
	char buf;
	char ch;
	char temp;
	string str;
	string name, description,ID,des,ID1,price;
	while (true) {
		char buf;
		seller_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				while ((buf = getchar()) != EOF && buf != '\n');
				cin.clear(); cin.sync();
				continue;
			}
			switch (choice) {
			case 1:
				int quantity;
				printf("Please enter product name:"); 
				getline(cin, name);
				if (name.size() > 11) {
					printf("Invalid input!\nFail to release!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (!judge_goods_name_valid((char*)name.c_str())) {
					printf("Fail to release goods!\n");
					break;
				}
				printf("Please enter product price:");
				getline(cin,price);
				count = 0;flag = 0; 
				for (int i = 0; i < price.size(); i++) {
					if (flag == 1)
						count++;
					if (price[i] == '.')
						flag = 1;
				}
				if (count > 1) {
					printf("You cannot enter two decimal places!\n");
					break;
				}
				price_temp=stod(price);
				if (price_temp <= 0) {
					printf("The price entered is invalid!\nFail to release goods!\n");
					break;
				}
				printf("Please enter the quantity of the item:");
				if (!scanf("%d", &quantity) ) {
					printf("The amount entered is invalid!\nFail to release goods!\n");
					while ((buf = getchar()) != EOF && buf != '\n');
					break;
				}
				temp = getchar();
				if (temp != 10 && temp != 13) {
					printf("Invalid input!\nFail to release!\n");
					while ((temp = getchar()) != EOF && temp != '\n');
					cin.clear(); cin.sync();
					break;
				}
				if (quantity <= 0) {
					printf("You cannot release such goods!\nXD\n");
					break;
				}
				printf("Please enter product description:"); 
				getline(cin,description);
				if (description.size()>200) {
					printf("Invalid input!\nFail to release!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (!judge_description((char*)description.c_str())) {
					printf("The deswcription entered is invalid!\nFail to release goods!\n");
					break;
				}
				printf("Please confirm that the information on the listed product is correct\n");
				printf("****************************************************************************************\n");
				printf("CommodityName:%s\nCommodityPrice:%.1lf\nCommodityQuantity:%d\nDescription:%s\n", name.c_str(), price_temp, quantity, description.c_str());
				printf("****************************************************************************************\n");
				printf("Please confirm: (y/n) :");
				scanf("%c", &ch);
				temp = getchar();
				if (temp != 10 && temp != 13) {
					printf("Invalid input!\nFail to release!\n");
					while ((temp = getchar()) != EOF && temp != '\n');
					cin.clear(); cin.sync();
					break;
				}
				if (ch == 'y') {
					str = write_release_goods((char*)name.c_str(), (char*)description.c_str(), price_temp, quantity);
					read_commands_seller(str);
				}
				else if (ch == 'n') {
					printf("Fail to release!\n");
				}
				else {
					printf("Invalid input!\n");
				}
				break;
			case 2:
				str = write_check_goods_released();
				read_commands_seller(str);
				break;
			case 3:
				printf("Please enter the ID of the item you want to modify:");
				getline(cin, ID);
				if (ID.size()>4) {
					printf("Invalid input!\nFail to modify!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_ID_valid((char*)ID.c_str())&&judge_goods_seller((char*)ID.c_str())) {
					printf("Please enter the attributes of the item you want to modify  (1.price  2.description):");
					int tmp;
					if (cin >> tmp) {
						goods* p = create_goods();
						goods* head = p;
						for (; p && strcmp(p->ID, (char*)ID.c_str()) != 0; p = p->next);
						if (tmp == 1) {
							printf("Please enter the modified price:");
							getchar();
							getline(cin, price);
							count = 0;flag = 0; 
							for (int i = 0; i < price.size(); i++) {
								if (flag == 1)
									count++;
								if (price[i] == '.')
									flag = 1;
							}
							if (count > 1) {
								printf("You cannot enter two decimal places!\n");
								break;
							}
							if (stod(price) <= 0) {
								printf("You cannot enter negative number!\n");
								break;
							}
							printf("Please confirm that the information of the modified product is correct\n");
							printf("****************************************************************************************\n");
							printf("CommodityID:  %s\nCommodityName:  %s\nCommodityPrice:  %.1lf\nDescription:  %s\n", p->ID,p->name, stod(price),p->description);
							printf("****************************************************************************************\n");
							printf("Please confirm: (y/n) :");
							scanf("%c", &ch);
							temp = getchar();
							if (temp != 10 && temp != 13) {
								printf("Invalid input!\nFail to modify!\n");
								while ((temp = getchar()) != EOF && temp != '\n');
								cin.clear(); cin.sync();
								break;
							}
							if (ch == 'y') {
								str = write_change_goods_information((char*)ID.c_str(), stod(price));
								read_commands_seller(str);
							}
							else if (ch == 'n') {
								printf("Fail to modify!\n");
								break;
							}
							else {
								printf("Invalid input!\n");
								break;
							}
						}
						else if (tmp == 2) {
							printf("Please enter the modified description:");
							getline(cin,des);
							if (des.size()>200) {
								printf("Invalid input!\nFail to modify!\n");
								cin.clear(); cin.sync();
								break;
							}
							if (!judge_description((char*)des.c_str())) {
								printf("The description entered is invalid!\nFail to modify!\n");
								break;
							}
							printf("Please confirm that the information of the modified product is correct\n");
							printf("****************************************************************************************\n");
							printf("CommodityID:  %s\nCommodityName:  %s\nCommodityPrice:  %.1lf\nDescription:  %s\n", p->ID, p->name, p->price, des.c_str());
							printf("****************************************************************************************\n");
							printf("Please confirm: (y/n) :");
							scanf("%c", &ch);
							temp = getchar();
							if (temp != 10 && temp != 13) {
								printf("Invalid input!\nFail to modify!\n");
								while ((temp = getchar()) != EOF && temp != '\n');
								cin.clear(); cin.sync();
								break;
							}
							if (ch == 'y') {
								str = write_change_goods_information((char*)ID.c_str(), (char*)des.c_str());
								read_commands_seller(str);
							}
							else if (ch == 'n') {
								printf("Fail to modify!\n");
							}
						}
						else {
							printf("Invalid input!\n");
						}
						clear(head);
					}
					else {
						cin.clear(); cin.sync();
						printf("Invalid input!\n");
						char c;
						while ((c = getchar()) != EOF && c != '\n');
					}
				}
				break;
			case 4:
				printf("Please enter the ID of the product you want to remove:");
				getline(cin, ID1);
				if (ID1.size()>4) {
					printf("Invalid input!\nFail to remove!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_ID_valid((char*)ID1.c_str())&&judge_goods_seller((char*)ID1.c_str())) {
					goods* p = create_goods();
					for (; p && strcmp(p->ID, (char*)ID1.c_str()) != 0; p = p->next);
					printf("Confirm that if you want to remove the item\n");
					printf("****************************************************************************************\n");
					printf("%-14s %-14s %-10s %-10s %-14s %-12s %-14s\n","commodityID","commodityName"	,"price","number","sellerID","addedDate"," state  ");
					printf("%-14s %-14s %-10.1lf %-10d %-14s %-12s %-14s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID, p->time, p->state);
					printf("****************************************************************************************\n");
					printf("Please confirm: (y/n) :");
					scanf("%c", &ch);
					temp = getchar();
					if (temp != 10 && temp != 13) {
						printf("Invalid input!\nFail to remove!\n");
						while ((temp = getchar()) != EOF && temp != '\n');
						cin.clear(); cin.sync();
						break;
					}
					if (ch == 'y') {
						str = write_delete_goods((char*)ID1.c_str());
						read_commands_seller(str);
					}
					else if (ch == 'n') {
						printf("Fail to remove!\n");
					}
					else {
						printf("Invalid input!\n");
					}
				}
				break;
			case 5:
				str = write_check_orders();
				read_commands_seller(str);
				break;
			case 6:
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
