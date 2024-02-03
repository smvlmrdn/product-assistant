#pragma once
#include "Admin.h"

class User : public Admin {
private:
	vector <product> cart;	 												// Корзина
	double total_price = 0;													// Общая цена
public:
	User() { }

	/*
	ADMIN:
	void AddProfit(double total_price);										// Добавление записи о прибыли
	
	USER:
	void USER();															// Главная функция

	void ChoiceFunction();													// Поиск по артикулю или названию
	void Recommendation();													// Вывод рекоммендаций
	void AddProductToCart();												// Добавление продукта
	void AddProductToCart(int article);										// Добавление продукта (по артиклю)
	
	void SearchByName(string name);											// Поиск по названию
	void SearchByArticle(int article);										// Поиск по артиклю
	
	void DisplayCart();														// Вывод корзины товаров
	void ClearOneProductFromCart();											// Удаление одного товара из корзины
	void ClearAllProductsFromCart();										// Очистка всего списка
	
	void End_Purchase();													// Около конец покупки 
	bool Pay();																// Оплата
	*/

	void USER() { 
		bool amendment = true, amendment_ = true; 
		int choice;
		cout << "Добро пожаловать в магазин нашей компании. Мы ведем свою деятельность на территории Псковской области," << endl;
		cout << "работая с многоми здешними филиалами, по типу: Академия ТОП, Шаурма 60, Сфера и прочие. Также мы пред-" << endl;
		cout << "ставляем широкий спектр разнообразных товаров (кроссовки от компаний: Nike, Adidas, Asics, New Balance" << endl;
		cout << "...; Бренд Marcelo Miracles, Maison Margiela, Scr, Moncler, Vlone и пр). Товар в нашем магазине исклю-" << endl;
		cout << "чительно оригинальный. Можете убедиться в этом посетив нас во Пскове, по адресу: ул. Рижская 16а, кор-" << endl;
		cout << "пус 52." << endl << endl;

		while (amendment) {
			cout << "Выберите желаемую операцию: " << endl;
			cout << "1 - Просмотр корзины" << endl;
			cout << "2 - Добавление товаров" << endl;
			cout << "3 - Поиск товаров" << endl;
			cout << "4 - Оплата" << endl;
			cout << "Ваш выбор: "; cin >> choice;
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
		cout << "Введите название или артикуль товара, который вы желаете найти: " << endl;
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
		cout << "Cписок рекомендуемых товаров:" << endl;
		for (size_t i = 0; i < 3; i++) {
			//cout << i + 1 << ". " << products[random_num].Getname() << " " << products[random_num].Getprice() 
			//	<< " руб. (артикул " << products[random_num].Getarticle() << ")" << endl; 
			cout << i + 1 << ". " << products[random_num].Getname() << endl;
			cout << "   Цена: " << products[random_num].Getprice() << " руб. " << endl;
			cout << "   Артикул: " << products[random_num].Getarticle() << endl;
			random_num++;
		}
		cout << endl;
	}
	void AddProductToCart() {
		int article, choice, count, ind;
		bool amendment = false;	
		cout << "Введите артикул товара: "; cin >> article; 
		system("cls");

		for (size_t i = 0; i < products.size(); i++) { 
			if (products[i].Getarticle() == article) { 
				cout << "Добавление продукта: " << endl; 
				cout << products[i].Getname() << endl; 
				cout << "Цена " << products[i].Getprice() << " руб." << endl; 

				cout << "Вы уверены что хотите добавить именно этот товар ? (1 - да, 2 - нет): "; 
				cin >> choice;
				switch (choice) {
				case 1:
					cout << "Введите кол-во этого товара: "; cin >> count; 

					if (count <= products[i].Getcount()) {
						cart.push_back(product(article, products[i].Getname(), products[i].Getprice(), count));
						ind = cart.size() - 1;
						total_price += cart[ind].Getprice() * cart[ind].Getcount();
						cart[ind].Setcount(count);
						system("cls"); 

						cout << "Готово. " << endl;
						cout << "Ваша текущая корзина: " << endl;
						DisplayCart();
					}
					else {
						cout << "Операция отклонена, тк товар закончился " << endl;
						cout << "Действующее кол-во товаров: " << products[i].Getcount() << endl;
						cout << "Попробуйте снова." << endl;
						AddProductToCart(); 
					}
					break;
				case 2: break;
				default: break;
				}

				cout << "Желаете добавить еще товаров в корзину? (1 - да, 2 - нет, 3 - закончить выбор товаров): "; cin >> choice;
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
			cout << "По вашему запросу ничего не нашлось. :( " << endl;
		}
	}
	void AddProductToCart(int article) {
		int choice, count, ind;
		bool amendment = false;
		system("cls");

		for (size_t i = 0; i < products.size(); i++) {
			if (products[i].Getarticle() == article) {
				cout << "Добавление продукта: " << endl;
				cout << products[i].Getname() << endl;
				cout << "Цена " << products[i].Getprice() << " руб." << endl;

				cout << "Вы уверены что хотите добавить именно этот товар ? (1 - да, 2 - нет): ";
				cin >> choice;
				switch (choice) {
				case 1:
					cout << "Введите кол-во этого товара: "; cin >> count;

					if (count <= products[i].Getcount()) {
						cart.push_back(product(article, products[i].Getname(), products[i].Getprice(), count));
						ind = cart.size() - 1;
						total_price += cart[ind].Getprice() * cart[ind].Getcount();
						cart[ind].Setcount(count);
						system("cls");

						cout << "Готово. " << endl;
						cout << "Ваша текущая корзина: " << endl;
						DisplayCart();
					}
					else {
						cout << "Операция отклонена, тк товар закончился " << endl;
						cout << "Действующее кол-во товаров: " << products[i].Getcount() << endl;
						cout << "Попробуйте снова." << endl;
						AddProductToCart();
					}
					break;
				case 2: break;
				default: break;
				}

				cout << "Желаете добавить еще товаров в корзину? (1 - да, 2 - нет, 3 - закончить выбор товаров): "; cin >> choice;
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
			cout << "По вашему запросу ничего не нашлось. :( " << endl;
		}
	}

	void SearchByName(string name) { 
		//string name = "52";
		size_t count = 0;
		int choice;
		
		cout << "По запросу \"" << name << "\" нашлось: " << endl;
		for (size_t i = 0; i < products.size(); i++) {
			if (Tolower(products[i].Getname()).find(Tolower(name)) != string::npos) {
				cout << ++count << ". " << products[i].Getname() << endl;
				cout << "   Цена: " << products[i].Getprice() << " руб. " << endl;
				cout << "   Артикул: " << products[i].Getarticle() << endl;
			}
		}
		if (count == 0) {
			cout << "Ничего." << endl;
			cout << "Хотите попробовать еще раз? (да - 1, нет - 2) : "; cin >> choice;
			switch (choice) {
			case 1: ChoiceFunction(); break;
			case 2: break;
			default: break;
			}
		}
		else {
			cout << "Желаете ли добавить какой-то товар в корзину ? (1 - да, 2 - нет): "; cin >> choice; 
			switch (choice) { 
			case 1: AddProductToCart(); break;
			case 2: break;
			default: break;
			}
		}
		cout << endl;
	}
	void SearchByArticle(int article) {
		bool amendment = false;														// Проверка на изменения в функции 
		int choice;
		for (size_t i = 0; i < products.size(); i++) {
			if (products[i].Getarticle() == article) {
				cout << "По вашему запросу нашлось: " << endl;
				cout << products[i].Getname() << endl; 
				cout << "Цена " << products[i].Getprice() << " руб." << endl;
				
				cout << "Желаете ли добавить этот товар в корзину ? (1 - да, 2 - нет): "; cin >> choice;
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
			cout << "По вашему запросу ничего не нашлось. :( " << endl;
		}
	}

	void DisplayCart() {
		for (size_t i = 0; i < cart.size(); i++) {
			cout << i + 1 << ". " << cart[i].Getname() << endl;
			cout << "   Цена: " << cart[i].Getprice() << "x" << cart[i].Getcount() << " руб. " << endl;
			cout << "   Артикул: " << cart[i].Getarticle() << endl;
		}
		cout << endl << "Конечная сумма к оплате: " << total_price << " руб." << endl << endl;
	}
	void ClearOneProductFromCart() {
		int article, index = -1, choice;
		cout << "Ваша текущая корзина: " << endl;
		DisplayCart(); 
		cout << endl << "Введите артикуль товара, который вы хотите удалить: ";
		cin >> article;

		for (size_t i = 0; i < cart.size(); i++) {
			if (cart[i].Getarticle() == article) { index = i; break; }
		}

		if (index != -1) {
			total_price -= cart[index].Getprice() * cart[index].Getcount();
			cart.erase(cart.begin() + index); 
			

			system("cls");
			DisplayCart();
			cout << endl << "Готово. Вас устраивает текущая корзина ? " << endl;
			cout << "1 - да;" << endl;
			cout << "2 - еще одно удаление;" << endl;
			cout << "Ваш выбор: ";
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
			cout << endl << "Артикул введен неправильно или вообще не введен. Возвращаем вас обратно";
			for (int i = 0; i < 3; i++) { cout << "."; Sleep(1000); }
			cout << endl;
			system("cls");
		}

	}
	void ClearAllProductsFromCart() {
		int choice; 
		cout << "Вы точно хотите удалить все продукты? Ваш выбор (1 - да, 2 - нет): "; cin >> choice; 
		switch (choice) {
		case 1:
			cart.clear();
			cout << "Готово." << endl; 
			break;
		case 2: break;
		default: break;
		}
	}

	void End_Purchase() {
		cout << "Вот ваша конечная корзина: " << endl;
		DisplayCart();

		int choice;
		cout << "Вас устраивает ваша корзина ? (1 - да, 2 - редактировать корзину): ";
		cin >> choice;
		switch (choice) {
		case 1:	break;
		case 2: 
			cout << "Выберите операцию. " << endl;
			cout << "1 - добавить товар" << endl;
			cout << "2 - очистить один товар" << endl;
			cout << "3 - очистить весь список" << endl;
			cout << "4 - вернуться обратно" << endl;

			cout << "Ваш выбор: "; cin >> choice;

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
		cout << "К оплате c учетом комиссий: " << total_price * 1.2 << " руб. на карту ...73552 812 " << endl;
		cout << "Оплата совершена ? (52 - да): "; cin >> choice;
		if (choice == 52) {
			cout << "Спасибо что посетили наш магазин. Мы безумно рады вам. " << endl;
			system("cls");
			AddProfit(total_price * 0.2);
			return false;
		}
		return true;
	}

};
