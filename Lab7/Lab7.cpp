//The code did Ananev Egor
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void IntMatriza(int**&, int&);
void PrintMatriza(int**&, int&);
void PrintResults(int*&, int*&, int&, int&, int&);
void Dextra(int**&, int*&, int*&, int*&, int&, int&, int&, int&);

int main()
{
	setlocale(LC_ALL, "Russian");
	int** matr;
	int* distance;
	int* tops;
	int* shortcut;
	int size;
	int k = 1;
	int begin_index = 0; //(вершина - 1)
	int end;
	cout << "Вершина до которой нужно найти кратчайший путь: ";
	cin >> end;
	end = end - 1;
	int end1 = end;
	IntMatriza(matr, size);
	PrintMatriza(matr, size);
	Dextra(matr, distance, tops, shortcut, size, k, begin_index, end);
	PrintResults(shortcut, distance, size, k, end1);
}

void IntMatriza(int**& matr, int& size)
{
	ifstream f("Matritza.txt");
	int count = 0;
	while (!f.eof())
	{
		int temp;
		f >> temp;
		count++;
	}
	count = sqrt(count);
	size = count;
	f.seekg(0);
	matr = new int*[size];
	for (int i = 0; i < size; i++)
	{
		matr[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			f >> matr[i][j];
		}
	}
	f.close();
}

void PrintMatriza(int**& matr, int& size)
{
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	cout << "    Матрица: " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(5) << matr[i][j];
		}
		cout << endl;
	}
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

void PrintResults(int*& shortcut, int*& distance, int& size, int& k, int& end)
{
	ofstream f("Result.txt");
	cout << "Кратчайшие расстояния до вершин:" << endl;
	f << "Кратчайшие расстояния до вершин:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Вершина" << " -=(" << i + 1 << ")=-" << " " << distance[i] << endl;
		f << "Вершина" << " -=(" << i + 1 << ")=-" << " " << distance[i] << endl;
		cout << "-=-=-=-=-=-=-=-=-=-" << endl;
	}
	cout << endl;
	cout << "Кратчайший путь от 1 --> " << end + 1 << endl;
	f << endl;
	f << "Кратчайший путь от 1 --> " << end + 1 << endl;
	for (int j = k - 1; j >= 0; j--)
	{
		cout << setw(5) << shortcut[j];
		f << " " << shortcut[j];
	}
	f.close();
}

void Dextra(int**& matr, int*& distance, int*& tops, int*& shortcut, int& size, int& k, int& begin_index, int& end)
{
	int temp, minindex, min;
	distance = new int[size];
	tops = new int[size];
	shortcut = new int[size];
	for (int i = 0; i < size; i++)
	{
		distance[i] = 10000;
		tops[i] = 1;
	}
	distance[begin_index] = 0;
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < size; i++)
		{
			if ((tops[i] == 1) && (distance[i] < min))
			{
				min = distance[i];
				minindex = i;
			}
		}
		if (minindex != 10000)
		{
			for (int i = 0; i < size; i++)
			{
				if (matr[minindex][i] > 0)
				{
					temp = min + matr[minindex][i];
					if (temp < distance[i])
					{
						distance[i] = temp;
					}
				}
			}
			tops[minindex] = 0;
		}
	} 
	while (minindex < 10000);
	shortcut[0] = end + 1;
	int weight = distance[end];
	while (end != begin_index)
	{
		for (int i = 0; i < size; i++)
		{
			if (matr[i][end] != 0)
			{
				int temp = weight - matr[i][end];
				if (temp == distance[i])
				{
					weight = temp;
					end = i;
					shortcut[k] = i + 1;
					k++;
				}
			}
		}
	}
}