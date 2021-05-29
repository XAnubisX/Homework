#include <iostream>
#include <fstream>
#include <sstream>
#include "DLList.h"
#include "Journal.h"
using namespace std;
int main()
{
  setlocale(LC_ALL, "Russian");
  DLList List;
  void* S;
  Journal A;
  int m = 1;
  ifstream file("lab5.txt");
  string line;
  while(getline(file, line))
  {
    istringstream line_F(line);
    line_F >> A.quantity >> A.price >> A.pages >> A.color;
    S = Journal_init(A);
    List.AddNext(S);
  }
  file.close();
  while(m)
  {
    system("cls");
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Добавить элемент:             " << endl;
    cout << "1) В начало                   " << endl;
    cout << "2) В конец                    " << endl;
    cout << "3) На k-ую позицию            " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Удалить элемент:                       " << endl;
    cout << "4) Первый                              " << endl;
    cout << "5) Последний                           " << endl;
    cout << "6) Стоящий на k-ой позиции             " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "7) Сортировка по \"количеству\"            " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "8) Очистите список                     " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "9) Загрузка данных из списка в файл    " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "10) Показать список                    " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "0) Выход                               " << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cin >> m;
    switch(m)
    {
      case 1:
      {
        system("cls");
        Journal_cin(A);
        S = Journal_init(A);
        List.AddFirst(S);
        Journal_out(List);
        system("pause");
        break;
      }
      case 2:
      {
        system("cls");
        Journal_cin(A);
        S = Journal_init(A);
        List.AddLast(S);
        Journal_out(List);
        system("pause");
        break;
      }
      case 3:
      {
        system("cls");
        int k;
        cout << "Введите номер позиции с " << 1 << " к " << List.Count + 1 << endl;
        cout << "k = "; cin >> k;
        k--;
        if(k >= 0 & k <= List.Count)
        {
          Journal_cin(A);
          S = Journal_init(A);
          if(k == 0)
          {
            List.AddFirst(S);
          }
          else
          {
            if(k == List.Count)
            {
              List.AddLast(S);
            }
            else
            {
              List.Move_k(k - 1);
              List.AddNext(S);
            }
          }
          Journal_out(List);
        }
        else cout << "Ошибка!" << endl;
        system("pause");
        break;
      }
      case 4:
      {
        system("cls");
        if(List.DelFirst(S))
        {
          Journal_del(S);
          Journal_out(List);
        }
        else
        {
            cout << "Ошибка!" << endl;
        }
        system("pause");
        break;
      }
      case 5:
      {
        system("cls");
        if(List.DelLast(S))
        {
          Journal_del(S);
          Journal_out(List);
        }
        else
        {
            cout << "Ошибка!" << endl;
        }
        system("pause");
        break;
      }
      case 6:
      {
        system("cls");
        int k;
        if(!List.Count)
        {
            cout << "Ошибка!" << endl;
          system("pause");
          break;
        }
        cout << "Введите номер позиции с " << 1 << " к " << List.Count << endl;
        cout << "k = "; cin >> k;
        k--;
        if(k >= 0 & k <= List.Count)
        {
          if(k == 0)
          {
            List.DelFirst(S);
          }
          else
          {
            if(k == (List.Count - 1))
            {
              List.DelLast(S);
            }
            else
            {
              List.Move_k(k);
              List.Del(S);
            }
          }
          Journal_out(List);
        }
        else cout << "Ошибка!" << endl;
        system("pause");
        break;
      }
      case 7:
      {
        system("cls");
        void* tmp;
        for(int i = 0; i < List.Count; i++)
        {
          List.MoveLast();
          for(int j = (List.Count - 1); j >= (i + 1); j--)
          {
            if(((Journal*) List.C->data)->quantity < ((Journal*) List.C->prev->data)->quantity)
            {
              tmp = List.C->data;
              List.C->data = List.C->prev->data;
              List.C->prev->data = tmp;
            }
            List.MovePrev();
          }
        }
        Journal_out(List);
        system("pause");
        break;
      }
      case 8:
      {
        List.MoveFirst();
        while(List.Del(S))
        {
          Journal_del(S);
        }
        Journal_out(List);
        system("pause");
        break;
      }
      case 9:
      {
        ofstream file("lab5.txt");
        List.MoveFirst();
        for(int i = 0; i < List.Count; i++)
        {
          A = *((Journal*) List.C->data);
          file << A.quantity << " "  << A.price << " "<< A.pages << " " << A.color << endl;
          List.MoveNext();
        }
        file.close();
        cout << "Загруженный!!!" << endl;
        system("pause");
        break;
      }
      case 10:
      {
        system("cls");;
        Journal_out(List);
        system("pause");
        break;
      }
    }
  }
  List.MoveFirst();
  while(List.Del(S))
  {
    Journal_del(S);
  }
  system("pause");
  return 0;
}
