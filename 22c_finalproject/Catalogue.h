#ifndef CATALOGUE_H
#define CATALOGUE_H
#include <iostream>
#include <fstream>
#include "BST.h"
#include "HashTable.h"

enum BookFields {
	ISBN,
	TITLE,
	AUTHOR,
	PUBLISHER,
};

class Catalogue : public Book {

private:
	// static members
	static int size;
	static BST<string, string> bstISBN, bstTitle, bstAuthor, bstPublisher;
	static HashTable hashISBN;
	static List<Book> readingList;
	const static string fileName;
	static void deleteBST(BST<string, string>* );
	static void deleteList();
	static void saveInOrder(BST<string, string>* , ofstream&);
	static void printInOrder(BST<string, string>*);
	static void printLevelOrder(BST<string, string>* );
	static void printGivenLevel(BST<string, string>* , int , bool, BST<string, string>*);
	static int height(BST<string, string>* );
	static int largestString(BST<string, string>* );

public:
	// constructors
	Catalogue();

	// static functions
	static void load();
	static void close();
	static void save();

	static Book* addBook(Book*);
	static Book find(string);
	static void deleteBook(string);
	static void listHashSeq();
	static void listSortSeq(int);
	static void printIndented(int);
	static void printEfficiencies();
	static void addReadingList(string);
	static void deleteReadingList(string);
	static void showReadingList();
	static void printReadingList(string);
};
#endif
