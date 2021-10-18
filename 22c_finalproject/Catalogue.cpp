
#define _CRT_SECURE_NO_WARNINGS
#include "catalogue.h"

//num books in the inventory
int Catalogue::size;

//data file of books in catalogue
const string Catalogue::fileName = "books.txt";

List<Book> Catalogue::readingList;
HashTable Catalogue::hashISBN;
BST<string, string> Catalogue::bstAuthor("", "");
BST<string, string> Catalogue::bstISBN("", "");
BST<string, string> Catalogue::bstPublisher("", "");
BST<string, string> Catalogue::bstTitle("", "");

Catalogue::Catalogue() {}

//loads books from the file data
void Catalogue::load()
{
	ifstream inFile(Catalogue::fileName);
	if (!inFile)
	{
		throw "Your file cannot be opened.";
		return;
	}

	string isbn, author, title, publisher;
	Book book;

	// read size from file
	inFile >> size;
	inFile.ignore(1, '\n');

	getline(inFile, isbn, ';');
	getline(inFile, title, ';');
	getline(inFile, author, ';');
	getline(inFile, publisher);

	book = Book(isbn, title, author, publisher);
	Catalogue::hashISBN.insert(book);
	Catalogue::bstAuthor = BST<string, string>(book.getAuthor(), book.getIsbn());
	Catalogue::bstISBN = BST<string, string>(book.getIsbn(), book.getIsbn());
	Catalogue::bstPublisher = BST<string, string>(book.getPublisher(), book.getIsbn());
	Catalogue::bstTitle = BST<string, string>(book.getTitle(), book.getIsbn());

	//init the hash and bst(s) here
	for (int i = 0; i < size - 1; i++) {

		getline(inFile, isbn, ';');
		getline(inFile, title, ';');
		getline(inFile, author, ';');
		getline(inFile, publisher);

		book = Book(isbn, title, author, publisher);
		Catalogue::hashISBN.insert(book);
		Catalogue::bstAuthor.add(new BST<string, string>(book.getAuthor(), book.getIsbn()));
		Catalogue::bstISBN.add(new BST<string, string>(book.getIsbn(), book.getIsbn()));
		Catalogue::bstPublisher.add(new BST<string, string>(book.getPublisher(), book.getIsbn()));
		Catalogue::bstTitle.add(new BST<string, string>(book.getTitle(), book.getIsbn()));
	}

	inFile.close();
}

void Catalogue::close()
{
	//call on left and right nodes of each bst, root node is not dynamic memory
	Catalogue::deleteBST(Catalogue::bstAuthor.getLeft());
	Catalogue::deleteBST(Catalogue::bstAuthor.getRight());
	Catalogue::deleteBST(Catalogue::bstISBN.getLeft());
	Catalogue::deleteBST(Catalogue::bstISBN.getRight());
	Catalogue::deleteBST(Catalogue::bstPublisher.getLeft());
	Catalogue::deleteBST(Catalogue::bstPublisher.getRight());
	Catalogue::deleteBST(Catalogue::bstTitle.getLeft());
	Catalogue::deleteBST(Catalogue::bstTitle.getRight());
	//hash table destructor will deallocate by itself
	Catalogue::deleteList();//delete reading list
}

void Catalogue::save() {
	ofstream outFile(Catalogue::fileName);

	// write size
	outFile << size << endl;
	//in order save of isbn tree
	Catalogue::saveInOrder(&Catalogue::bstPublisher, outFile);
}

void Catalogue::saveInOrder(BST<string, string>* node, ofstream& outFile)
{
	if (node == nullptr)
		return;

	Catalogue::saveInOrder(node->getLeft(), outFile);
	Book book = Catalogue::find(node->getValueSecondary());
	outFile << book.getIsbn();
	outFile << ";";
	outFile << book.getTitle();
	outFile << ";";
	outFile << book.getAuthor();
	outFile << ";";
	outFile << book.getPublisher();
	outFile << endl;
	Catalogue::saveInOrder(node->getRight(), outFile);
}

Book* Catalogue::addBook(Book* book) {
	if (Catalogue::find(book->getIsbn()).getIsbn().length() != 0) {
		cout << "ISBN already in use" << endl;
		return nullptr;//isbn already used
	}
	Catalogue::size++;//mod file
	Catalogue::hashISBN.insert(*book);
	Catalogue::bstAuthor.add(new BST<string, string>(book->getAuthor(), book->getIsbn()));
	Catalogue::bstISBN.add(new BST<string, string>(book->getIsbn(), book->getIsbn()));
	Catalogue::bstPublisher.add(new BST<string, string>(book->getPublisher(), book->getIsbn()));
	Catalogue::bstTitle.add(new BST<string, string>(book->getTitle(), book->getIsbn()));
	save();
	return book;
}

Book Catalogue::find(string ISBN) {
	return Catalogue::hashISBN.search(ISBN);
}

void Catalogue::deleteBook(string ISBN) {
	Catalogue::size--;
	//change structures,deallocate memory, 
	Book book = Catalogue::find(ISBN);
	Catalogue::hashISBN.remove(book.getIsbn());
	delete Catalogue::bstAuthor.deleteValue(book.getAuthor(), book.getIsbn());
	delete Catalogue::bstISBN.deleteValue(book.getIsbn(), book.getIsbn());
	delete Catalogue::bstPublisher.deleteValue(book.getPublisher(), book.getIsbn());
	delete Catalogue::bstTitle.deleteValue(book.getTitle(), book.getIsbn());
	save();
}


/* Given a dynamically allocatedbinary tree, deallocate node memory*/
void Catalogue::deleteBST(BST<string, string>* node)
{
	if (node == nullptr)
		return;

	Catalogue::deleteBST(node->getLeft());
	Catalogue::deleteBST(node->getRight());
	delete node;
}

void Catalogue::deleteList()
{
	int num = Catalogue::readingList.countItems();
	if (num == 0)
		return;
	else
	{
		while (num > 0)
		{
			delete Catalogue::readingList.deleteFirst();
			num--;
		}
	}
}

/* Given a binary tree, print its nodes in inorder based on a key*/
void Catalogue::listSortSeq(int tree)
{
	if(tree==1)
		Catalogue::printInOrder(&Catalogue::bstAuthor);
	else if (tree == 2)
		Catalogue::printInOrder(&Catalogue::bstISBN);
	else if (tree == 3)
		Catalogue::printInOrder(&Catalogue::bstPublisher);
	else if (tree == 4)
		Catalogue::printInOrder(&Catalogue::bstTitle);
}

void Catalogue::printIndented(int tree)
{
	if (tree == 1)
		Catalogue::printLevelOrder(&Catalogue::bstAuthor);
	else if (tree == 2)
		Catalogue::printLevelOrder(&Catalogue::bstISBN);
	else if (tree == 3)
		Catalogue::printLevelOrder(&Catalogue::bstTitle);
}

void Catalogue::printInOrder(BST<string, string>* node)
{
	if (node == nullptr)
		return;

	Catalogue::printInOrder(node->getLeft());
	Book book = Catalogue::find(node->getValueSecondary());
	cout << book << endl;
	Catalogue::printInOrder(node->getRight());
}

/* Function to print level order traversal a tree*/
void Catalogue::printLevelOrder(BST<string, string>* root)
{
	int h = Catalogue::height(root);
	int nodeWidth = 1 << h-1;
	int levelWidth = Catalogue::largestString(root) * nodeWidth;
	int i;
	for (i = 1; i <= h; i++) {
		Catalogue::printGivenLevel(root, i, true, root);
		cout << endl;
	}
}

void Catalogue::printGivenLevel(BST<string, string>* root, int level, bool originalLevel , BST<string, string>* tree)
{
	if (originalLevel)
	{
		int h = Catalogue::height(tree);
		int nodeWidth = 1 << h - 1;
		int thisNodeWidth = 1 << level - 1;
		int levelWidth = Catalogue::largestString(tree) * nodeWidth;
		int thisWidth = Catalogue::largestString(tree) * thisNodeWidth;
		for (int i = 0; i < (levelWidth - thisWidth) / 2; i++)
		{
			cout << " ";
		}
	}

	if (level == 1) {
		if (root == nullptr) {
			for (int i = 0; i < Catalogue::largestString(tree); i++)
			{
				cout << " ";
			}
			return;
		}
		else
			cout << "(" << root->getValue() << ")";
	}
	if (root == nullptr) {
		Catalogue::printGivenLevel(nullptr, level - 1, false, tree);
		Catalogue::printGivenLevel(nullptr, level - 1, false, tree);
	}
	else if (level > 1)
	{
		Catalogue::printGivenLevel(root->getLeft(), level - 1, false, tree);
		Catalogue::printGivenLevel(root->getRight(), level - 1, false, tree);
	}

	if (originalLevel)
	{
		int h = Catalogue::height(tree);
		int nodeWidth = 1 << h - 1;
		int thisNodeWidth = 1 << level - 1;
		int levelWidth = Catalogue::largestString(tree) * nodeWidth;
		int thisWidth = Catalogue::largestString(tree) * thisNodeWidth;
		for (int i = 0; i < (levelWidth - thisWidth) / 2; i++)
		{
			cout << " ";
		}
	}
}

int Catalogue::height(BST<string, string>* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = Catalogue::height(node->getLeft());
		int rheight = Catalogue::height(node->getRight());

		/* use the larger one */
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

int Catalogue::largestString(BST<string, string>* node)
{
	if (node == nullptr)
		return 0;

	int left = Catalogue::largestString(node->getLeft());
	int right = Catalogue::largestString(node->getRight());
	int cur = node->getValue().length();
	if (cur > left && cur > right)
	{
		return cur;
	}
	else if (left > right)
	{
		return left;
	}
	else
	{
		return right;
	}
}

void Catalogue::listHashSeq()
{
	Catalogue::hashISBN.printTable(cout);
}

void Catalogue::printEfficiencies()
{
	cout << "Load Factor: " << (double)((int)(Catalogue::hashISBN.loadFactor() * 10000)) / 100 << "%" << endl;
	cout << "Longest Bucket: " << Catalogue::hashISBN.longestBucket() << endl;
	cout << "Average number of nodes in linked lists: " << (double)((int)(Catalogue::hashISBN.averageNodes() * 10000)) / 10000 << endl;
}

void Catalogue::addReadingList(string ISBN)
{
	Book temp = Catalogue::find(ISBN);
	if (temp.getIsbn().length() == 0) {//default string
		cout << "ISBN entered is not in the catalogue." << endl;
		return;
	}
	Node<Book>* tempN = new Node<Book>();
	tempN->setData(temp);
	Catalogue::readingList.addAnywhere(tempN);
}

void Catalogue::deleteReadingList(string ISBN)
{
	Book temp = Catalogue::find(ISBN);
	if (temp.getIsbn().length() == 0) {//default string
		cout << "ISBN entered is not in the catalogue." << endl;
		return;
	}
	delete Catalogue::readingList.deleteAnywhere(temp, false);
}

void Catalogue::showReadingList()
{
	cout << "Your reading list: " << endl;
	int num = Catalogue::readingList.countItems();
	if (num == 0)
		return;
	else
	{
		Node<Book>* book = Catalogue::readingList.findFirst();
		while (num > 0)
		{
			cout << book->getData();
			book = book->getNext();
			num--;
		}
	}
}

void Catalogue::printReadingList(string fileName)
{
	ofstream out(fileName);
	out << "Your reading list: " << endl;
	int num = Catalogue::readingList.countItems();
	if (num == 0)
		return;
	else
	{
		Node<Book>* book = Catalogue::readingList.findFirst();
		while (num > 0)
		{
			out << book->getData();
			book = book->getNext();
			num--;
		}
	}
}