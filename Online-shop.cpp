#include "Admin.h"
#include "User.h"

/*
������ ��������� �������� 

����������, ��� ������ ����� ������ ����� ����������� ������ ����� ����. 
�� ���� ���� ��������� ����������� � ���� "1", �� ��� ��������� ������� 
����� ���� "2" � ��.

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
		cout << "�������� ������������." << endl;
		cout << "1 - ADMIN" << endl;
		cout << "2 - USER" << endl;
		cout << "��� �����: "; cin >> choice;
		system("cls");
		switch (choice) {
		case 0: t = false; break;
		case 1: 
			for (size_t i = 0; i < 5; i++) {
				cout << "������� ������: ";
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


