#include<iostream>
#include<cstring>
#include<cstdio>
#include<sstream>
#include<string>
#include<fstream>
#include<stack>
#include<time.h>
#include <limits>
#include "struct.h";
#include "User.h"
#include <strstream>
#include <iomanip>
using namespace std;
bool END = 0;
void clear(goods* p);
void clear(orders* p);
void clear(users* p);
void clear(rechargements* p);
void user_title() {
	printf("=======================================================================================================\n");
	printf("1.I am the buyer 2.I am the seller 3.Management of Personal Information 4.Message system 5.Log out\n");
	printf("=======================================================================================================\n");
}
void administrator_title() {
	printf("======================================================================================================================\n");
	printf("1.View all products 2.Search for products 3.Remove products 4.View all orders  5.View all users  6.ban users  7.logout\n");
	printf("======================================================================================================================\n");
}
void buyer_title() {
	printf("======================================================================================================================\n");
	printf("1.View all products 2.buy goods 3.Search products 4.View historical orders 5.View product details 6.user's interface\n");
	printf("======================================================================================================================\n");
	printf("==========================\n");
	printf("7.shopping cart\n");
	printf("==========================\n");
}
void seller_title() {
	printf("======================================================================================================================\n");
	printf("1.List products 2.View listings 3.Edit your listing 4.Remove products 5.View historical orders 6.user's interface\n");
	printf("======================================================================================================================\n");
}
void personal_center_title() {
	printf("==========================================================================================================\n");
	printf("1.View information 2.Modify information 3.Rechargement 4.change password 5.user's interface\n");
	printf("==========================================================================================================\n");
}
void main_title() {
	printf("=====================================================================\n");
	printf("1.Administrator login  2.User Registration  3.User login  4.Exit\n");
	printf("=====================================================================\n");
}
void message_title() {
	printf("=========================================================================================================\n");
	printf("1.Leave a message 2.Check unread messages 3.Check all messages 4.Check specific messages 5.user interface\n");
	printf("=========================================================================================================\n");
}
//void buyer_interface(users& buyer);
orders* create_orders() {
	FILE* fp = fopen("order.txt", "r");
	if (!fp) {
		printf("No such file!");
		exit(-1);
	}
	else {
		orders* head = NULL, * tail = NULL;
		char check=getc(fp);
		rewind(fp);
		if (!feof(fp))
			fscanf(fp, "orderID,commodityID,unitPrice,number,date,sellerID,buyerID\n");
		while (!feof(fp) && check != EOF) {
			orders* p = new orders;
			p->next = NULL;
			fscanf(fp, "%4[^,],%4[^,],%lf,%d,%10[^,],%4[^,],%4[^,]\n", p->ID, p->goods_ID, &(p->currency), &(p->quantity), p->time, p->seller_ID, p->buyer_ID);
			if (!head)
				head =p;
			else
				tail->next = p;
			tail = p;
		}
	fclose(fp);
	return head;
	}
}
goods* create_goods() {
	FILE* fp = fopen("commodity.txt", "r");
	if (!fp) {
		printf("No such file!");
		exit(-1);
	}
	else {
		goods* head = NULL, * tail = NULL;
		char check = getc(fp);
		rewind(fp);
		if (!feof(fp))
			fscanf(fp, "commodityID,commodityName,price,number,description,sellerID,addedDate,state\n");
		while (!feof(fp) && check != EOF) {
			goods* p = new goods;
			p->next = NULL;
			fscanf(fp, "%4[^,],%20[^,],%lf,%d,%200[^,],%4[^,],%10[^,],%7[^,]\n", p->ID, p->name, &(p->price), &(p->items_number), p->description,p->seller_ID, p->time,p->state);
			if (!head)
				head = p;
			else
				tail->next = p;
			tail = p;
		}
		fclose(fp);
		return head;
	}
}
users* create_users() {
	FILE* fp = fopen("user.txt", "r");
	if (!fp) {
		printf("No such file!");
		exit(-1);
	}
	else {
		users* head = NULL;
		users* tail = new users;
		char check = getc(fp);
		rewind(fp);
		if (!feof(fp))
			fscanf(fp, "userID,username,password,phoneNumber,address,balance,userState\n");
		while (!feof(fp) && check != EOF) {
			users* p = new users;
			p->next = NULL;
			fscanf(fp, "%4[^,],%10[^,],%20[^,],%20[^,],%40[^,],%lf,%8[^,]\n", p->ID, p->name, p->password, p->contact_details, p->address,&( p->money_rest),p->state);
			if (!head)
				head = p;
			else
				tail->next = p;
			tail = p;
		}
		fclose(fp);
		return head;
	}
}
rechargements* create_rechargements() {
	FILE* fp = fopen("rechargement.txt", "r");
	if (!fp) {
		cerr << "No such file!";
		exit(-1);
	}
	else {
		fscanf(fp, "userD,rechargements,time\n");
		rechargements* head = NULL, * tail = NULL;
		while (!feof(fp)) {
			rechargements* p = new rechargements;
			p->next = NULL;
			fscanf(fp, "%4s,%lf,%10s\n", p->ID,&(p->money), p->time);
			if (head == NULL)
				head = p;
			else
				tail->next = p;
			tail = p;
		}
		fclose(fp);
		return head;
	}
}
rechargements* create_rechargements_specific(users* user) {
	rechargements* p = create_rechargements();
	rechargements* head = NULL, * tail = NULL;
	if (!p)
		return nullptr;
	for (; p; p = p->next) {
		if (strcmp(user->ID, p->ID) == 0) {
			rechargements* q = new rechargements;
			sprintf(q->ID, p->ID);
			q->money = p->money; q->next = NULL;
			if (head == NULL)
				head = q;
			else
				tail->next = q;
			tail = q;
		}
	}
	return head;
}
void write_orders(orders* p) {
	if (!p) {
		//printf("No orders now!");
		return;
	}
	FILE* fp = fopen("order.txt", "w");
	fprintf(fp, "orderID,commodityID,unitPrice,number,date,sellerID,buyerID\n");
	for(;p;p=p->next)
		fprintf(fp, "%s,%s,%.1lf,%d,%s,%s,%4s\n", p->ID, p->goods_ID, p->currency, p->quantity, p->time, p->seller_ID, p->buyer_ID);
	fclose(fp);
}
void write_goods(goods* p) {
	if (!p) {
		//printf("No goods now!");
		return;
	}
	FILE* fp = fopen("commodity.txt", "w");
	fprintf(fp, "commodityID,commodityName,price,number,description,sellerID,addedDate,state\n");
	for (; p; p = p->next) 
		fprintf(fp, "%s,%s,%.1lf,%d,%s,%s,%s,%7s\n", p->ID, p->name, p->price, p->items_number, p->description, p->seller_ID, p->time, p->state);
	fclose(fp);
}
void write_users(users* p) {
	if (!p) {
		//printf("No users now!");
		return;
	}
	FILE* fp = fopen("user.txt", "w");
	fprintf(fp, "userID,username,password,phoneNumber,address,balance,userState\n");
	for(;p;p=p->next)
		fprintf(fp, "%s,%s,%s,%s,%s,%.1lf,%8s\n", p->ID, p->name, p->password, p->contact_details, p->address, p->money_rest,p->state);
	fclose(fp);
}
void write_rechargements(rechargements* p) {
	if (!p) {
		//printf("No rechargements now!");
		return;
	}
	FILE* fp = fopen("rechargement.txt", "w");
	if (!fp) {
		cerr << "No such file!";
		exit(-1);
	}
	else {
		fprintf(fp, "userD,rechargements,time\n");
		for(;p;p=p->next)
			fprintf(fp, "%s,%.1lf,%10s\n", p->ID,p->money, p->time);
	}
	fclose(fp);
}
void get_time(commands* command);
void write_commands(const string& strings) {
	commands* command = new commands;
	get_time(command);
	FILE* fp = fopen("commands.txt", "a");
	fprintf(fp, "%s%s\n", command->time,strings.c_str());
	fclose(fp);
}
void get_new_ID_users(users* user) {
	users* p = create_users();
	users* head = p;
	if (!p) {
		sprintf(user->ID, "U001");
	}
	else {
		for (; p->next; p = p->next);
		string tmp(p->ID);
		string::iterator it = tmp.begin();
		tmp.erase(it);
		stringstream temp(tmp);
		int temp1;
		temp >> temp1; 
		if (temp1 == 999) {
			printf("Out of range!");
			clear(head);
			return;
		}	
		temp1++;
		user->ID[0] = 'U';
		for (int i = 1; i < 4; i++) {
			user->ID[i] = '0' + temp1 / pow(10, 3 - i);
			temp1 %= (int)pow(10,3-i);
		}
		user->ID[4] = '\0';
		clear(head);
	}
}
void get_new_ID_orders(orders* order) {
	orders* p = create_orders();
	orders* head=p;
	if (!p) {
		sprintf(order->ID, "T001");
	}
	else {
		for (; p->next; p = p->next);
		string tmp(p->ID);
		string::iterator it = tmp.begin();
		tmp.erase(it);
		stringstream temp(tmp);
		int temp1;
		temp >> temp1;
		if (temp1 == 999) {
			printf("Out of range!");
			clear(head);
			return;
		}
		temp1++;
		order->ID[0] = 'T';
		for (int i = 1; i < 4; i++) {
			order->ID[i] = '0' + temp1 / pow(10, 3 - i);
			temp1 %= (int)pow(10, 3 - i);
		}
		order->ID[4] = '\0';
		clear(head);
	}
}
void get_new_ID_goods(goods* good) {
	goods* p = create_goods();
	goods* head = p;
	if (!p) {
		sprintf(good->ID, "M001");
	}
	else {
		for (; p->next; p = p->next);
		string tmp(p->ID);
		string::iterator it = tmp.begin();
		tmp.erase(it);
		stringstream temp(tmp);
		int temp1;
		temp >> temp1;
		if (temp1 == 999) {
			printf("Out of range!");
			clear(head);
			return;
		}
		temp1++;
		good->ID[0] = 'M';
		for (int i = 1; i < 4; i++) {
			good->ID[i] = '0' + temp1 / pow(10, 3 - i);
			temp1 %= (int)pow(10, 3 - i);
		}
		good->ID[4] = '\0';
		clear(head);
	}
}
void get_time(goods* good) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	sprintf(good->time, "%d-%02d-%02d", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday);
}
void get_time(orders* order) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	sprintf(order->time, "%d-%02d-%02d", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday);
}
void get_time(rechargements* rechargement) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	sprintf(rechargement->time, "%d-%02d-%02d ", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday);
}
void get_time(commands* command) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	sprintf(command->time, "%d-%02d-%02d %02d:%02d:%02d ", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday,tm_t->tm_hour,tm_t->tm_min,tm_t->tm_sec);
}
void get_time(messages* temp) {
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	char t[15];
	sprintf(t, "%d-%02d-%02d ", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday);
	temp->time = t;
}
int judge_priority(const char ch1, const char ch2) {
	int i1 = 0, i2 = 0;
	if (ch1 == '+' || ch1 == '-')
		i1 = 0;
	else if (ch1 == '#')
		i1 = 2;
	else
		i1 = 1;
	if (ch2 == '+' || ch2 == '-')
		i2 = 0;
	else if (ch2 == '#')
		i2 = 2;
	else
		i2 = 1;
	return i1 - i2;
}
orders* sort_quantity_first(users* user) {
	FILE* fp = fopen("order.txt", "r");
	if (!fp) {
		printf("No such file!");
		exit(-1);
	}
	else {
		orders* head = NULL, * tail = NULL;
		char check = getc(fp);
		rewind(fp);
		if (!feof(fp))
			fscanf(fp, "orderID,commodityID,unitPrice,number,date,sellerID,buyerID,买家ID\n");
		while (!feof(fp) && check != EOF) {
			orders* p = new orders;
			p->next = NULL;
			fscanf(fp, "%4[^,],%4[^,],%lf,%d,%10[^,],%4[^,],%4[^,]\n", p->ID, p->goods_ID, &(p->currency), &(p->quantity), p->time, p->seller_ID, p->buyer_ID);
			if (strcmp(p->seller_ID, user->ID) == 0||strcmp(p->buyer_ID,user->ID)==0) {
				if (!head)
					head = p;
				else
					tail->next = p;
				tail = p;
			}
		}
		fclose(fp);
		return head;
	}
}
orders* sort_quantity_second(orders* head) {
	if (!head || !head->next)
		return head;
	orders* dummy = new orders;
	dummy->next = head;
	orders* pre = head;
	orders* cur = head->next;
	while (cur) {
		orders* tmp = dummy;
		if (pre->quantity >= cur->quantity) {
			while (tmp->next->quantity < cur->quantity)
				tmp = tmp->next;
			pre->next = cur->next;
			cur->next = tmp->next;
			tmp->next = cur;
			cur = pre->next;
		}
		else {
			pre = pre->next;
			cur = cur->next;
		}
	}
	return dummy->next;
}
string form_expressions(users* user) {
	int BEGIN = 1;
	rechargements* p0 = create_rechargements_specific(user);
	rechargements* head0 = p0;
	orders* p1 = sort_quantity_first(user);
	orders* head1 = p1;
	orders* p2 = sort_quantity_second(p1);
	orders* head2 = p2;
	string strings;
	if(p0) {
		for (; p0; p0 = p0->next) {
			strings.append(to_string(p0->money));
			strings.push_back('+');
		}
	}
	ostringstream stream;
	while(p2){
		if (!p0 && BEGIN == 1)
			;
		else
			strings.push_back('+');
		if (BEGIN == 1)
			BEGIN = 0;
		int tmp = p2->quantity;
		stream << p2->quantity;
		strings.append(stream.str());
		stream.clear(); stream.str("");
		strings.push_back('*'); strings.push_back('(');
		if (strcmp(p2->buyer_ID, user->ID) == 0)
			strings.push_back('-');
		strings.append(to_string(p2->currency));
		p2 = p2->next;
		while (p2&&p2->quantity == tmp) {
			if (strcmp(p2->seller_ID, user->ID) == 0)
				strings.push_back('+');
			else
				strings.push_back('-');
			strings.append(to_string(p2->currency));
			p2 = p2->next;
		}
		strings.push_back(')');
	}
	if (!p2&&head0) {
		strings.pop_back();
		strings.push_back(')');
	}
	clear(head0); clear(head1);
	return strings;
}
string simplify_expressions(const string& strings) {
	string new_strings;
	stack<char> stacks;
	int flag = 2;
	for (int i = 0;i<strings.length();i++) {
		if (strings[i] >= '0' && strings[i] <= '9' || strings[i] == '.') {
			flag = 1;
			while (strings[i] >= '0' && strings[i] <= '9' || strings[i] == '.') {
				new_strings.push_back(strings[i]);
				i++;
			}
			new_strings.push_back(' ');
		}
		if (strings[i] == '(') {
			stacks.push(strings[i]);
		}
		else if (strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/') {
			while (true) {
				char ch = strings[i];
				if (strings[i] == '-' && flag == 2)
					ch = '#';
				if (stacks.empty() || stacks.top() == '(') {
					stacks.push(ch); break;
				}
				else if (judge_priority(ch, stacks.top()) > 0) {
					stacks.push(ch); flag = 2; break;
				}
				else {
					new_strings.push_back(stacks.top());
					stacks.pop();
					new_strings.push_back(' ');
				}
			}
			flag = 2;
		}
		else if (strings[i] == ' ')
			continue;
		else {
			while (!stacks.empty()&&stacks.top() != '(') {
				new_strings.push_back(stacks.top());
				stacks.pop();
				new_strings.push_back(' ');
			}
			if(!stacks.empty())
				stacks.pop();
		}
	}
	while(!stacks.empty()) {
		new_strings.push_back(stacks.top());
		stacks.pop();
		new_strings.push_back(' ');
	}
	return new_strings;
}
bool judge_expressions(const string& strings) {
	int count=0,count_num=0,total_num=0,count_number_after=0;
	int flag = 0,flag0=1,special_flag=1,flag1=0,flag2=1,flag3=0;//flag用来判断符号，数字，括号（一部分），special_flag用来判断小数点，flag1用来判断'/'，flag0用来判断符号和数字的相对情况,flag2表示括号
	string tmp; double temp;//flag2判断括号情况
	for (int i = 0; i < strings.length(); i++) {
		if (isdigit(strings[i]) || strings[i] == '.') {
			special_flag = 1;
			count_number_after = 0;
			if (flag == 1) {
				return false;
			}
			count_num = 0;
			while (isdigit(strings[i]) || strings[i] == '.') {
				if (special_flag == 0 && strings[i] == '.')
					return false;
				else if (special_flag == 0&& strings[i] != '.')
					count_number_after++;
				if (strings[i] == '.')
					special_flag = 0;
				tmp.push_back(strings[i]);
				i++; count_num++;
			}
			stringstream stream(tmp);
			stream >> temp;
			if (temp == 0 && count_num > 1 && special_flag != 0 || tmp[0] == '.' || flag1 == 1 && temp == 0 || special_flag == 0 && count_number_after > 1|| special_flag == 0 && count_number_after ==0) {
				return false;
			}
			else if (flag2 == 0) {
				total_num++;
			}
			tmp.clear(); tmp.shrink_to_fit();
			flag = 1; i--; flag0 = 0;
		}
		else if (strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/') {
			if (flag == 2 && flag2 == 0 && strings[i] == '-')
				;
			else if (flag == 2) {
				return false;
			}
			if (strings[i] == '/')
				flag1 = 1;
			else if (strings[i] == '+') {
				if (flag0 == 1) {
					return false;
				}
			}
			flag = 2; flag0 = 1;
		}
		else if (strings[i] == '(' || strings[i] == ')') {
			if (strings[i] == ')') count--;
			if (count < 0) {
				return false;
			}
			//flag = 0;
			if (strings[i] == '(') {
				flag2 = 0;
				count++;
			}
			else {
				if (total_num==0) {
					return false;
				}
				else if (count == 0) {
					total_num = 0;
					flag2 = 1;
				}
			}
		}
		else if (strings[i] == ' ');
		else { 
			return false; 
		}
	}
	if (count > 0 || flag0 != 0) {
		return false;
	}
	return true;
}
string judge_expressions_remake(const string& strings) {
	int count = 0, count_num = 0, total_num = 0, count_number_after = 0;
	int flag = 0, flag0 = 1, special_flag = 1, flag1 = 0,flag2=1;//flag用来判断符号，数字，括号，special_flag用来判断小数点，flag1用来判断'/'，flag0用来判断符号和数字的相对情况
	string tmp; double temp;
	for (int i = 0; i < strings.length(); i++) {
		if (isdigit(strings[i]) || strings[i] == '.') {
			special_flag = 1;
			if (flag == 1) {
				string new_str("There are no operators between the two numbers!Operator misuse!\n");
				return new_str;
			}
			count_num = 0; count_number_after = 0;
			while (i<strings.length()&&(isdigit(strings[i]) || strings[i] == '.')) {
				if (special_flag == 0 && strings[i] == '.') {
					string str("Operator misuse!\n");
					return str;
				}
				else if (special_flag == 0 && strings[i] != '.')
					count_number_after++;
				if (strings[i] == '.')
					special_flag = 0;
				tmp.push_back(strings[i]);
				i++; count_num++;
			}
			stringstream stream(tmp);
			stream >> temp;
			if (temp == 0 && count_num > 1 && special_flag != 0 || tmp[0] == '.' || flag1 == 1 && temp == 0 || special_flag == 0 && count_number_after > 1||special_flag == 0 && count_number_after == 0) {
				string new_str;
				if (temp == 0 && count_num > 1 && special_flag != 0)
					new_str.append("0000 is invalid!\n");
				else if (tmp[0] == '.')
					new_str.append("Decimal point misuse\n");
				else if (flag1 == 1 && temp == 0)
					new_str.append("0 cannot be used as a divisor!\n");
				else if (special_flag == 0 && count_number_after == 0) {
					new_str.append("Decimal point misuse\n");
				}
				else
					new_str.append("Two decimal places cannot be entered!\n");
				return new_str;
			}
			else if(flag2==0)
				total_num++;
			tmp.clear(); tmp.shrink_to_fit();
			flag = 1; i--; flag0 = 0;
		}
		else if (strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/') {
			if (flag == 2 && flag2 == 0 && strings[i] == '-')
				;
			else if (flag == 2) {
				string new_str("Operator misuse!\n");
				return new_str;
			}
			if (strings[i] == '/')
				flag1 = 1;
			else if (strings[i] == '+') {
				if (flag0 == 1) {
					string new_str("+ Not available as a monature operator!\n");
					return new_str;
				}
			}
			flag = 2; flag0 = 1;
		}
		else if (strings[i] == '(' || strings[i] == ')') {
			if (strings[i] == ')') count--;
			if (count < 0) {
				string new_str("Parentheses do not match!\n");
				return new_str;
			}
			//flag = 0;
			if (strings[i] == '(') {
				count++;
				flag2 = 0;
			}
			else {
				if (total_num==0) {
					string new_str("There are no numbers in parentheses!\n");
					return new_str;
				}
				else if (count == 0) {
					total_num = 0;
					flag2 = 1;
				}
			}
		}
		else if (strings[i] == ' ');
		else {
			string new_str("Don't input other things other than number, letter and '.' !\n");
			return new_str;
		}
	}
	if (count > 0);
	else if (flag0 != 0);
	if (count > 0 || flag0 != 0) {
		string new_str;
		if (count > 0)
			new_str.append("Parentheses do not match!\n");
		else if (flag0 != 0)
			new_str.append("Lack number!\n");
		return new_str;
	}
	
}
string get_answer(const string& strings) {
	stack<double> stacks;
	string tmp;
	for (int i = 0; i < strings.length(); i++) {
		if (isdigit(strings[i]) || strings[i] == '.') {
			while (isdigit(strings[i]) || strings[i] == '.') {
				tmp.push_back(strings[i]);
				i++;
			}
			stringstream stream(tmp);
			double temp;
			stream >> temp;
			stacks.push(temp);
			tmp.clear(); tmp.shrink_to_fit();
		}
		else if (strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/') {
			double num1 = stacks.top(); stacks.pop();
			double num2 = stacks.top(); stacks.pop();
			double num3 = 0;
			if (strings[i] == '+')
				num3 = num1 + num2;
			else if (strings[i] == '-')
				 num3 = -num1 + num2;
			else if (strings[i] == '*')
				num3 = num1 * num2;
			else {
				if (num1 == 0) {
					string new_str("0 cannot be used as a divisor!\n");
					return new_str;
				}
				num3 = num2 / num1;
			}
			stacks.push(num3);
		}
		else if (strings[i] == '#') {
			double temp=stacks.top();
			stacks.pop();
			temp = -temp;
			stacks.push(temp);
		}
		else
			continue;
	}
	if (stacks.size() == 0) {
		string str("0");
		return str;
	}
	ostringstream stream;
	stream << stacks.top();
	string tt = stream.str(); int flag = 0;
	for (int i = 0; i < tt.length(); i++) {
		if (tt[i] == '.')
			flag = 1;
	}
	if (flag == 0)
		return tt;
	strstream ss;
	ss << fixed << setprecision(1) << stacks.top();
	string new_str;
	ss >> new_str;
	return new_str;
}
string calculator(const string& strings) {
	if (!judge_expressions(strings))
		return judge_expressions_remake(strings);
	else {
		return get_answer(simplify_expressions(strings));
	}
}
void clear(goods* p) {
	while (p) {
		goods* q = p;
		p = p->next;
		delete q;
	}
}
void clear(users* p) {
	while (p) {
		users* q = p;
		p = p->next;
		delete q;
	}
}
void clear(orders* p) {
	while (p) {
		orders* q = p;
		p = p->next;
		delete q;
	}
}
void clear(rechargements* p) {
	while (p) {
		rechargements* q = p;
		p = p->next;
		delete q;
	}
}
void clear(messages* p) {
	while (p) {
		messages* q = p;
		p = p->next;
		delete q;
	}
}
bool judge_goods_name_exist(char name[11]) {
	goods* p = create_goods();
	goods* head = p;
	for (; p && strcmp(p->name, name) != 0; p = p->next);
	if (!p) {
		printf("No matching item found!\n");
		return false;
	}
	clear(head);
	return true;
}
bool judge_goods_name_valid(char name[11]) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z')
			;
		else {
			printf("Invalid input!\n");
			return false;
		}
	}
}
bool judge_goods_ID_valid(char ID[5]) {
	if (ID[0] != 'M' || strlen(ID) < 4) {
		printf("Invalid input!\n");
		return false;
	}
	for (int i = 1; i < 4; i++) {
		if (!isdigit(ID[i])) {
			printf("Invalid input!\n");
			return false;
		}
	}
	return true;
}
bool judge_goods_ID_exist(char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	if (!p||strcmp(p->state,"removed")==0) {
		printf("No matching good found!\n");
		return false;
	}
	clear(head);
	return true;
}
bool judge_users_ID_valid(char ID[5]) {
	if (ID[0] != 'U' || strlen(ID) < 4) {
		printf("Invalid input!\n");
		return false;
	}
	for (int i = 1; i < 4; i++) {
		if (!isdigit(ID[i])) {
			printf("Invalid input!\n");
			return false;
		}
	}
	return true;
}
bool judge_users_ID_exist(char ID[5]) {
	users* p = create_users();
	users* head = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	if (!p) {
		printf("No matching user found!\n");
		return false;
	}
	clear(head);
	return true;
}
bool judge_user_name_exist(char name[11]) {
	users* p = create_users();
	users* head = p;
	if (!p) {
		printf("No user yet!\n");
		return false;
	}
	for (; p && strcmp(p->name, name) != 0; p = p->next);
	if (!p) {
		printf("No matching user found!\n");
		return false;
	}
	return true;
}
bool judge_user_name_exist(string name) {
	users* p = create_users();
	users* head = p;
	if (!p) {
		printf("No user yet!\n");
		return false;
	}
	for (; p && strcmp(p->name, name.c_str()) != 0; p = p->next);
	if (!p||strcmp(p->state,"inactive")==0) {
		printf("No matching user found!\n");
		return false;
	}
	return true;
}
bool judge_phoneNumber(char contact_details[20]) {
	for (int i = 0; i < strlen(contact_details); i++) {
		if (!isdigit(contact_details[i])) {
			printf("Invalid input!\n");
			return false;
		}
	}
	return true;
}
//User friend function
bool judge_password(const char password[21]) {
	for (int i = 0; i < strlen(password); i++) {
		if (password[i] <= 'z' && password[i] >= 'a' || password[i] >= '0' && password[i] <= '9')
			;
		else if (password[i] == ' ') {
			printf("Space is not allowed!\nInvalid input!\n");
			return false;
		}
		else
			return false;
	}
	return true;
}
bool judge_user_name_when_sign_up(const char name[11]) {
	users* p = create_users();
	users* head = p;
	if (!p) {
		return true;
	}
	for (; p; p = p->next) 
		if (strcmp(name, p->name) == 0) {
			clear(head);
			printf("Name already be used!\nTry another!\n");
			return false;
		}
	for (int i = 0; i < strlen(name);i++) {
		if (!(isalpha(name[i]) || isdigit(name[i]) || name[i] == '_')) {
			clear(head);
			return false;
		}
	}
	clear(head);
	return true;
}
User& sign_up(users* temp) {
	users* p = create_users();
	get_new_ID_users(temp);
	sprintf(temp->state, "active");
	temp->next = NULL; 
	temp->money_rest = 0.0;
	User new_user(temp);
	users* head = p;
	if (!p) {
		write_users(new_user.user);
	}
	else {
		for (; p->next; p = p->next);
		p->next = temp;
		write_users(head);
	}
	clear(head);
	printf("-----Successful registration!-----\n\n");
	return new_user;
}
bool sign_in(char name[11]) {
	users* p = create_users();
	users* head = p;
	if (!p) {
		printf("No user!\n");
		return false;
	}
	else {
		for (; p && strcmp(p->name, name) != 0; p = p->next);
		if (!p) {
			printf("No matching user!\n");
			return false;
		}
		else if (strcmp(p->state, "inactive") == 0) {
			printf("This user has already been blocked!\n");
			return false;
		}
		char password[21];
		printf("Please enter your password：");
		cin.getline(password,21);
		if (!judge_password(password)) {
			clear(head);
			return false;
		}
		else {
			if (strcmp(password, p->password) == 0)
				return true;
			printf("Wrong password!\n");
			return false;
		}
	}
	clear(head);
	return false;
}
bool judge_name(const char name[11]) {
	int count = 0;
	for (int i = 0; i < strlen(name); i++) {
		if (name[i]<='z'&&name[i]>='a'||name[i]>='A'&&name[i]<='Z')
			count++;
		else if (name[i] == ' ') {
			printf("Space is not allowed!\n");
			return false;
		}
		else {
			printf("Invalid input!\n");
			return false;
		}
	}
}
bool judge_address(const char address[41]) {
	for (int i = 0; i < strlen(address); i++) {
		if (address[i] <= 'z' && address[i] >= 'a' || address[i] >= 'A' && address[i] <= 'Z')
			;
		else if (address[i] == ' ') {
			printf("Space is not allowed!\n");
			return false;
		}
		else {
			printf("Invalid input!\n");
			return false;
		}
	}
	return true;
}
bool judge_description(char des[201]) {
	for (int i = 0; i < strlen(des);i++) {
		if (des[i] == ' ') {
			printf("Space is not allowed!\n");
			return false;
		}
		else if (des[i] == ',') {
			printf("', 'is not allowed!\n");
			return false;
		}
	}
	return true;
}
bool judge_goods_ID_buyer(char ID[5]) {
	goods* p = create_goods();
	goods* head = p;
	for (; p && strcmp(p->ID, ID) != 0; p = p->next);
	if (!p|| strcmp(p->state, "removed") == 0) {
		printf("No matching good found!\n");
		return false;
	}
	clear(head);
	return true;
}
bool judge_context(string context) {
	for (char ch : context) {
		if (ch == '#') {
			printf("'#' is not allowed in context!   Try use another symbol!\n");
			return false;
		}
	}
	return true;
}
