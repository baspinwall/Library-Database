#pragma once
#ifndef LIST_H_
#define LIST_H_
#include "Node.h"

template <typename L>
class List
{
private:
	int count;
	Node<L>* head;
	Node<L>* tail;
public:
	List();
	Node<L>* addFirst(Node<L>*);
	Node<L>* addLast(Node<L>*);
	Node<L>* addAnywhere(Node<L>*);
	Node<L>* addAnywhere(Node<L>*, int);

	Node<L>* deleteFirst();
	Node<L>* deleteLast();
	Node<L>* deleteAnywhere(L, bool);
	Node<L>* deleteAnywhere(int);

	Node<L>* findFirst() const;
	Node<L>* findLast() const;
	int findAnywhere(L, bool) const;
	Node<L>* findAnywhere(int) const;

	int countItems() const;
	void emptyList();
};


template <typename L>
List<L>::List()
{
	count = 0;
	head = nullptr;
	tail = nullptr;
}

/*PRE: node should be valid
POST: returns pointer to node passed in
*/
template <typename L>
Node<L>* List<L>::addFirst(Node<L>* dataIn) {
	if (count == 0) {
		head = dataIn;
		tail = dataIn;
	}
	else {
		dataIn->setNext(head);
		head = dataIn;
	}
	count++;
	return dataIn;
}

/*PRE: node should be valid
POST: returns pointer to node passed in
*/
template <typename L>
Node<L>* List<L>::addLast(Node<L>* dataIn) {
	if (count == 0) {
		head = dataIn;
		tail = dataIn;
	}
	else {
		tail->setNext(dataIn);
		tail = dataIn;
	}
	count++;
	return dataIn;
}

/*PRE: Assumes that the linked list is created and added to in a sorted order
POST: Adds the specified node to a location based on value, where the next element will be greater than it and the previous element will be less than or equal to it
*/
template <typename L>
Node<L>* List<L>::addAnywhere(Node<L>* dataIn)
{
	if (count == 0)//special case of empty
		return addFirst(dataIn);
	else if (count == 1)//special case of one element
	{
		if (head->getData() <= dataIn->getData())
		{
			head->setNext(dataIn);
			tail = dataIn;
		}
		else {
			dataIn->setNext(head);
			head = dataIn;
		}
	}
	else {
		if (head->getData() > dataIn->getData())//check for smallest element
		{
			dataIn->setNext(head);
			head = dataIn;
		}
		else if (tail->getData() <= dataIn->getData()) {//check for largest element
			tail->setNext(dataIn);
			tail = dataIn;
		}
		else {//check for between elements
			Node<L>* pre;
			Node<L>* cur;
			cur = head;
			pre = cur;
			for (int i = 0; i < count - 1; i++) {//while i<max pos in linked list
				pre = cur;//i pos element, ends at max pos -1
				cur = cur->getNext();//i+1 pos element, ends at max pos
				if (pre->getData() <= dataIn->getData() && cur->getData() > dataIn->getData())//if in between pre and cur in value
				{
					pre->setNext(dataIn);
					dataIn->setNext(cur);
					break;
				}
			}
		}
	}
	count++;
	return dataIn;
}
/*PRE: dataIn node will be added to a certain index, pos within bounds
POST: pos specified should be within bounds, else exception thrown
*/
template <typename L>
Node<L>* List<L>::addAnywhere(Node<L>* dataIn, int pos)
{
	if (pos > count || pos < 0)
		throw "invalid position";
	if (pos == 0)
		return addFirst(dataIn);
	else if (pos == count)
		return addLast(dataIn);
	else {
		Node<L>* pre;
		Node<L>* cur;
		cur = head;
		pre = cur;
		for (int i = 0; i < pos; i++) {
			pre = cur;
			cur = cur->getNext();
		}
		pre->setNext(dataIn);
		dataIn->setNext(cur);
	}
	count++;
	return dataIn;
}

/*PRE: node should be valid
POST: returns pointer to deleted node, else null pointer
*/
template <typename L>
Node<L>* List<L>::deleteFirst()
{
	if (count == 0) {
		return nullptr;
	}
	else {
		Node<L>* temp = head;
		head = head->getNext();
		count--;
		if (count == 0)
			tail = nullptr;
		return temp;
	}
}

/*PRE: node should be valid
POST: returns pointer to deleted node, else null pointer
*/
template <typename L>
Node<L>* List<L>::deleteLast()
{
	if (count == 0) {
		return nullptr;
	}
	else if (count == 1) {
		Node<L>* temp = head;
		head = nullptr;
		tail = nullptr;
		count--;
		return temp;
	}
	else {
		Node<L>* last = findAnywhere(count - 2);
		Node<L>* temp = tail;
		tail = last;
		count--;
		return temp;
	}
}

/*PRE: Assumes that the linked list is created and added to in a sorted order, bool is a nonsense variable added for function overloading
POST: deletes node with target data, returns pointer to deleted node, else null pointer
*/
template <typename L>
Node<L>* List<L>::deleteAnywhere(L target, bool overloadingVar)
{
	if (count == 0)//special case of empty
		return nullptr;
	else {
		if (head->getData() == target)//check for smallest element
		{
			return deleteFirst();
		}
		else if (tail->getData() == target) {//check for largest element
			return deleteLast();
		}
		else {//check for elements
			Node<L>* pre;
			Node<L>* cur;
			cur = head;
			pre = cur;
			for (int i = 0; i < count - 1; i++) {//while i<max pos in linked list
				pre = cur;//i pos element, ends at max pos -1
				cur = cur->getNext();//i+1 pos element, ends at max pos
				if (cur->getData() == target)//if equals cur
				{
					pre->setNext(cur->getNext());
					count--;
					return cur;
				}
			}
			return nullptr;//if not found
		}
	}
}

/*PRE: node removed from specified index, within bounds
POST: throws exception if invalid position, returns deleted node
*/
template <typename L>
Node<L>* List<L>::deleteAnywhere(int pos)
{
	if (pos > count - 1 || pos < 0)
		throw "invalid position";
	if (pos == 0)
		return deleteFirst();
	else if (pos == count - 1)
		return deleteLast();
	else {
		Node<L>* pre;
		Node<L>* cur;
		cur = head;
		pre = cur;
		for (int i = 0; i < pos; i++) {
			pre = cur;
			cur = cur->getNext();
		}
		pre->setNext(cur->getNext());
		count--;
		return cur;
	}
}

/*PRE: assumes first is valid node
POST: returns pointer to first node, else null pointer
*/
template <typename L>
Node<L>* List<L>::findFirst() const
{
	return head;
}

/*PRE: assumes first is valid node
POST: returns pointer to last node, else null pointer
*/
template <typename L>
Node<L>* List<L>::findLast() const
{
	return tail;
}

/*PRE: assumes list is sorted, returns position of node with target value, bool is a nonsense variable for overloading purposes
POST: returns position of node, else -1 if node not found
*/
template <typename L>
int List<L>::findAnywhere(L target, bool overloadingVar) const
{
	Node<L>* cursor;
	int pos = 0;
	for (cursor = head; cursor != nullptr; cursor = cursor->getNext())
	{
		if (target == cursor->getData())
			return pos;
		pos++;
	}
	return -1;
}

/*PRE: position within bounds
POST: returns node pointer, throws exception if pos out of bounds
*/
template <typename L>
Node<L>* List<L>::findAnywhere(int pos) const
{
	if (pos > count - 1 || pos < 0)
		throw "invalid position";
	if (pos == 0)
		return head;
	else if (pos == count - 1)
		return tail;
	else {
		Node<L>* cur;
		cur = head;
		for (int i = 0; i < pos; i++) {
			cur = cur->getNext();
		}
		return cur;
	}
}

/*PRE: none
POST: returns number of nodes
*/
template <typename L>
int List<L>::countItems() const
{
	return count;
}

/*PRE: none
POST: removes head pointer, assumes that main will deallocate dynamic nodes and has already gotten pointer to head if necessary
*/
template <typename L>
void List<L>::emptyList()
{
	head = nullptr;
	count = 0;
}







#endif /* LIST_H_ */

