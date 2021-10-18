#pragma once
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "Book.h"
#include "List.h"
using namespace std;

class HashTable {
public:
	/**Constructors*/
	HashTable() {}
	~HashTable();


	/**Access Functions*/
	int hash(string key) const;
	int countBucket(int index) const;
	int longestBucket() const;
	double averageNodes() const;
	double loadFactor() const;
	Book search(string) const;

	/**Manipulation Procedures*/
	void insert(Book b);
	int remove(string);
	//void printBucket(ostream& out, int index) const;
	void printTable(ostream& out) const;

private:
	static const int SIZE = 50;
	List<Book> Table[SIZE];

};
#endif /* HASHTABLE_H_ */
