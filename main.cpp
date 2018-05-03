#include<iostream>
#include"ListInt.h"

using namespace std;
void PrintList(ListInt& list, int number)
{
	ListInt::iterator it;
	if (list.empty()) {
		cout << "List " << number << endl;
		cout << "list " << number << " is empty" << endl;
		return;
	}
	cout << "List " << number << endl;
	for (it = list.head(); it.valid(); ++it)
		cout << it.get() << " ";
	cout << endl << endl;
}
int main()
{
	setlocale(LC_ALL,"rus");
	ListInt list1, list2;
	
	for (size_t i = 0; i < 10; i++)
	{
		list1.push_front(i);
		list2.push_back(i);
	}
	PrintList(list1,1);
	PrintList(list2,2);
	cout << "list1.grab_and_append called with list2" << endl << endl;
	list1.grab_and_append(list2);
	PrintList(list1, 1);
	PrintList(list2, 2);
	cout << "sorted list1" << endl << endl;
	list1.sort();
	PrintList(list1, 1);
	cout << "reversed list1" << endl << endl;
	list1.reverse();
	PrintList(list1, 1);
	cout << "List 1 size: " << list1.getSize() << endl
		<< "List 2 size: " << list2.getSize() << endl << endl;
	list2.insert(list2.head(),1000);
	cout << "list2.insert called with value = 1000" << endl;
	PrintList(list2, 2);
    
	
	return 0;
}
