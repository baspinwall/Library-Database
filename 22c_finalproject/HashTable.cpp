#include"HashTable.h"

HashTable::~HashTable()
{
	for (int i = 0; i < HashTable::SIZE; i++)
	{
		int num = HashTable::Table[i].countItems();
		
		if (num ==0)
			continue;
		else
		{
			while (num > 0)
			{
				delete HashTable::Table[i].deleteFirst();
				num--;
			}
		}
	}
}

int HashTable::hash(string key) const
{
	int index, sum = 0;

	for (unsigned int i = 0; i < key.length(); i++)
		sum += (int)key[i];
	index = sum % HashTable::SIZE;

	return index;
}

int HashTable::countBucket(int index) const
{
	if (index >= 0 && index < HashTable::SIZE)
		return HashTable::Table[index].countItems();
	else
		return -1;
}

int HashTable::longestBucket() const
{
	int longest = -1;
	int temp;
	for (int i = 0; i < HashTable::SIZE; i++)
	{
		temp = HashTable::countBucket(i);
		if (temp > longest)
		{
			longest = temp;
		}
	}
	return longest;
}

double HashTable::averageNodes() const
{
	double total = 0;
	double totalNodes = 0;
	int temp;
	for (int i = 0; i < HashTable::SIZE; i++)
	{
		temp = HashTable::countBucket(i);
		if (temp > 1)
		{
			total++;
			totalNodes += temp - 1;
		}
	}
	return totalNodes/total;
}

double HashTable::loadFactor() const
{
	double total = 0;
	int temp;
	for (int i = 0; i < HashTable::SIZE; i++)
	{
		temp = HashTable::countBucket(i);
		if (temp > 0)
		{
			total++;
		}
	}
	return total / HashTable::SIZE;
}

Book HashTable::search(string ISBN) const
{
	int index = hash(ISBN);
	int num = HashTable::Table[index].countItems();
	if (num==0)
		return Book();
	else
	{
		Node<Book>* book = HashTable::Table[index].findFirst();
		while (num > 0)
		{
			if (book->getData().getIsbn() == ISBN)
				return book->getData();
			else
				book = book->getNext();
			num--;
		}
		return Book();
	}
}

void HashTable::insert(Book b)
{
	int index = hash(b.getIsbn());
	Node<Book>* book = new Node<Book>();
	book->setData(b);
	HashTable::Table[index].addAnywhere(book);
}


int HashTable::remove(string ISBN)
{
	int index = hash(ISBN);
	int num = HashTable::Table[index].countItems();
	if (num != 0)
	{
		Node<Book>* book = HashTable::Table[index].findFirst();
		while (num > 0)
		{
			if (book->getData().getIsbn() == ISBN)
				delete HashTable::Table[index].deleteAnywhere(book->getData(),false);
			else
				book = book->getNext();
			num--;
		}
	}
	return -1;
}

/*void HashTable::printBucket(ostream& out, int index) const
{
	//assert(index >= 0 && index < SIZE);
	//out << fixed << setprecision(2);
	//HashTable::Table[index].inOrderPrint(out);
}
*/
void HashTable::printTable(ostream& out) const
{
	//out << "Books in the catalogue: " << endl << endl;
	for (int i = 0; i < SIZE; i++)
	{
		out << "Bucket " << i << ":" << endl;
		int num = HashTable::Table[i].countItems();
		if (num == 0)
			continue;
		else
		{
			Node<Book>* book = HashTable::Table[i].findFirst();
			while (num > 0)
			{
				out << book->getData();
				book = book->getNext();
				num--;
			}
		}
	}
	out << endl;
}
