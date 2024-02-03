#pragma once
#include "Admin.h"

class User : public Admin {
private:
	vector <product> cart;	 												// �������
	double total_price = 0;													// ����� ����
public:
	User() { }

	/*
	ADMIN:
	void AddProfit(double total_price);										// ���������� ������ � �������
	
	USER:
	void USER();															// ������� �������

	void ChoiceFunction();													// ����� �� �������� ��� ��������
	void Recommendation();													// ����� �������������
	void AddProductToCart();												// ���������� ��������
	void AddProductToCart(int article);										// ���������� �������� (�� �������)
	
	void SearchByName(string name);											// ����� �� ��������
	void SearchByArticle(int article);										// ����� �� �������
	
	void DisplayCart();														// ����� ������� �������
	void ClearOneProductFromCart();											// �������� ������ ������ �� �������
	void ClearAllProductsFromCart();										// ������� ����� ������
	
	void End_Purchase();													// ����� ����� ������� 
	bool Pay();																// ������
	*/

	void USER() { 
		bool amendment = true, amendment_ = true; 
		int choice;
		cout << "����� ���������� � ������� ����� ��������. �� ����� ���� ������������ �� ���������� ��������� �������," << endl;
		cout << "������� � ������� �������� ���������, �� ����: �������� ���, ������ 60, ����� � ������. ����� �� ����-" << endl;
		cout << "�������� ������� ������ ������������� ������� (��������� �� ��������: Nike, Adidas, Asics, New Balance" << endl;
		cout << "...; ����� Marcelo Miracles, Maison Margiela, Scr, Moncler, Vlone � ��). ����� � ����� �������� �����-" << endl;
		cout << "�������� ������������. ������ ��������� � ���� ������� ��� �� ������, �� ������: ��. ������� 16�, ���-" << endl;
		cout << "��� 52." << endl << endl;

		while (amendment) {
			cout << "�������� �������� ��������: " << endl;
			cout << "1 - �������� �������" << endl;
			cout << "2 - ���������� �������" << endl;
			cout << "3 - ����� �������" << endl;
			cout << "4 - ������" << endl;
			cout << "��� �����: "; cin >> choice;
			system("cls");

			Recommendation();
			switch (choice) {
			case 1:	DisplayCart(); break;
			case 2: AddProductToCart(); break;
			case 3: ChoiceFunction(); break;
			case 4: amendment = Pay(); break;
			}

		}

	}

	void ChoiceFunction() {
		string search_product;
		cout << "������� �������� ��� �������� ������, ������� �� ������� �����: " << endl;
		cin >> ws; 
		getline(cin, search_product);
		if (atoi(search_product.c_str())) {
			SearchByArticle(atoi(search_product.c_str()));
		}
		else {
			SearchByName(search_product); 
		}
	}
	void Recommendation() {
		int random_num = rand() % (products.size() - 3) + 1;
		cout << "C����� ������������� �������:" << endl;
		for (size_t i = 0; i < 3; i++) {
			//cout << i + 1 << ". " << products[random_num].Getname() << " " << products[random_num].Getprice() 
			//	<< " ���. (������� " << products[random_num].Getarticle() << ")" << endl; 
			cout << i + 1 << ". " << products[random_num].Getname() << endl;
			cout << "   ����: " << products[random_num].Getprice() << " ���. " << endl;
			cout << "   �������: " << products[random_num].Getarticle() << endl;
			random_num++;
		}
		cout << endl;
	}
	void AddProductToCart() {
		int article, choice, count, ind;
		bool amendment = false;	
		cout << "������� ������� ������: "; cin >> article; 
		system("cls");

		for (size_t i = 0; i < products.size(); i++) { 
			if (products[i].Getarticle() == article) { 
				cout << "���������� ��������: " << endl; 
				cout << products[i].Getname() << endl; 
				cout << "���� " << products[i].Getprice() << " ���." << endl; 

				cout << "�� ������� ��� ������ �������� ������ ���� ����� ? (1 - ��, 2 - ���): "; 
				cin >> choice;
				switch (choice) {
				case 1:
					cout << "������� ���-�� ����� ������: "; cin >> count; 

					if (count <= products[i].Getcount()) {
						cart.push_back(product(article, products[i].Getname(), products[i].Getprice(), count));
						ind = cart.size() - 1;
						total_price += cart[ind].Getprice() * cart[ind].Getcount();
						cart[ind].Setcount(count);
						system("cls"); 

						cout << "������. " << endl;
						cout << "���� ������� �������: " << endl;
						DisplayCart();
					}
					else {
						cout << "�������� ���������, �� ����� ���������� " << endl;
						cout << "����������� ���-�� �������: " << products[i].Getcount() << endl;
						cout << "���������� �����." << endl;
						AddProductToCart(); 
					}
					break;
				case 2: break;
				default: break;
				}

				cout << "������� �������� ��� ������� � �������? (1 - ��, 2 - ���, 3 - ��������� ����� �������): "; cin >> choice;
				system("cls");
				switch (choice) {
				case 1:	
					Recommendation(); 
					AddProductToCart();	
					break;
				case 2: break;
				case 3: End_Purchase(); break;
				default: break;
				}
				amendment = true; 
				break;
			}
		}
		if (!amendment) {
			cout << "�� ������ ������� ������ �� �������. :( " << endl;
		}
	}
	void AddProductToCart(int article) {
		int choice, count, ind;
		bool amendment = false;
		system("cls");

		for (size_t i = 0; i < products.size(); i++) {
			if (products[i].Getarticle() == article) {
				cout << "���������� ��������: " << endl;
				cout << products[i].Getname() << endl;
				cout << "���� " << products[i].Getprice() << " ���." << endl;

				cout << "�� ������� ��� ������ �������� ������ ���� ����� ? (1 - ��, 2 - ���): ";
				cin >> choice;
				switch (choice) {
				case 1:
					cout << "������� ���-�� ����� ������: "; cin >> count;

					if (count <= products[i].Getcount()) {
						cart.push_back(product(article, products[i].Getname(), products[i].Getprice(), count));
						ind = cart.size() - 1;
						total_price += cart[ind].Getprice() * cart[ind].Getcount();
						cart[ind].Setcount(count);
						system("cls");

						cout << "������. " << endl;
						cout << "���� ������� �������: " << endl;
						DisplayCart();
					}
					else {
						cout << "�������� ���������, �� ����� ���������� " << endl;
						cout << "����������� ���-�� �������: " << products[i].Getcount() << endl;
						cout << "���������� �����." << endl;
						AddProductToCart();
					}
					break;
				case 2: break;
				default: break;
				}

				cout << "������� �������� ��� ������� � �������? (1 - ��, 2 - ���, 3 - ��������� ����� �������): "; cin >> choice;
				system("cls");
				switch (choice) {
				case 1:
					Recommendation();
					AddProductToCart();
					break;
				case 2: break;
				case 3: End_Purchase(); break;
				default: break;
				}
				amendment = true;
				break;
			}
		}
		if (!amendment) {
			cout << "�� ������ ������� ������ �� �������. :( " << endl;
		}
	}

	void SearchByName(string name) { 
		//string name = "52";
		size_t count = 0;
		int choice;
		
		cout << "�� ������� \"" << name << "\" �������: " << endl;
		for (size_t i = 0; i < products.size(); i++) {
			if (Tolower(products[i].Getname()).find(Tolower(name)) != string::npos) {
				cout << ++count << ". " << products[i].Getname() << endl;
				cout << "   ����: " << products[i].Getprice() << " ���. " << endl;
				cout << "   �������: " << products[i].Getarticle() << endl;
			}
		}
		if (count == 0) {
			cout << "������." << endl;
			cout << "������ ����������� ��� ���? (�� - 1, ��� - 2) : "; cin >> choice;
			switch (choice) {
			case 1: ChoiceFunction(); break;
			case 2: break;
			default: break;
			}
		}
		else {
			cout << "������� �� �������� �����-�� ����� � ������� ? (1 - ��, 2 - ���): "; cin >> choice; 
			switch (choice) { 
			case 1: AddProductToCart(); break;
			case 2: break;
			default: break;
			}
		}
		cout << endl;
	}
	void SearchByArticle(int article) {
		bool amendment = false;														// �������� �� ��������� � ������� 
		int choice;
		for (size_t i = 0; i < products.size(); i++) {
			if (products[i].Getarticle() == article) {
				cout << "�� ������ ������� �������: " << endl;
				cout << products[i].Getname() << endl; 
				cout << "���� " << products[i].Getprice() << " ���." << endl;
				
				cout << "������� �� �������� ���� ����� � ������� ? (1 - ��, 2 - ���): "; cin >> choice;
				switch (choice) {
				case 1: AddProductToCart(article); break; 
				case 2: break;
				default: break;
				}
				amendment = true;
				break;
			}
		}

		if (!amendment) {
			cout << "�� ������ ������� ������ �� �������. :( " << endl;
		}
	}

	void DisplayCart() {
		for (size_t i = 0; i < cart.size(); i++) {
			cout << i + 1 << ". " << cart[i].Getname() << endl;
			cout << "   ����: " << cart[i].Getprice() << "x" << cart[i].Getcount() << " ���. " << endl;
			cout << "   �������: " << cart[i].Getarticle() << endl;
		}
		cout << endl << "�������� ����� � ������: " << total_price << " ���." << endl << endl;
	}
	void ClearOneProductFromCart() {
		int article, index = -1, choice;
		cout << "���� ������� �������: " << endl;
		DisplayCart(); 
		cout << endl << "������� �������� ������, ������� �� ������ �������: ";
		cin >> article;

		for (size_t i = 0; i < cart.size(); i++) {
			if (cart[i].Getarticle() == article) { index = i; break; }
		}

		if (index != -1) {
			total_price -= cart[index].Getprice() * cart[index].Getcount();
			cart.erase(cart.begin() + index); 
			

			system("cls");
			DisplayCart();
			cout << endl << "������. ��� ���������� ������� ������� ? " << endl;
			cout << "1 - ��;" << endl;
			cout << "2 - ��� ���� ��������;" << endl;
			cout << "��� �����: ";
			cin >> choice;

			switch (choice) {
			case 1: break;
			case 2:
				system("cls");
				ClearOneProductFromCart();
				break;
			}
		}
		else {
			cout << endl << "������� ������ ����������� ��� ������ �� ������. ���������� ��� �������";
			for (int i = 0; i < 3; i++) { cout << "."; Sleep(1000); }
			cout << endl;
			system("cls");
		}

	}
	void ClearAllProductsFromCart() {
		int choice; 
		cout << "�� ����� ������ ������� ��� ��������? ��� ����� (1 - ��, 2 - ���): "; cin >> choice; 
		switch (choice) {
		case 1:
			cart.clear();
			cout << "������." << endl; 
			break;
		case 2: break;
		default: break;
		}
	}

	void End_Purchase() {
		cout << "��� ���� �������� �������: " << endl;
		DisplayCart();

		int choice;
		cout << "��� ���������� ���� ������� ? (1 - ��, 2 - ������������� �������): ";
		cin >> choice;
		switch (choice) {
		case 1:	break;
		case 2: 
			cout << "�������� ��������. " << endl;
			cout << "1 - �������� �����" << endl;
			cout << "2 - �������� ���� �����" << endl;
			cout << "3 - �������� ���� ������" << endl;
			cout << "4 - ��������� �������" << endl;

			cout << "��� �����: "; cin >> choice;

			switch (choice) {
			case 1: AddProductToCart(); break;
			case 2: ClearOneProductFromCart(); break;
			case 3: ClearAllProductsFromCart(); break;
			case 4: break;
			default: break;
			}

			break;
		default: break;
		}

	}
	bool Pay() {
		int choice;
		cout << "� ������ c ������ ��������: " << total_price * 1.2 << " ���. �� ����� ...73552 812 " << endl;
		cout << "������ ��������� ? (52 - ��): "; cin >> choice;
		if (choice == 52) {
			cout << "������� ��� �������� ��� �������. �� ������� ���� ���. " << endl;
			system("cls");
			AddProfit(total_price * 0.2);
			return false;
		}
		return true;
	}

};
