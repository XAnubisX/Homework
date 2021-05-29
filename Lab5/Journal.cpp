#include <iostream>
#include "Journal.h"
using namespace std;
void* Journal_init(Journal B)
{
    Journal* A = new Journal;
  A->quantity = B.quantity;
  A->price = B.price;
  A->pages = B.pages;
  A->color = B.color;
  void* S = (void*) A;
  return S;
}
void Journal_del(void* S)
{
  delete (Journal*) S;
}
void Journal_out(DLList List)
{
    Journal A;
  List.MoveFirst();
  system("cls");
  if(!List.Count)
  {
    cout << "—писок пуст" << endl;
    return;
  }
  for(int i = 0; i < List.Count; i++)
  {
    A = *((Journal*) List.C->data);
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << " количество = " << A.quantity << endl;
    cout << " цена = " << A.price << endl;
    cout << " страницы = " << A.pages << endl;
    cout << " цвет = " << A.color << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    List.MoveNext();
  }
}
void Journal_cin(Journal& A)
{
  cout << "¬ведите ваши данные:" << endl;
  cout << "количество = "; cin >> A.quantity;
  cout << "цена = "; cin >> A.price;
  cout << "страницы = "; cin >> A.pages;
  cout << "цвет = "; cin >> A.color;
}
