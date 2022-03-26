#include<iostream>
#include<sstream>
#include "struct.h"
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include<cstring>
#include "administrator.h"
#include "function.h"
using namespace std;
int main()
{
	/*users* p = new users;
	sprintf(p->state, "inactive");
	sprintf(p->address, "nanjing");*/
	FILE* fp = fopen("commodity.txt", "r");
	if (!fp) {
		fp = fopen("commodity.txt", "w");
		fclose(fp);
	}
	fp = fopen("user.txt", "r");
	if (!fp) {
		fp = fopen("user.txt", "w");
		fclose(fp);
	}
	fp = fopen("commands.txt", "r");
	if (!fp) {
		fp = fopen("commands.txt", "w");
		fclose(fp);
	}
	fp = fopen("order.txt", "r");
	if (!fp) {
		fp = fopen("order.txt", "w");
		fclose(fp);
	}
	fp = fopen("rechargement.txt", "r");
	if (!fp) {
		fp = fopen("rechargement.txt", "w");
		fclose(fp);
	}
	fp = fopen("shoppingcart.txt", "r");
	if (!fp) {
		fp = fopen("shoppingcart.txt", "w");
		fclose(fp);
	}
	fp = fopen("messa.txt", "r");
	if (!fp) {
		fp = fopen("messa.txt", "w");
		fclose(fp);
	}
	int choice;
	char check;
	administrator ad;
	while (true) {
		main_title();
		printf("Please enter the action:");
		if (cin >> choice) {
			check = getchar();
			if (check != '\n') {
				printf("Invalid input!\nPlease try again!\n");
				continue;
			}
			users* p = create_users();
			users* head = p;
			switch (choice) {
			case 1:
				char name[11], password[21];
				printf("Please enter your user name:"); cin.getline(name,11);
				printf("Please enter your password:"); cin.getline(password,21);
				if (ad.log_in(name, password)) {
					printf("-----Successful login!-----\n");
					ad.administrator_interface();
				}
				break;
			case 2:
				char user_name[11];
				for (int i = 0; i < 3; i++) {
					printf("Please enter your user name:"); cin.getline(user_name,11);
					if (judge_goods_name_valid(user_name)) {
						if (judge_user_name_when_sign_up(user_name)) {
							users* new_user_pointer = new users;
							sprintf(new_user_pointer->name, user_name);
							printf("Please enter your password:"); cin.getline(new_user_pointer->password, 21);
							if (!judge_password(new_user_pointer->password)) {
								break;
							}
							printf("Please enter your contact details:"); cin.getline(new_user_pointer->contact_details, 21);
							if (!judge_phoneNumber(new_user_pointer->contact_details)) {
								break;
							}
							printf("Please enter the address:"); cin.getline(new_user_pointer->address, 41);
							if (!judge_address(new_user_pointer->address)) {
								break;
							}
							get_new_ID_users(new_user_pointer);
							sprintf(new_user_pointer->state, "active");
							new_user_pointer->next = NULL;
							new_user_pointer->money_rest = 0.0;
							if (!p) {
								write_users(new_user_pointer);
							}
							else {
								for (; p->next; p = p->next);
								p->next = new_user_pointer;
								write_users(head);
							}
							printf("-----Successful registration!-----\n\n");
							User temp(new_user_pointer);
							temp.user_interface();
							new_user_pointer = nullptr;
							break;
						}
						else {
							printf("Name already used, please try another!\n");
						}
					}
				}
				break;
			case 3:
				char user_name_already[11];
				if (!p) {
					printf("No user yet!   Please sign up!\n");
					break;
				}
				printf("Please enter your user name:");cin.getline(user_name_already,11);
				if (sign_in(user_name_already)) {
					for (; p && strcmp(p->name, user_name_already) != 0; p = p->next);
					User user_already(p);
					printf("-----Successful login!-----\n");
					user_already.user_interface();
				}
				break;
			case 4:
				exit(0);
				break;
			default:
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
}