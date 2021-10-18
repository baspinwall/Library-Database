#ifndef BOOK_H
#define BOOK_H
#include<string>
#include<iostream>

using namespace std;

class Book {
protected:
	string isbn;
	string title;
	string author;
	string publisher;

public:
	// constructors
	Book();
	Book(string, string, string, string);

	// destructors
	virtual ~Book();

	// mutators
	void setIsbn(string);
	void setTitle(string);
	void setAuthor(string);
	void setPublisher(string);

	//accessor
	string getIsbn()const;
	string getTitle()const;
	string getAuthor()const;
	string getPublisher()const;

	friend bool operator== (const Book & a, const Book & b);
	friend bool operator<= (const Book & a, const Book & b);
	friend bool operator>= (const Book & a, const Book & b);
	friend bool operator> (const Book & a, const Book & b);
	friend bool operator< (const Book & a, const Book & b);
	friend ostream &operator << (ostream&, const Book &);
};
#endif
