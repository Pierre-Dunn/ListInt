#ifndef __LISTINT_H__
#define __LISTINT_H__


#include <cstddef>

class ListInt
{
private:
	class Node 
	{
	public:
		int _value;
		Node *_prev, *_next;
		Node(int value=0, Node* prev = NULL, Node* next = NULL) :_value(value), _prev(prev), _next(next) {};
	};
	Node *merge(Node* first, Node* second);
	Node *mergeSort(Node* head);
	Node *split(Node *head);
	Node *_head, *_tail;  
	size_t _size;         

public:
	
	ListInt();
	~ListInt();
	size_t getSize() const { return _size; }
	bool empty() const { return _size == 0; }

	void reverse();     
	void grab_and_append(ListInt& from); 
	void sort();         // отсортировать по возрастанию (можно добавить сюда
						 // параметр - функтор сравнения на меньше для любого порядка сортировки)
	void push_back(int val); 
	void push_front(int val);
	void pop_back();
	void pop_front();
	void clear();
	
	class iterator 
	{
	private:
		Node * _current;
		iterator(Node* node) :_current(node) {}; 
		friend class ListInt; 
	public:
		iterator() :_current(NULL) {};  
		iterator(const iterator& it); 
		~iterator() { _current = NULL; }

		bool valid() const; 
		bool invalid() const; 

							 
	  //int& get();

		int get() const;

		void prev();
		void next();

		bool equal(const iterator& other) const;
		iterator& operator ++();	
		iterator& operator --();
		iterator operator --(int);
		iterator operator ++(int);
		iterator& operator =(int index);
	};

	iterator head() { return iterator(_head); }
	iterator tail() { return iterator(_tail); }

	iterator insert(iterator pos, int value);  

public:
	iterator erase(iterator pos); // Обратить внимание: после удаления узла итератор позиции должен стать инвалидным
								  // возвращает итератор указывающий на узел следующий после удаленного
};




#endif