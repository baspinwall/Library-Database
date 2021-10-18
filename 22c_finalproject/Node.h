#pragma once
#ifndef NODE_H_
#define NODE_H_

template <typename N>
class Node {
private:
	N data;
	Node<N>* next;
public:
	Node();

	void setData(N dataIn);//sets data
	void setNext(Node<N>* nextIn);//sets pointer to next node
	N getData() const;//gets data
	Node<N>* getNext() const;//gets pointer to next node

};


template <typename N>
Node<N>::Node()
{
	next = nullptr;
}

/*PRE: none
POST: sets pointer to next node
*/
template <typename N>
void Node<N>::setNext(Node<N> *nextNodePtr)
{
	next = nextNodePtr;
}

/*PRE: none
POST: sets data
*/
template <typename N>
void Node<N>::setData(N dataIn)
{
	data = dataIn;
}

/*PRE: none
POST: returns data, else default value of object type
*/
template <typename N>
N Node<N>::getData() const
{
	return data;
}

/*PRE: none
POST: returns pointer to next node, else null pointer
*/
template <typename N>
Node<N>* Node<N>::getNext() const
{
	return next;
}


#endif /* NODE_H_ */

