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
    cout << "������ ����" << endl;
    return;
  }
  for(int i = 0; i < List.Count; i++)
  {
    A = *((Journal*) List.C->data);
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << " ���������� = " << A.quantity << endl;
    cout << " ���� = " << A.price << endl;
    cout << " �������� = " << A.pages << endl;
    cout << " ���� = " << A.color << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    List.MoveNext();
  }
}
void Journal_cin(Journal& A)
{
  cout << "������� ���� ������:" << endl;
  cout << "���������� = "; cin >> A.quantity;
  cout << "���� = "; cin >> A.price;
  cout << "�������� = "; cin >> A.pages;
  cout << "���� = "; cin >> A.color;
}
