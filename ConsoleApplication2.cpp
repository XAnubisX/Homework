#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct Ball {
	string color;
	double price;
	string proz;
	double size;
	void Out();
};

void Ball::Out() {
	cout << "\tЦвет: " << color << endl;
	cout << "\tЦена: " << price << endl;
	cout << "\tПроизводитель: " << proz << endl;
	cout << "\tРазмер:" << size << endl;
}

struct Stack
{
	struct Node
	{
		Ball data; Node* prev;
	};
	Node *top = NULL;
	int count;
	bool Push(Ball);
	bool Pop(Ball&);
	void Info();
};

//вставка
bool Stack::Push(Ball data) {
	if (!top) {
		top = new Node;
		top->prev = NULL;
		count = 1;
	}
	else {
		Node *temp;
		temp = new Node;
		temp->prev = top;
		top = temp;
		count++;
	}
	top->data = data;
	return true;
}

//удаление
bool Stack::Pop(Ball& data) {
	if (!top) return false;
	Node* temp = top->prev;
	data = top->data;
	delete top;
	top = temp;
	count--;
	return true;
}

//Стек инфо
void Stack::Info() {
	if (!top)
		cout << "---> Стек пустой" << endl;
	else {
		cout << "Информация о стеке: " << endl;
		cout << "\tРазмер стека = " << count << endl;
		top->data.Out();
		cout << endl;
	}
}

void Menu();
void readFile(Stack&);
void userPush(Stack&);
void getOut(Stack&);
void Clear(Ball&, Stack&);

//Меню
void Menu() {
	Stack s;
	Ball p;
	readFile(s);
	int key;
	do {
		system("cls");
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "1. Добавить продукт в корзину" << endl;
		cout << "2. Достать продукт из корзины" << endl;
		cout << "3. Очистить корзину" << endl;
		cout << "0. Выход" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		s.Info();
		cout << "Ввод: ";
		cin >> key;

		switch (key) {
		case 1: userPush(s); break;
		case 2: getOut(s); break;
		case 3: Clear(p, s); break;
		case 0: break;
		default:  system("cls");
			cout << "Данные об ошибках, повторите попытку..." << endl;
			system("pause");
		}
	} while (key);
}

//Файл
void readFile(Stack &stack) {
	Ball ball;
	ifstream data;
	data.open("data.txt", ios::in);
	if (!data) {
		cout << "---> Ошибка открытия файла <---" << endl;
		return;
	}
	else {
		while (data >> ball.color >> ball.price >> ball.proz >> ball.size) {
			stack.Push(ball);
		}
		data.close();
	}
} 

//Ввод
void userPush(Stack& s) {
	string color, proz;
	double price, size;
	Ball ball;
	cout << "Введите товар (цвет, цена, производитель, размер): ";
	cin >> color >> price >> proz >> size;
	while (price < 0 or size <= 0) {
		cout << "---> Цена или размер не могут быть меньше 0 <---" << endl;
		cout << "Цена: ";
		cin >> price;
		cout << "Размер: ";
		cin >> size;
	}
	ball = { color, price, proz, size };
	s.Push(ball);
}

//Достать продукт
void getOut(Stack& s) {
	Stack temp;
	Ball top;
	string color, proz;
	double price, size;
	bool flag = true;
	if (s.count == 0) {
		cout << "No products in the cart" << endl;
		system("pause");
		return;
	}
	cout << "Введите параметры товара(цвет, цена, производитель, размер): ";
	cin >> color >> price >> proz >> size;
	while (flag) {
		top = s.top->data;
		if ((color == top.color) && (price == top.price) && (proz == top.proz) && (size == top.size)) {
			s.Pop(top);
			flag = 0;
			break;
		}
		else if (s.count > 0) {
			s.Pop(top);
			temp.Push(top);
		}
		if (s.count == 0) break;
	}
	while (temp.count > 0) {
		top = temp.top->data;
		s.Push(top);
		temp.Pop(top);
	}
	if (flag) cout << "В корзине нет товара" << endl;
	else cout << "Продукт был найден" << endl;
	system("pause");
}

//Очистить стек
void Clear(Ball& ball, Stack &s) {
	while (s.count) {
		s.Pop(ball);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Menu();
	return 0;
}