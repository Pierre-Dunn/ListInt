#include "ListInt.h"
#include<iostream>

ListInt::Node * ListInt::merge(Node * first, Node * second)
{
	if (!first)
		return second;

	if (!second)
		return first;

	if (first->_value < second->_value)
	{
		first->_next = merge(first->_next, second);
		first->_next->_prev = first;
		first->_prev = NULL;
		return first;
	}
	else
	{
		second->_next = merge(first, second->_next);
		second->_next->_prev = second;
		second->_prev = NULL;
		return second;
	}
}
ListInt::Node * ListInt::mergeSort(Node* head)
{
	if (!head || !head->_next)
		return head;
	Node *second = split(head);

	
	head = mergeSort(head);
	second = mergeSort(second);

	
	return merge(head, second);
}
ListInt::Node * ListInt::split(Node *head)
{
	Node *fast = head, *slow = head;
	while (fast->_next && fast->_next->_next)
	{
		fast = fast->_next->_next;
		slow = slow->_next;
	}
	Node *second = slow->_next;
	slow->_next = NULL;
	return second;
}

ListInt::ListInt()
{
	_size = 0;
	_head = _tail = NULL;
}

ListInt::~ListInt()
{
	clear();
}

void ListInt::reverse()
{
	Node* ptr = _head;
	while (ptr != 0) {
		Node* tmp = ptr->_next;
		ptr->_next = ptr->_prev;
		ptr->_prev = tmp;
		if (tmp == NULL) {
			_tail = _head;
			_head = ptr;
		}
		ptr = tmp;
		
	}
}

void ListInt::grab_and_append(ListInt & from)
{
	for (ListInt::iterator it = from.head(); it.valid();  ++it)
	{
		push_back(it.get()); 
	}
	from.clear();
}

 void ListInt::sort()
{
	this->_head = mergeSort(this->_head);
}

void ListInt::push_back(int val)
{
	if (_size == 0)
	{
		_head = _tail = new Node(val);
	}
	else
	{
		_tail = new Node(val, _tail); // Íîâûé óçåë ñòàíîâèòñÿ õâîñòîì, åãî óêàçàòåëü prev óêàçûâàåò íà ñòàðûé õâîñò
		_tail->_prev->_next = _tail; // Ïðåäûäóùèé óçåë ñâÿçûâàåòñÿ ñ íîâûì õâîñòîì
	}
	_size++;
}

void ListInt::push_front(int val)
{
	if(_size == 0)
		_tail = _head = new Node(val);
	else
	{
		_head = new Node(val, NULL, _head);
		_head->_next->_prev = _head;
	}
	_size++;
}

void ListInt::pop_back()
{
	if (empty()) return;
	Node* temp = _tail;
	_tail = _tail->_prev;                      // Íîâûì õâîñòîì ñòàíîâèòñÿ ïðåäøåñòâóþùèé ñòàðîìó õâîñòó óçåë
	if (_tail != NULL) _tail->_next = NULL;
	//std::cout << temp->_value << std::endl;
	delete temp;
	_size--;
}

void ListInt::pop_front()
{
	if (empty()) return;
	Node* temp = _head;
	_head = _head->_next;                      // Íîâîé ãîëîâîé ñòàíîâèòñÿ ñëåäóþùèé ïîñëå ñòàðîé ãîëîâû óçåë
	if(_head != NULL) _head->_prev = NULL;
	//std::cout << temp->_value << std::endl;
	delete temp;
	_size--;
}

void ListInt::clear()
{
	while (_size)
		pop_front();
}

ListInt::iterator ListInt::insert(iterator pos, int value)// âîçâðàùàåò ïîçèöèþ ïîñëå âñòàâëåííîé
{
	if(pos._current == _head)
	{
		this->push_front(value);
		pos = this->head();
		return pos;
	}
	else if(pos._current != 0)
	{
		Node* prev = this->_head;
		ListInt::iterator it;
		for (it = this->head(); it._current != pos._current->_prev; ++it)
		{
			prev = prev->_next;			
		}
		Node *newNode = new Node(value, prev, prev->_next);
		prev->_next->_prev = newNode;
		prev->_next = newNode;
		_size++;	
		pos._current = NULL;
		pos = ++it;
		return pos;

	}
	else return this->head();
}

ListInt::iterator ListInt::erase(iterator pos)
{
	if (pos._current == _head)
	{
		this->pop_front();
		pos._current = NULL;
		pos = this->head();
		return ++pos;
	}
	else if (pos._current == _tail)
	{
		this->pop_back();
		pos._current = NULL;
		pos = this->tail();
		return pos;
	}
	else if (pos._current == NULL)
		return this->head();
	else
	{
		Node* prev = this->_head;
		ListInt::iterator it;
		for (it = this->head(); it._current != pos._current->_prev; ++it)
		{
			prev = prev->_next;
		}
		Node* toDelete = prev->_next;
		prev->_next = toDelete->_next;
		toDelete->_next->_prev = prev;
		delete toDelete;
		_size--;
		pos._current = prev;
		return ++pos;
	}
}

ListInt::iterator::iterator(const iterator & it)
{
	_current = it._current;
}

bool ListInt::iterator::valid() const
{
	return _current != NULL;
}

bool ListInt::iterator::invalid() const
{
	return _current == NULL;
}

int ListInt::iterator::get() const
{
	if(_current != NULL)
		return _current->_value;
}

void ListInt::iterator::prev()
{
	_current = _current->_prev;
}

void ListInt::iterator::next()
{
	_current = _current->_next;
}

bool ListInt::iterator::equal(const iterator & other) const
{
	return this->_current == other._current;
}

ListInt::iterator & ListInt::iterator::operator++()//preincrement
{		
		this->next();
		return *this;
}

ListInt::iterator & ListInt::iterator::operator--()//predecrement
{
	this->prev();
	return *this;
}

ListInt::iterator ListInt::iterator::operator--(int)//postdecrement
{
	iterator temp = *this;
	--*this;
	return temp;
}

ListInt::iterator ListInt::iterator::operator++(int)//postincrement
{
	iterator temp = *this;
	++*this;
	return temp;
}

ListInt::iterator & ListInt::iterator::operator=(const ListInt::iterator& it)
{
	if (this == &it) return *this;
	this->_current = it._current;
	return *this;
}
