#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_
#include "List.h"

template <typename S>
class Queue : protected List <S>
{
private:

public:
	Node<S>* enqueue(Node<S>*);//adds node to top of stack
	Node<S>* dequeue();//removes node from top of stack
	Node<S>* front();//returns pointer to node at top of the stack
	Node<S>* rear();
	int size();
	bool isEmpty();//returns boolean value denoting emptiness
};

/*PRE: valid node
POST: returns pointer to node passed in
*/
template <typename S>
Node<S>* Queue<S>::enqueue(Node<S>* in)
{
	return List<S>::addFirst(in);
}

/*PRE: valid node
POST: returns pointer to node dequeued, if no nodes in queue, will return a null pointer
*/
template <typename S>
Node<S>* Queue<S>::dequeue()
{
	return List<S>::deleteLast();
}

/*PRE: queue is not empty
POST: returns pointer to node at front(where nodes are dequeued from), else a null pointer
*/
template <typename S>
Node<S>* Queue<S>::front()
{
	return List<S>::findLast();
}

/*PRE: queue is not empty
POST: returns pointer to node at rear(where nodes are queued to), else a null pointer
*/
template <typename S>
Node<S>* Queue<S>::rear()
{
	return List<S>::findFirst();
}

/*PRE: none
POST: returns size of queue
*/
template <typename S>
int Queue<S>::size()
{
	return List<S>::countItems();
}

/*PRE: none
POST: returns true if empty
*/
template <typename S>
bool Queue<S>::isEmpty()
{
	return List<S>::countItems() == 0;
}


#endif /* QUEUE_H_ */
