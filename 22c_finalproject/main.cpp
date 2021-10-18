#include"Catalogue.h"
using namespace std;
int main()
{
	// initialize the catalogue module
	try {
		Catalogue::load();
	}
	catch (char *msg) {
		cout << msg << endl;
		cin.get();
		return 1;
	}
	
	int choice;
	do {
		string file;//user file for reading list
		string ISBNMod;//deletion/modification isbn
		Book book;//temporary book
		string newIsbn, newTitle, newAuthor, newPublisher, newDate;
		int secondaryChoice;

		cout<< "(1). Add new data" << endl
			<< "(2). Delete data" << endl
			<< "(3). Find and display one data record using the primary key" << endl
			<< "(4). List data in hash table sequence" << endl
			<< "(5). List data in key sequence(sorted)" << endl
			<< "(6). Print indented tree (may require resizing of console for proper display)" << endl
			<< "(7). Efficiency" << endl
			<< "(8). Reading list" << endl
			<< "(9). Quit" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter the details of the book to add to the catalogue" << endl;
			cin.ignore(1);
			cout << "Please enter ISBN: ";
			getline(cin, newIsbn);
			cout << "Please enter Title: ";
			getline(cin, newTitle);
			cout << "Please enter Author: ";
			getline(cin, newAuthor);
			cout << "Please enter Publisher: ";
			getline(cin, newPublisher);

			book = Book(newIsbn, newTitle, newAuthor, newPublisher);
			Catalogue::addBook(&book);
			break;

		case 2:
			cout << "Enter the ISBN of the book to delete." << endl;
			cin >> ISBNMod;
			Catalogue::deleteBook(ISBNMod);
			break;

		case 3:
			cout << "Enter the ISBN to search for" << endl;
			cin >> ISBNMod;
			book = Catalogue::find(ISBNMod);
			if (book.getIsbn().length() == 0)
				cout << "ISBN not found" << endl;
			else
				cout << book;
			break;

		case 4:
			Catalogue::listHashSeq();
			break;

		case 5:
			cout<< "Enter the key to print by:" << endl;
			cout<< "(1). Author" << endl
				<< "(2). ISBN" << endl
				<< "(3). Publisher" << endl
				<< "(4). Title" << endl;
			cin >> secondaryChoice;
			Catalogue::listSortSeq(secondaryChoice);
			break;

		case 6:
			cout<< "Enter the key to print by:" << endl;
			cout<< "(1). Author" << endl
				<< "(2). ISBN" << endl
				<< "(3). Title" << endl;
			cin >> secondaryChoice;
			Catalogue::printIndented(secondaryChoice);
			break;

		case 7:
			Catalogue::printEfficiencies();
			break;

		case 8://book reading list
			cout<< "(1). Add a book to the reading list" << endl
				<< "(2). Remove a book from the reading list" << endl
				<< "(3). Display the reading list" << endl
				<< "(4). Print the reading list to a file" << endl;
			cin >> secondaryChoice;
			if (secondaryChoice==1)
			{
				cout << "Enter the ISBN of the book to add" << endl;
				cin >> ISBNMod;
				Catalogue::addReadingList(ISBNMod);
			}
			else if (secondaryChoice == 2) 
			{
				cout << "Enter the ISBN of the book to delete" << endl;
				cin >> ISBNMod;
				Catalogue::deleteReadingList(ISBNMod);
			}
			else if (secondaryChoice == 3) 
			{
				Catalogue::showReadingList();
			}
			else if (secondaryChoice == 4) {
				cout << "Enter the filename to print to" << endl;
				cin >> file;
				Catalogue::printReadingList(file);
			}
			break;

		case 9://do nothing, exit at while condition
			break;

		default:
			cin.clear();
			cin.ignore(1024, '\n');
			cout << endl << "Invalid option selected." << endl;
			cout << "Only input choices 1-9 are valid." << endl;
			cout << "Re enter: " << endl;
			break;
		}
	} while (choice != 9);

	//free any dynamic memory
	Catalogue::close();
	cin.get();
	return 0;
}