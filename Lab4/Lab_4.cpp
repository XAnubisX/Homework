#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Journal 
{
	string color;
	double price;
	double pages;
	int quantity;
};
//Структура очереди
struct Queue 
{
	struct Node { int n; char* data; Node* next; };
	Node *First = NULL;
	int count = 0;
	bool Push(char*, int);
	bool Pop(char*&, int&);
	void Info();
};
//Ввод
bool Queue::Push(char* data, int n) 
{
	if (!First) 
	{
		First = new Node;
		First->next = NULL;
		First->n = n;
		First->data = new char[n];
		for (int i = 0; i < n; i++) 
		{
			First->data[i] = data[i];
		}
		count = 1;
	}
	else {
		Node *temp;
		temp = First;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new Node;
		temp->next->data = new char[n];
		temp->next->next = NULL;
		temp->next->n = n;
		for (int i = 0; i < n; i++) 
		{
			temp->next->data[i] = data[i];
		}
		count++;
	}
	return true;
}
//Удаление
bool Queue::Pop(char*& data, int& n) 
{
	if (!First) return false;
	Node* temp = First->next;
	n = First->n;
	data = new char[n];
	for (int i = 0; i < n; i++) 
	{
		data[i] = First->data[i];
	}
	delete First->data;
	delete First;
	First = temp;
	count--;
	return true;
}
//Информация очереди
void Queue::Info() 
{
	if (!First) cout << "--- Очередь пуста ---" << endl;
	else 
	{
		cout << "Размер очереди = " << count << endl;
	}
}

void Menu();
void ClearBinaryFile();
void WriteBinaryFile(char*, int);
bool ReadBinaryFile(Queue&);
void InputBinaryFile();
void AddProduct(Queue&);
void PullOut(Queue&);
void Clear(Queue&);
void ClearExit(Queue&);
void GetSeria(char*&, int&, Journal);
void GetDeSeria(char*, int, Journal&);
void ShowProduct(Journal);

void GetSeria(char*& data, int& n, Journal a) 
{
	size_t s1 = a.color.size();
	int n0 = sizeof(size_t);
	int n1 = s1;
	int n2 = sizeof(double);
	int n3 = n2;
	int n4 = sizeof(int);
	n = n0 + n1 + n2 + n3 + n4;
	data = new char[n];

	char* d0 = reinterpret_cast<char*>(&s1);
	char* d1 = const_cast<char*>(a.color.c_str());
	char* d2 = reinterpret_cast<char*>(&a.price);
	char* d3 = reinterpret_cast<char*>(&a.pages);
	char* d4 = reinterpret_cast<char*>(&a.quantity);

	for (int i = 0; i < n0; i++) data[i] = d0[i];
	for (int i = 0; i < n1; i++) data[i + n0] = d1[i];
	for (int i = 0; i < n2; i++) data[i + n0 + n1] = d2[i];
	for (int i = 0; i < n3; i++) data[i + n0 + n1 + n2] = d3[i];
	for (int i = 0; i < n4; i++) data[i + n0 + n1 + n2 + n3] = d4[i];
}

void GetDeSeria(char* data, int n, Journal& a)
{
	int n0, n1, n2, n3, n4;
	n0 = sizeof(size_t);
	n2 = sizeof(double);
	n3 = n2;
	n4 = sizeof(int);
	size_t p = *reinterpret_cast<size_t*>(data);
	n1 = p;
	string ss1(data + n0, p);

	a.color = ss1;
	a.price = *reinterpret_cast<double*>(data + n0 + n1);
	a.pages = *reinterpret_cast<double*>(data + n0 + n1 + n2);
	a.quantity = *reinterpret_cast<int*>(data + n0 + n1 + n2 + n3);
}
//Меню
void Menu()
{
	Queue q;
	int key;
	ReadBinaryFile(q);
	do 
	{
		system("cls");
		cout << "-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "1) Добавить продукт" << endl;
		cout << "2) Вытащить продукт" << endl;
		cout << "3) Очистить" << endl;
		cout << "0) Выход" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-" << endl;
		q.Info();
		cout << "Ввод: ";
		cin >> key;

		switch (key) 
		{
		case 1: AddProduct(q); break;
		case 2: PullOut(q); break;
		case 3: Clear(q); break;
		case 0: ClearExit(q); break;
		default:  system("cls");
			cout << "Ошибка, повторите попытку..." << endl;
			system("pause");
		}
	} while (key);
}
//Очистка файла
void ClearBinaryFile() 
{
	fstream f_out;
	f_out.open("out.dat", ios::out | ios::binary);
	f_out.close();
}
//Запись файла
void WriteBinaryFile(char* data, int n) 
{
	fstream f_out;
	f_out.open("out.dat", ios::app | ios::binary);
	f_out.write((char*)&n, sizeof(int));
	f_out.write(data, n);
	f_out.close();
}
//Чтение файла
bool ReadBinaryFile(Queue& q) 
{
	system("cls");
	fstream f_in("out.dat", ios::in | ios::binary);
	if (!f_in) 
	{
		cout << "---> Ошибка, нет входного двоичного файла" << endl;
		return false;
	}
	int n;
	Journal p;
	while (!f_in.eof())
	{
		if (f_in.read((char*)&n, sizeof(int))) 
		{
			char* data = new char[n];
			f_in.read(data, n);
			q.Push(data, n);
			GetDeSeria(data, n, p);
			ShowProduct(p);
			delete[] data;
			data = NULL;
		}
	}
	f_in.close();
	system("pause");
	return true;
}
//Входной файл
void InputBinaryFile() 
{
	Journal p[] =
	{
		{"blue", 12, 24, 2},
		{"white", 24, 48, 5}
	};
	char* data;
	int ssize, m = 2;
	ClearBinaryFile();
	for (int i = 0; i < m; i++) 
	{
		GetSeria(data, ssize, p[i]);
		WriteBinaryFile(data, ssize);
	}
	delete[] data;
	data = NULL;
}
//Добавить продукт
void AddProduct(Queue &q) 
{
	Journal p;
	char* data;
	int ssize;
	system("cls");
	cout << "Введите технические характеристики продукта(цвет, цена, количество страниц, количество): " << endl;
	cin >> p.color >> p.price >> p.pages >> p.quantity;
	while (p.pages <= 0 || p.price < 0 || p.quantity < 0)
	{
		cout << "-=-=- Ошибка данных об страницах, цене или количеству -=-=- " << endl;
		cout << "Цена: ";
		cin >> p.price;
		cout << "Количество страниц: ";
		cin >> p.pages;
		cout << "Количество: ";
		cin >> p.quantity;
	}
	GetSeria(data, ssize, p);
	q.Push(data, ssize);
	delete[] data;
	data = NULL;
}
//Вывод
void PullOut(Queue &q) 
{
	Journal p;
	string color;
	double price, pages;
	int ssize, quantity, count = q.count;
	system("cls");
	if (q.count == 0)
	{
		cout << "В очереди нет продуктов" << endl;
		system("pause");
		return;
	}
	cout << "Введите технические характеристики продукта(цвет, цена, количество страниц, количество): ";
	cin >> color >> price >> pages >> quantity;
	while (pages <= 0 || price < 0 || quantity < 0) 
	{
		cout << "-=-=- Ошибка данных об страницах, цене или количеству -=-=- " << endl;
		cout << "Цена: ";
		cin >> price;
		cout << "Количество страниц: ";
		cin >> pages;
		cout << "Количество: ";
		cin >> quantity;
	}

	for (int i = 0; i < count; i++) 
	{
		char* data;
		q.Pop(data, ssize);
		GetDeSeria(data, ssize, p);
		if ((color == p.color) && (price == p.price) && (pages == p.pages) && (quantity == p.quantity)) 
		{
			cout << "Продукт найден" << endl;
			delete[] data;
			data = NULL;
			system("pause");
			return;
		}
		else 
		{
			q.Push(data, ssize);
			delete[] data;
			data = NULL;
		}
	}
	cout << "В очереди нет товара" << endl;
	system("pause");
}
//Очистка
void Clear(Queue& q) 
{
	if (q.count == 0)
	{
		return;
	}
	Journal p;
	int ssize, i = 1;
	system("cls");
	while (q.count) 
	{
		char* data = new char[q.First->n];
		ssize = q.First->n;
		q.Pop(data, ssize);
		GetDeSeria(data, ssize, p);
		cout << i << ". ";
		ShowProduct(p);
		i++;
		delete[] data;
		data = NULL;
	}
	system("pause");
}

void ClearExit(Queue& q) 
{
	Journal p;
	if (q.count == 0) 
	{
		return;
	}
	int ssize;
	while (q.count) 
	{
		char* data = new char[q.First->n];
		ssize = q.First->n;
		q.Pop(data, ssize);
		delete[] data;
		data = NULL;
	}
}

void ShowProduct(Journal p) 
{
	cout << "\tЦвет: " << p.color
		<< "\tЦена: " << p.price
		<< "\tКол-во страниц: " << p.pages
		<< "\tКоличество: " << p.quantity << endl;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	InputBinaryFile();
	Menu();
	return 0;
}