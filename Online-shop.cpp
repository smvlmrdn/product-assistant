#include "Admin.h"
#include "User.h"

/*
Данная программа является 

Условимься, что каждый новый запуск будет происходить каждый новый день. 
То есть если программа запуститься в день "1", то при следующем запуске 
будет день "2" и тд.

*/

const char* PASS = "GLOCKI_52";

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	srand(time(NULL));
	Admin NGG_company;
	User guest;
	bool t = true;
	int choice;
	string password;

	while (t) {
		cout << "Выберите пользователя." << endl;
		cout << "1 - ADMIN" << endl;
		cout << "2 - USER" << endl;
		cout << "Ваш выбор: "; cin >> choice;
		system("cls");
		switch (choice) {
		case 0: t = false; break;
		case 1: 
			for (size_t i = 0; i < 5; i++) {
				cout << "Введите пароль: ";
				cin >> ws;
				getline(cin, password);
				if (password == PASS) {
					i = 6;
					NGG_company.ADMIN();
				}
			}
			break;
		case 2: 
			guest.USER(); 
			break;
		}
	}

	return 0;
}


