#include <iostream>
#include "DLList.h"
using namespace std;
#ifndef Journal_h
#define Journal_h
struct Journal
{
  double quantity;
  double price;
  double pages;
  string color;
};
void* Journal_init(Journal);
void Journal_del(void*);
void Journal_out(DLList);
void Journal_cin(Journal&);
#endif
