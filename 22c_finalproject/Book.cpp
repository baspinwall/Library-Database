#define _CRT_SECURE_NO_WARNINGS
#include "book.h"

using namespace std;

// constructors
Book::Book() {}
Book::Book
(
	string isbnNum, string bookTitle, string bookAuthor, string bookPublisher
)

{
	isbn = isbnNum;
	title = bookTitle;
	author = bookAuthor;
	publisher = bookPublisher;
}

// destructors
Book::~Book() {};

// mutators
void Book::setIsbn(string isbn) { this->isbn = isbn; }
void Book::setTitle(string title) { this->title = title; }
void Book::setAuthor(string author) { this->author = author; }
void Book::setPublisher(string publisher) { this->publisher = publisher; }

// accessors
string Book::getIsbn() const { return isbn; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }

bool operator== (const Book& a, const Book& b)
{
	if (a.getIsbn() == b.getIsbn())
		return true;
	return false;
}

bool operator>= (const Book& a, const Book& b)
{
	if (a.getIsbn() >= b.getIsbn())
		return true;
	return false;
}

bool operator<= (const Book& a, const Book& b)
{
	if (a.getIsbn() <= b.getIsbn())
		return true;
	return false;
}

bool operator> (const Book& a, const Book& b)
{
	if (a.getIsbn() > b.getIsbn())
		return true;
	return false;
}

bool operator< (const Book& a, const Book& b)
{
	if (a.getIsbn() < b.getIsbn())
		return true;
	return false;
}
//overloading operator for output
ostream &operator << (ostream &strm, const Book& obj) {
	strm
		<< "ISBN: " << obj.getIsbn() << endl
		<< "Title: " << obj.getTitle() << endl
		<< "Author: " << obj.getAuthor() << endl
		<< "Publisher: " << obj.getPublisher() << endl;
	return strm;
}
