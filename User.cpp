#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include "function.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
using namespace std;
void User::check_personal_information() {
	printf("*******************************************************\n");
	printf("username:%s\n", user->name);
	printf("contact details:%s\n", user->contact_details);
	printf("address:%s\n", user->address);
	stringstream ss; 
	ss << fixed << setprecision(1) << stod(get_answer(simplify_expressions(form_expressions(user))).c_str());
	string new_str;
	ss >> new_str;
	printf("balance:%s\n", new_str.c_str());
	printf("*******************************************************\n\n");
}
void User::recharge(double rechargement) {
	rechargements* p = create_rechargements();
	rechargements* q = new rechargements;
	q->money = rechargement; q->next = NULL; get_time(q); sprintf(q->ID, this->user->ID);
	if (!p) {
		write_rechargements(q);
	}
	else {
		rechargements* head = p;
		for (; p->next; p = p->next);
		p->next = q;
		write_rechargements(head);
	}; 
	users* p0 = create_users();
	users* head1 = p0;
	for (; p0 && strcmp(p0->ID, user->ID) != 0; p0 = p0->next);
	p0->money_rest += rechargement;
	write_users(head1);
	printf("Successful rechargement!\nCurrent balance:  %.1lf\n\n", p0->money_rest);
}
void User::change_personal_information() {
	printf("Please enter the attributes you want to modify  (1.username  2.address  3.contact details):");
	int choice, judge0 = 0, judge1 = 0; judge0 = scanf("%d", &(choice)); judge1 = getchar();
	if (!judge0 || judge1 != 13 && judge1 != 10) {
		printf("invalid input!\n\n");
		char c;
		while ((c = getchar()) != EOF && c != '\n');
		return;
	}
	else {
		string name,address,contact_details;
		users* p = create_users(); users* head = p; users* tmp = head;
		for (; p&&strcmp(p->ID,this->user->ID)!=0; p = p->next);
		switch (choice) {
		case 1:
			printf("Please enter the modified username:"); 
			getline(cin,name);
			if (name.size() > 10) {
				printf("Invalid input!\n");
				cin.sync(); cin.clear();
				break;
			}
			if (judge_name((char*)name.c_str()) && judge_user_name_when_sign_up((char*)name.c_str())) {
				sprintf(p->name, (char*)name.c_str());
				sprintf(user->name, (char*)name.c_str());
				printf("Successful modification!\n\n");
				write_users(tmp);
			}
			else
				printf("Modify failed!\n\n");
			break;
		case 2:
			printf("Please enter the modified address:");
			getline(cin,address);
			if (address.size() > 40) {
				printf("Invalid input!\n");
				cin.sync(); cin.clear();
				break;
			}
			if (!judge_address((char*)address.c_str())) {
				cin.sync(); cin.clear();
				break;
			}
			sprintf(p->address, (char*)address.c_str());
			sprintf(user->address, (char*)address.c_str());
			printf("Successful modification!\n\n");
			write_users(tmp);
			break;
		case 3:
			printf("Please enter the modified contact details:"); 
			getline(cin,contact_details);
			if (contact_details.size() > 20) {
				printf("Invalid input!\n");
				cin.sync(); cin.clear();
				break;
			}
			if (!judge_phoneNumber((char*)contact_details.c_str())) {
				printf("Invalid input!\n");
				break;
			}
			sprintf(p->contact_details, (char*)contact_details.c_str());
			sprintf(user->contact_details, (char*)contact_details.c_str());
			printf("Successful modification!\n\n");
			write_users(tmp);
			break;
		default:
			printf("Invalid input!\n");
			cin.clear(); cin.sync();
		}	
		clear(head);
	}
}
void User::change_password() {
	printf("Please enter the password that you wanna change to:");
	string password;
	getline(cin, password);
	if (!judge_password((char*)password.c_str())) {
		return;
	}
	sprintf(user->password, password.c_str());
	users* p = create_users();
	users* head = p;
	for (; p && strcmp(p->ID, user->ID) != 0; p = p->next);
	sprintf(p->password, password.c_str());
	write_users(head);
	clear(head);
	printf("You have changed your password successfully!\n");
}
void User::message_interface() {
	int choice;
	char check;
	string name;
	while (true) {
		message_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				continue;
			}
			switch (choice) {
			case 1:
				printf("Please enter the username that you want to send a message:");
				getline(cin, name);
				if (judge_name((char*)name.c_str()) && judge_user_name_exist(name))
					leave_messages(name);
				break;
			case 2:
				check_messages_unread();
				break;
			case 3:
				check_all_messages();
				break;
			case 4:
				printf("Please enter the username that you want to check on message:");
				getline(cin, name);
				if (judge_name((char*)name.c_str()) && judge_user_name_exist((char*)name.c_str()))
					check_other_messages(name);
				break;
			case 5:
				return;
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
void User::user_interface() {
	int choice;
	char check;
	string str;
	Buyer p(user);
	Seller q(user);
	while (true) {
		user_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				continue;
			}
			switch (choice) {
			case 1:
				p.buyer_interface();
				break;
			case 2:
				q.seller_interface();
				break;
			case 3:
				personal_interface();
				break;
			case 4:
				message_interface();
			case 5:
				return;
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
void User::personal_interface() {
	int choice;
	char check,buf;
	string str,rechargement;
	int flag = 0; int count = 0;
	while (true) {
		personal_center_title();
		printf("Please enter your action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				cin.clear(); cin.sync();
				while ((buf = getchar()) != EOF && buf != '\n');
				continue;
			}
			switch (choice) {
			case 1:
				check_personal_information();
				break;
			case 2:
				change_personal_information();
				break;
			case 3:
				printf("Please enter the recharge amount:");
				//getchar();
				getline(cin, rechargement);
				count = 0;flag = 0; 
				for (int i = 0; i < rechargement.size(); i++) {
					if (flag == 1)
						count++;
					if (rechargement[i] == '.')
						flag = 1;
				}
				if (count > 1) {
					printf("You cannot enter two decimal places!\n");
					break;
				}
				if (stod(rechargement) <= 0) {
					printf("You cannot enter negative number!\n");
					break;
				}
				recharge(stod(rechargement));
				break;
			case 4:
				change_password();
				break;
			case 5:
				return;
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
//message system
messages* User::create_messages() {
	ifstream fp("messages.txt", ios::in);
	if (!fp.is_open()){
		printf("Fail to open!\n");
		exit(-1);
	}
	string temp;
	int i = 0;
	messages* head = nullptr, * tail = nullptr;
	while (getline(fp, temp)) {
		messages* p = new messages;
		i = temp.find('#');
		p->time = temp.substr(0, i);
		temp = temp.substr(i + 1, INT_MAX);
		i = temp.find('#');
		p->other_name = temp.substr(0, i);
		temp = temp.substr(i + 1, INT_MAX);
		i = temp.find('#');
		p->self_name = temp.substr(0, i);
		temp = temp.substr(i + 1, INT_MAX);
		i = temp.find('#');
		p->state = temp.substr(0, i);
		temp = temp.substr(i + 1, INT_MAX);
		p->context = temp;
		p->next = nullptr;
		if (!head)
			head = p;
		else
			tail->next = p;
		tail = p;
	}
	return head;
}
void User::write_messages(messages* p) {
	ofstream fp("messages.txt", ios::out);
	if (!fp.is_open()) {
		printf("Fail to open!\n");
		exit(-1);
	}
	string temp;
	for (; p;p=p->next) {
		fp << p->time;
		fp << '#';
		fp << p->other_name;
		fp << '#';
		fp << p->self_name;
		fp << '#';
		fp << p->state;
		fp << '#';
		fp << p->context;
		fp << '\n';
	}
}
void User::leave_messages(string name) {
	printf("Please enter your message:");
	messages* p = create_messages();
	messages* head = p;
	messages* temp = new messages;
	temp->next = nullptr;
	getline(cin, temp->context);
	if (!judge_context(temp->context)) {
		return;
	}
	temp->other_name = name;
	temp->self_name = user->name;
	get_time(temp);
	temp->state = "Unread";
	if (!p) {
		write_messages(temp);
		return;
	}
	for (; p->next; p = p->next);
	p->next = temp;
	write_messages(head);
	clear(head);
	printf("You have successfully left a message to %s!\n",name.c_str());
	return;
}
void User::check_messages_unread() {
	messages* p = create_messages();
	messages* head = p;
	int BEGIN = 0;
	for (; p; p = p->next) {
		if (p->other_name == user->name&&p->state=="Unread") {
			printf("%s  %s\n%s\n\n", p->self_name.c_str(), p->time.c_str(), p->context.c_str());
			p->state = "read";
			BEGIN = 1;
		}
	}
	write_messages(head);
	if (BEGIN != 1) {
		printf("No messages yet!  Try leave some!\n");
	}
	clear(head);
}
void User::check_all_messages() {
	messages* p = create_messages();
	messages* head = p;
	int BEGIN = 0;
	for (; p; p = p->next) {
		if (p->other_name == user->name||p->self_name==user->name) {
			printf("%s  to  %s  %s\n%s\n\n", p->self_name.c_str(),p->other_name.c_str(), p->time.c_str(), p->context.c_str());
			if(p->state=="Unread"&&p->other_name==user->name)
				p->state = "read";
			BEGIN = 1;
		}
	}
	write_messages(head);
	if (BEGIN != 1) {
		printf("No messages yet!  Try leave some!\n");
	}
	clear(head);
}
void User::check_other_messages(string name) {
	messages* p = create_messages();
	messages* head = p;
	int BEGIN = 0;
	for (; p; p = p->next) {
		if (p->other_name == user->name && p->self_name==name) {
			printf("%s  %s\n%s\n\n", p->self_name.c_str(), p->time.c_str(), p->context.c_str());
			p->state = "read";
			BEGIN = 1;
		}
	}
	write_messages(head);
	if (BEGIN != 1) {
		printf("No messages yet!  Try leave some!\n");
	}
	clear(head);
}