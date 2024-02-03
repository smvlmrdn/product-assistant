#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

const char* path_to_names_file = "names.txt";
const char* path_to_numbers_file = "numbers.txt";
const char* path_to_profit_file = "profit.txt";
using namespace std;

string Tolower(string str) {
	string s = str; 
	transform(s.begin(), s.end(), s.begin(), tolower); 
	return s;
}

class product {
private:
	int article;															// Артикул  проудкта
	string name;															// Название продукта 
	double price;															// Прайс (стоимость)
	int count;																// Кол-во  продуктов 
public:
	product(int newarticle, string newname, double newprice, int newcount) 
		: article(newarticle), name(newname), price(newprice),  count(newcount) {}

	int Getarticle() { return article; }
	string Getname() { return name; }
	double Getprice() { return price; }
	int Getcount() { return count; }

	void Setcount(int newcount) { count -= newcount; }

	~product() {}
};

class Admin {
private:
	vector <double> profit;													// Список прибылей
	double All_profit;														// Общая прибыль
public:
	vector <product> products;												// Список продуктов

	Admin() {
		int newarticle; string newname; int newprice; int newcount;
		fstream fnames(path_to_names_file, ios::in);
		fstream fnumbers(path_to_numbers_file, ios::in);
		if (!fnumbers || !fnames) {
			cout << "Файл не открылся для чтения !!!" << endl;
			exit(1);
		}
		while (fnumbers >> newarticle >> newprice >> newcount && getline(fnames, newname)) { 
			products.push_back(product(newarticle, newname, newprice, newcount));
			//cout << newarticle << " " << newprice << " " << newsize << " " << newcount << endl;
		}
		
		fnames.close();
		fnumbers.close();

		double newprofit;
		fstream fprofit(path_to_profit_file, ios::in);
		if (!fprofit) { 
			cout << "Файл не открылся для чтения !!!" << endl; 
			exit(1); 
		}
		while (fprofit >> newprofit) {
			profit.push_back(newprofit);
		}
		fprofit.close();

	}
	~Admin() {
		fstream fnames(path_to_names_file, ios::out);
		fstream fnumbers(path_to_numbers_file, ios::out);
		if (!fnumbers || !fnames) {
			cout << "Файл не открылся для записи !!!" << endl;
			exit(1);
		}
		for (size_t i = 0; i < products.size(); i++) {
			fnumbers << products[i].Getarticle() << " "
				<< products[i].Getprice() << " "
				<< products[i].Getcount() << endl;
			fnames << products[i].Getname() << endl;
		}
		fnames.close();
		fnumbers.close();

		profit.push_back(All_profit); 
		fstream fprofit(path_to_profit_file, ios::out);
		if (!fprofit) {
			cout << "Файл не открылся для записи !!!" << endl;
			exit(1);
		}
		for (size_t i = 0; i < profit.size(); i++) {
			fprofit << profit[i] << endl; 
		}

		fprofit.close();
	}

	/*
	void ADMIN();															// Главная функция

	void Display();															// Вывод всех товаров

	void Addproduct();														// Добалвение товара 
	void ClearOneProduct();													// Удаление одного продукта, определенного по артиклю
	void ClearAllProducts();												// Удаление всех продутков
	void DisplayProfit();													// Вывод прибыли на экран
	void ClearProfit();														// Удаление записи о прибыли
	
	void AddProfit(double total_price);										// Добавление записи о прибыли	    (for USER)
	*/
	
	void ADMIN() {
		bool amendment = true, amendment_ = true;
		int choice;

		while (amendment) {
			cout << "Выберите вкладку." << endl;
			cout << "1 - Товары;" << endl;
			cout << "2 - Прибыль;" << endl;
			cout << "3 - Выход" << endl;
			cout << "Ваш выбор: "; cin >> choice;
			system("cls");
			switch (choice) {
			case 1:
				while (amendment_) {
					Display();
					cout << endl << "Выберите действие." << endl;
					cout << "1 - Добавление одного товара;" << endl;
					cout << "2 - Очистка одного определенного товара, по артиклю;" << endl;
					cout << "3 - Очистка всего списка товаров;" << endl;
					cout << "4 - Вернуться обратно." << endl;
					cout << "Введите номер операции: "; cin >> choice;
					system("cls");

					switch (choice) {
					case 1:	Addproduct(); break;
					case 2:	ClearOneProduct(); break;
					case 3:	ClearAllProducts(); break;
					case 4:	amendment_ = false; break;
					}
					system("cls");

				}

				amendment_ = true;
				break;
			case 2:
				while (amendment_) {
					DisplayProfit();
					cout << endl << "Выберите действие." << endl;
					cout << "1 - Очистка списка ежедневных прибылей;" << endl;
					cout << "2 - Вернуться обратно." << endl;
					cout << "Введите номер операции: "; cin >> choice;
					system("cls");

					switch (choice) {
					case 1:	ClearProfit(); break;
					case 2: amendment_ = false; break;
					}
				}

				amendment_ = true;
				break;
			case 3:
				amendment = false; break;
			}
		}
	}

	void Display() {
		cout << "Список товаров:" << endl;
		for (size_t i = 0; i < products.size(); i++) {
			cout << "Товар |52|: " 
				<< products[i].Getarticle() << " " 
				<< products[i].Getname()    << " "
				<< products[i].Getprice()   << " " 
				<< products[i].Getcount()   << endl;
		}
	}

	void Addproduct() {
		string newname; int newprice; int newcount;
		int newarticle = products.size() + 10001;
		cout << "Добавление продуктов." << endl;
		cout << "Введите название вашего товара:   "; cin >> ws;
		getline(cin, newname);
		cout << "Введите стоимость вашего товара:  "; cin >> newprice;
		cout << "Введите кол-во ваших товаров:     "; cin >> newcount;

		products.push_back(product(newarticle, newname, newprice, newcount));

		cout << "Товар готов. Проверьте его в списке новых товаров." << endl;
		Display();
	}
	void ClearOneProduct() {
		int article, index = -1, choice; 
		Display();
		cout << endl << "Введите артикуль товара, который вы хотите удалить: ";
		cin >> article;

		for (size_t i = 0; i < products.size(); i++) {
			if (products[i].Getarticle() == article) { index = i; break; }
		}

		if (index != -1) {
			products.erase(products.begin() + index);

			system("cls");
			Display();
			cout << endl << "Готово. Вас устраивает полученный список ? " << endl;
			cout << "1 - да;" << endl;
			cout << "2 - еще одно удаление;" << endl;
			cout << "Ваш выбор: ";
			cin >> choice;

			switch (choice) {
			case 1: break;
			case 2:
				system("cls");
				ClearOneProduct();
				break;
			}
		}
		else {
			cout << endl << "Артикул введен неправильно или вообще не введен. Возвращаем вас обратно";
			for (int i = 0; i < 3; i++) { cout << "."; Sleep(1000); }
			cout << endl;
			system("cls");
		}
		
	}
	void ClearAllProducts() {
		int choice;
		cout << "Вы точно хотите удалить все продукты? Ваш выбор (1 - да, 2 - нет): "; cin >> choice;
		switch (choice) {
		case 1: 
			products.clear(); 
			cout << "Готово." << endl; 
			break;
		case 2: break;
		default: break;
		}
	}
	void DisplayProfit() {
		double total_profit = 0;
		cout << "Прибыль за день номер: " << endl;
		for (size_t i = 0; i < profit.size(); i++) {
			cout << i + 1 << ". " << profit[i] << endl;
			total_profit += profit[i];
		}
		cout << "Общая суммарная прибыль: " << total_profit << endl;
	}
	void ClearProfit() {
		int choice;
		cout << "Вы точно хотите удалить записи о прибыли? Ваш выбор (1 - да, 2 - нет): "; cin >> choice;
		switch (choice) {
		case 1: profit.clear();
			cout << "Готово." << endl;
			break;
		case 2: break;
		}
	}

	void AddProfit(double total_price) {
		All_profit += total_price;
	}

};
