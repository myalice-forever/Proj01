#include "Buyer.h"
#include "function.h"
#include "sstream"
#include<iostream>
#include<iomanip>
#include<string.h>
#include "struct.h"
#include<cstring>
using namespace std;
bool Buyer::judge_buy_goods(char ID[5], int qua) {
	goods* p = create_goods();
	goods* head = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	if (!p || strcmp(p->state, "removed") == 0) {
		printf("No matching items found!\n");
		clear(head);
		return false;
	}
	else if (strcmp(p->seller_ID, user->ID) == 0) {
		printf("You cannot buy your own goods!\n");
		return false;
	}
	if (p->items_number < qua) {
		printf("Insufficient quantity of item to purchase!\n");
		clear(head);
		return false;
	}
	users* qq = create_users(); users* head2 = qq;
	for (; qq && strcmp(qq->ID, user->ID) != 0; qq = qq->next);
	if (p->price*qua > qq->money_rest) {
		printf("Insufficient balance, purchase failed!\n");
		clear(head2); clear(head);
		return false;
	}
	return true;
}
string Buyer::search_goods_on_sale_write_commands(char name[11]) {
	string strings("SELECT * FROM commodity WHERE commodityName CONTAINS "); 
	string argument("commodityName"); argument.append(name);
	strings.append(name);
	write_commands(strings);
	return argument;
}
void Buyer::search_goods_on_sale(char name[11]) {
	goods* p = create_goods();
	goods* head = p;
	if (!p) {
		printf("No goods found!\n");
		return;
	}
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-10s %-10s %-14s %-10s\n", "commodityID", "commodityName", "price", "number", "sellerID", "addedDate");
	for (; p; p = p->next) {
		if (strstr(p->name, name)&&strcmp(p->state," onSale")==0) {
			printf("%-14s %-14s %-10.1lf %-10d %-14s %-10s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID, p->time);
		}
	}
	printf("**************************************************************************************************\n");
	clear(head);
}
string Buyer::buy_goods_write_commands(char ID[5],int qua) {
	string argument("INSERT INTO order VALUES");
	argument.push_back('(');
	goods* p = create_goods();
	goods* head = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	ostringstream ss,s;
	ss << qua;
	s << fixed << setprecision(1) << p->price;
	orders* q = new orders;
	get_new_ID_orders(q);
	argument.append(q->ID).append(",").append(p->ID).append(",").append(s.str()).append(",").append(ss.str()).append(",").append(p->seller_ID).append(",").append(user->ID).push_back(')');
	write_commands(argument);
	clear(head);
	string ans(ID); ans.push_back(' '); ans.append(ss.str());
	return ans;
}
void Buyer::buy_goods(const char ID[5],int qua) {
	goods* p = create_goods();
	goods* head1 = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	users* qq = create_users(); users* head2 = qq;
	for (; qq && strcmp(qq->ID, user->ID) != 0;qq=qq->next);
	qq->money_rest -= qua * p->price;
	user->money_rest -= qua * p->price;
	if(strcmp(user->ID, p->seller_ID) == 0)
		user->money_rest += qua * p->price;
	qq = head2;
	for (; qq && strcmp(qq->ID, p->seller_ID) != 0; qq = qq->next);
	qq->money_rest += qua * p->price;
	p->items_number -= qua;
	if (p->items_number == 0) {
		sprintf(p->state, "removed");
	}
	orders* q = new orders; get_new_ID_orders(q); get_time(q); sprintf(q->buyer_ID, user->ID); sprintf(q->goods_ID, ID); q->quantity = qua; q->currency = p->price; sprintf(q->seller_ID, p->seller_ID);
	q->next = nullptr;
	orders* head = create_orders();
	orders* tmp = head;
	if (tmp) {
		for (; tmp->next; tmp = tmp->next); q->next = NULL; tmp->next = q;
		write_orders(head);
	}
	else {
		write_orders(q);
	}
	write_goods(head1); write_users(head2);
	printf("***************************************\n");
	printf("Trading time:  %10s\n",q->time);
	printf("Trading price:  %0.1lf\n", q->currency);
	printf("Trading quantity:  %d\n", q->quantity);
	printf("Transaction status:  Successful trading!\n");
	stringstream ss;
	ss << fixed << setprecision(1) << stod(get_answer(simplify_expressions(form_expressions(user))).c_str());
	string new_str;
	ss >> new_str;
	printf("Your balance:  %s\n", new_str.c_str());
	clear(head); clear(head1); clear(head2);
	return;
}
string Buyer::check_all_goods_on_sale_write_commands() {
	string strings("SELECT * FROM commodity");
	write_commands(strings);
	return strings;
}
void Buyer::check_all_goods_on_sale() {
	goods* p = sort_goods();
	goods* head = p;
	if (!p) {
		printf("No goods on sale!\n");
		return;
	}
	int count = 0;
	for (; p; p = p->next) {
		if (strcmp(p->state, "removed")) {
			count++;
		}
	}
	p = head;
	if (count == 0) {
		printf("No goods on sale yet!\n");
		return;
	}
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-10s %-10s %-14s %-10s\n", "commodityID", "commodityName", "price", "number", "sellerID", "addedDate");
	for (; p; p = p->next) {
		if (strcmp(p->state, " onSale") == 0) {
			printf("%-14s %-14s %-10.1lf %-10d %-14s %-10s\n", p->ID, p->name, p->price, p->items_number, p->seller_ID, p->time);
		}
	}
	printf("**************************************************************************************************\n");
	clear(head);
}
string Buyer::check_orders_write_commands() {
	string strings("SELECT * FROM order");
	write_commands(strings);
	return strings;
}
void Buyer::check_orders() {
	orders* p = create_orders();
	orders* head = p;
	if (!p) {
		printf("No orders !\n");
		return;
	}
	int count = 0;
	for (; p; p = p->next) {
		if (strcmp(p->buyer_ID, user->ID) == 0)
			count++;
	}
	p = head;
	if (count == 0) {
		printf("No orders yet!\n");
		return;
	}
	printf("**************************************************************************************************\n");
	printf("%-14s %-14s %-14s %-14s %-10s %-14s\n","orderID","commodityID", "unitPrice", "number", "date", "sellerID");
	for(;p;p=p->next)
		if(strcmp(p->buyer_ID,user->ID)==0)
			printf("%-14s %-14s %-14.1lf %-14d %-10s %-14s\n", p->ID, p->goods_ID, p->currency, p->quantity, p->time, p->seller_ID);
	printf("**************************************************************************************************\n");
	clear(head);
}
string Buyer::check_goods_details_write_commands(char ID[5]){
	string strings("SELECT * FROM commodity WHERE commodityID CONTAINS ");
	strings.append(ID);
	string ans("commodityID"); ans.append(ID);
	write_commands(strings);
	return ans;
}
void Buyer::check_goods_details(char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	if (!p) {
		printf("No goods found!\n");
		return;
	}
	for (; p; p = p->next) {
		if (strstr(p->ID, ID) && strcmp(p->state, " onSale") == 0) {
			printf("CommodityID:%s\n",p->ID);
			printf("CommodityName:%s\n", p->name);
			printf("Description:%s\n", p->description);
			printf("Price:%.1lf\n", p->price);
			printf("ItemNumber:%d\n", p->items_number);
			printf("AddedDate:%s\n", p->time);
			printf("SellerID:%s\n", p->seller_ID);
		}
	}
	clear(head);
}
void Buyer::read_commands_buyer(const string& strings) {
	if(strings.compare("SELECT * FROM commodity")==0){
		check_all_goods_on_sale();
	}
	else if (strings.compare("SELECT * FROM order") == 0) {
		check_orders();
	}
	else if (strstr(strings.c_str(), "commodityID")) {
		char ID[5];
		string tmp = strings.substr(11, 4);
		sprintf(ID ,tmp.c_str());
		check_goods_details(ID);
	}
	else if(strstr(strings.c_str(), "commodityName")) {
		char name[11];
		string tmp = strings.substr(13, 200);
		sprintf(name, tmp.c_str());
		search_goods_on_sale(name);
	}
	else {
		int quantity;
		string ID(strings.substr(0, 4));
		string tmp = strings.substr(5, 200);
		quantity=stod(tmp);
		buy_goods(ID.c_str(),quantity);
	}
}
//Extended functionality
goods* Buyer::sort_goods() {
	goods* p = create_goods();
	auto dummy = new goods;
	goods* head = p;
	dummy->next = head;
	goods* q = p;
	p = p->next;
	while (p) {
		goods* temp=dummy;
		if (q->price > p->price) {
			while (temp->next->price < p->price)
				temp = temp->next;
			q->next = p->next;
			p->next = temp->next;
			temp->next = p;
			p = q->next;
		}
		else {
			p = p->next;
			q = q->next;
		}
	}
	return dummy->next;
}
//shoppingcart function
shoppingcarts* Buyer::create_shoppingcarts() {
	FILE* fp = fopen("shoppingcart.txt", "r");
	shoppingcarts* head = nullptr, * tail = nullptr;
	char check = getc(fp);
	rewind(fp);
	while (!feof(fp) && check != EOF) {
		shoppingcarts* p = new shoppingcarts;
		fscanf(fp, "%4s %4s %4s %d %lf %10s %6s\n", p->goods_ID, p->seller_ID, p->buyer_ID, &(p->quantity), &(p->price), p->time, p->state);
		p->next = nullptr;
		if (strcmp(p->buyer_ID, user->ID) == 0) {
			if (!head) {
				head = p;
			}
			else {
				tail->next = p;
			}
			tail = p;
		}
	}
	fclose(fp);
	return head;
}
void write_shoppingcarts(shoppingcarts* p) {
	if (!p) {
		return;
	}
	FILE* fp = fopen("shoppingcart.txt", "w");
	for (; p; p = p->next) {
		fprintf(fp, "%s %s %s %d %.1lf %s %6s\n", p->goods_ID, p->seller_ID,p->buyer_ID, p->quantity, p->price, p->time,p->state);
	}
	fclose(fp);
}
void get_time(shoppingcarts* temp) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	sprintf(temp->time, "%d-%02d-%02d", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday);
}
void clear(shoppingcarts* head) {
	if (!head) {
		return;
	}
	while(head) {
		shoppingcarts* temp = head;
		head = head->next;
		delete temp;
	}
}
void Buyer::add_shoppingcart(const char ID[5], int quantity) {
	shoppingcarts* p = create_shoppingcarts();
	shoppingcarts* head = p;
	goods* q = create_goods();
	for (; p && strcmp(p->goods_ID, ID) != 0; p = p->next);
	for (; q && strcmp(q->ID, ID)!=0; q = q->next);
	if (p&&quantity+p->quantity > q->items_number) {
		printf("Not sufficient goods!\nFail to add this commodity to your cart!\n");
		return;
	}
	shoppingcarts* temp = new shoppingcarts;
	sprintf(temp->buyer_ID, user->ID);
	sprintf(temp->goods_ID, ID); sprintf(temp->seller_ID, q->seller_ID); temp->price = q->price; temp->quantity = quantity;
	get_time(temp);
	temp->next = nullptr;
	sprintf(temp->state, "undone");
	if (p) {
		for (; p->next && strcmp(p->goods_ID, ID) != 0; p = p->next);
		if (strcmp(p->goods_ID, ID) == 0) {
			p->quantity += quantity;
		}
		p->next = temp;
		write_shoppingcarts(head);
		clear(head);
	}
	else {
		write_shoppingcarts(temp);
	}
	printf("Successful adding!\n");
}
void Buyer::remove_shoppingcart(const char ID[5]) {
	shoppingcarts* p = create_shoppingcarts();
	shoppingcarts* head = p;
	for (; p && strcmp(p->goods_ID, ID) != 0; p = p->next);
	sprintf(p->state, "remove");
	write_shoppingcarts(head);
	clear(head);
	printf("Successful remove!\n");
}
void Buyer::empty_cart() {
	shoppingcarts* p = create_shoppingcarts();
	shoppingcarts* head = p;
	bool DONE = 0;
	if (!p) {
		printf("No goods in shoppingcart yet!\n");
		return;
	}
	goods* q = create_goods();
	goods* head2 = q;
	for (; p && strcmp(p->state,"undone")!=0; p = p->next);
	if (!p) {
		printf("No goods in your cart yet!\nFail to empty your cart!\n");
		return;
	}
	for (; p; p = p->next) {
		for (; q && strcmp(q->ID, p->goods_ID) != 0; q = q->next);
		if (strcmp(q->state, "removed") == 0) {
			printf("This commodity isn't on sale!\nYour purchase is failed!    If you still want to purchase this commodity,please add it to your shoppingcart once more with the right amount!\n");
			sprintf(p->state, "failed");
			continue;
		}
		else if (q->items_number < p->quantity) {
			printf("Not sufficient goods now!\nYour purchase is failed!    If you still want to purchase this commodity,please add it to your shoppingcart once more with the right amount!\n");
			sprintf(p->state, "failed");
			continue;
		}
		q = head2;
		if (judge_buy_goods(p->goods_ID, p->quantity)) {
			buy_goods(p->goods_ID, p->quantity);
			sprintf(p->state, "done");
			DONE = 1;
		}
		else {
			sprintf(p->state, "failed");
		}
	}
	if (DONE == 1)
		printf("Your shoppingcart has been successfully emptied!\n");
	else
		printf("Fail to buy some goods for some reason!\n");
	write_shoppingcarts(head);
	clear(head); clear(head2);
}
void Buyer::view_all_goods() {
	shoppingcarts* p = create_shoppingcarts();
	shoppingcarts* head = p;
	int count = 0;
	if (!p) {
		printf("No goods in shoppingcart yet!\n");
		return;
	}
	for (; p; p = p->next) {
		if (strcmp(p->state, "undone") == 0)
			count++;
	}
	if (count == 0) {
		printf("No goods in your cart yet!\n");
		return;
	}
	p = head;
	printf("%-15s %-10s %-10s %-10s %-10s\n", "CommodityID", "SellerID","Quantity", "Price", "Time");
	for (; p; p = p->next) {
		if (strcmp(p->state, "undone") == 0) {
			printf("%-15s %-10s %-10d %-10.lf %-10s\n", p->goods_ID, p->seller_ID,p->quantity, p->price, p->time);
		}
	}
	clear(head);
}
void shoppingcart_title() {
	printf("======================================================================================================================\n");
	printf("1.Add to your cart 2.remove from your cart 3.Empty your cart 4.View all goods in your cart 5.buyer interface\n");
	printf("======================================================================================================================\n");
}
bool Buyer::judge_goods_ID_cart(const char ID[5]) {
	shoppingcarts* p = create_shoppingcarts();
	shoppingcarts* head = p;
	if (!p) {
		printf("No goods in your cart yet!\n");
		return false;
	}
	for (; p && strcmp(p->goods_ID, ID) != 0; p = p->next);
	if (!p) {
		printf("No matching goods found!\n");
		return false;
	}
	else if (strcmp(p->state, "undone")) {
		printf("No matching goods found!\n");
		return false;
	}
	return true;
}
void Buyer::shoppingcart_interface() {
	int choice;
	char check,temp;
	string ID, qua;
	while (true) {
		shoppingcart_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				cin.clear(); cin.sync();
				continue;
			}
			switch (choice) {
			case 1:
				printf("Please enter good's ID:  "); getline(cin, ID);
				if (ID.size() > 4) {
					printf("Invalid input!\n");
					break;
				}
				if (judge_goods_ID_valid((char*)(ID.c_str())) && judge_goods_ID_exist((char*)(ID.c_str()))) {
					int qua;
					printf("Please enter the quantity to be added:");
					if (!scanf("%d", &(qua))) {
						printf("Invalid input!\n");
						break;
					}
					temp = getchar();
					if (temp != 10 && temp != 13) {
						printf("Invalid input!\nFail to purchase!\n");
						while ((temp = getchar()) != EOF && temp != '\n');
						cin.clear(); cin.sync();
						break;
					}
					add_shoppingcart((char*)ID.c_str(), qua);
				}
				break;
			case 2:
				printf("Please enter good's ID:  "); getline(cin, ID);
				if (ID.size() > 4) {
					printf("Invalid input!\n");
					break;
				}
				if (judge_goods_ID_valid((char*)ID.c_str()) && judge_goods_ID_cart(ID.c_str())) {
					remove_shoppingcart(ID.c_str());
				}
				break;
			case 3:
				empty_cart();
				break;
			case 4:
				view_all_goods();
				break;
			case 5:
				return;
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
void Buyer::buyer_interface() {
	int choice;
	char check;
	char temp;
	string str;
	string ID,name,ID2;
	while (true) {
		buyer_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				cin.clear(); cin.sync();
				continue;
			}
			switch (choice) {
			case 1:
				str = check_all_goods_on_sale_write_commands();
				read_commands_buyer(str);
				break;
			case 2:
				printf("Please enter the ID of the item you want to buy:");
				getline(cin, ID);
				if (ID.size()>4) {
					printf("Invalid input!\nFail to buy!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (!(judge_goods_ID_valid((char*)ID.c_str())&& judge_goods_ID_buyer((char*)ID.c_str()))) {
					break;
				}
				int qua;
				printf("Please enter the quantity to be purchased:"); 
				if (!scanf("%d", &(qua))) {
					printf("Invalid input!\n");
					break;
				}
				temp = getchar();
				if (temp != 10 && temp != 13) {
					printf("Invalid input!\nFail to purchase!\n");
					while ((temp = getchar()) != EOF && temp != '\n');
					cin.clear(); cin.sync();
					break;
				}
				if (judge_buy_goods((char*)ID.c_str(),qua)) {
					str = buy_goods_write_commands((char*)ID.c_str(),qua);
					read_commands_buyer(str);
				}
				break;
			case 3:
				printf("Please enter the name of the product you want to search:"); 
				getline(cin,name);
				if (name.size()>10) {
					printf("Invalid input!\nFail to search!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_name_valid((char*)name.c_str())) {
					str = search_goods_on_sale_write_commands((char*)name.c_str());
					read_commands_buyer(str);
				}
				break;
			case 4:
				str = check_orders_write_commands();
				read_commands_buyer(str);
				break;
			case 5:
				printf("Please enter the ID of the item you want to check:");
				getline(cin,ID2);
				if (ID2.size()>4) {
					printf("Invalid input!\nFail to check!\n");
					cin.clear(); cin.sync();
					break;
				}
				if (judge_goods_ID_valid((char*)ID2.c_str()) && judge_goods_ID_buyer((char*)ID2.c_str())) {
					str = check_goods_details_write_commands((char*)ID2.c_str());
					read_commands_buyer(str);
				}
				break;
			case 6:
				return;
			case 7:
				shoppingcart_interface();
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