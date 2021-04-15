#include <iostream>
#include <string>
using namespace std;

struct Product
{
	string name;
	int quantity;
	double price;
	double total_cost = quantity * price;
	void Out();
};
//Продукт
void Product::Out() {
	cout << endl << "Информация о первом товаре:" << endl;
	cout << "\tИмя товара: " << name << endl;
	cout << "\tКоличество: " << quantity << endl;
	cout << "\tЦена: " << price << endl;
	cout << "\tОбщая стоимость: " << total_cost << endl;
}

struct Queue
{
	struct Node { Product data; Node* next; };
	Node *First = NULL;
	int count = 0, rest = 0;
	double money = 0;
	bool Push(Product);
	bool Pop(Product&);
	void Info();
};
// Очередь добаление(Push)
bool Queue::Push(Product data) {
	if (!First) {
		First = new Node;
		First->next = NULL;
		First->data = data;
		count = 1;
		rest = First->data.quantity;
	}
	else {
		Node *temp;
		temp = First;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		rest += temp->next->data.quantity;
		temp->next->next = NULL;
		count++;
	}
	return true;
}
// Очередь удаление(POP)
bool Queue::Pop(Product& data) {
	if (!First) return false;
	Node* temp = First->next;
	data = First->data;
	delete First;
	First = temp;
	count--;
	return true;
}
//Очередь инфо
void Queue::Info() {
	system("cls");
	if (!First) cout << "---> Очередь пуста" << endl;
	else {
		cout << endl << "Информация о очереди: " << endl;
		cout << "\tРазмер очереди = " << count << endl;
		cout << "\tОстаток = " << rest << endl;
		cout << "\tДеньги = " << money << endl;
		First->data.Out();
	}
	system("pause");
}

void Menu();
void Arriving(Queue&);
void Sale(Queue&);
//Меню
void Menu() {
	Queue q;
	Product p;
	int key;
	do {
		system("cls");
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "1. Товары прибывают" << endl;
		cout << "2. Продажа товаров" << endl;
		cout << "3. Отчет" << endl;
		cout << "0. Выход" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ввод: ";
		cin >> key;

		switch (key) {
		case 1: Arriving(q); break;
		case 2: Sale(q); break;
		case 3: q.Info(); break;
		case 0: {
			while (q.count) {
				q.Pop(p);
			}
		}break;
		default:  system("cls");
			cout << "Данные об ошибках, повторите попытку..." << endl;
			system("pause");
		}
	} while (key);
}
//Добавление
void Arriving(Queue &q) {
	Product p;
	string name;
	int quantity;
	double price;
	cout << "Введите технические характеристики продукта(название, количество, цена): " << endl;
	cin >> name >> quantity >> price;
	while (quantity <= 0 or price < 0) {
		cout << "Остаток и цена не могут быть меньше 0" << endl;
		cout << "Количество: ";
		cin >> quantity;
		cout << "Цена: ";
		cin >> price;
	}
	p = { name, quantity, price };
	q.Push(p);
}

//Продажа
void Sale(Queue &q) {
	Product product;
	int count;
	double price;
	product = q.First->data;
	cout << "Введите количество и стоимость единиц товара, который вы хотите приобрести: ";
	cin >> count >> price;
	while (count <= 0 || count > q.rest || price <= 0 || price <= product.price) {
		cout << "---> Не корректно введены данный <--- " << endl;
		cout << "Количество товара: ";
		cin >> count;
		cout << "Стоимость: ";
		cin >> price;
	}
	while (count) {
		if (count <= product.quantity) {
			q.money += count * (price - product.price);
			product.total_cost -= count * product.price;
			product.quantity -= count;
			q.rest -= count;
			count = 0;
			q.First->data.quantity = product.quantity;
			q.First->data.total_cost = product.total_cost;
		}
		else {
			q.money += product.quantity * (price - product.price);
			count -= product.quantity;
			q.rest -= count;
			product.quantity = 0;
		}
		if (product.quantity == 0) {
			q.Pop(product);
			product = q.First->data;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Menu();
	return 0;
}