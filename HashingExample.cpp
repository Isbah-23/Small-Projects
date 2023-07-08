#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;
bool isPrime(int num) //checks if number is prime
{
	if (num == 0 || num == 1)
		return false;
	for (int i = 2; i <= num / 2; ++i)
		if (num % i == 0) 
			return false;
	return true;
}
int GetSize(int num) // return next prime after num*2
{
	num *= 2;
	while (!isPrime(num))
		num++;
	return num;
}

class Book {//Book class declaration and definition

	int ISSN;
	string title;
	list <string> listOfAuthorsName;
	int numberOfCopiesAsReferenceBook;
	int numberOfCopiesAsIssueableBook;

public:

	Book()//Default constructor
	{}
	Book(const Book& rhs)//overloaded constructor
	{
		ISSN = rhs.ISSN;
		title = rhs.title;
		listOfAuthorsName = rhs.listOfAuthorsName;
		numberOfCopiesAsReferenceBook = rhs.numberOfCopiesAsReferenceBook;
		numberOfCopiesAsIssueableBook = rhs.numberOfCopiesAsIssueableBook;
	}
	void SetISSN(int userInput)//Sets the ISSN number
	{
		ISSN = userInput;
	}
	void SetTitle(string userInput)//Sets the title
	{
		title = userInput;
	}
	void SetList(list<string> userInput)
	{
		listOfAuthorsName = userInput;//Uses overloaded operator for deep copy of list
	}
	void SetIssue(int userInput)//sets the number of copies available as issueable book
	{
		numberOfCopiesAsIssueableBook = userInput;
	}
	void SetReference(int userInput)//sets the number of copies available as referenceable book
	{
		numberOfCopiesAsReferenceBook = userInput;
	}
	//Overloaded operators...comparison on basis of ISSN
	bool operator==(Book& rhs)
	{
		return (ISSN == rhs.ISSN);
	}
	bool operator==(Book rhs)const
	{
		return (ISSN == rhs.ISSN);
	}
	bool operator==(int rhs)
	{
		return (ISSN == rhs);
	}
	bool operator>(Book& rhs)
	{
		return (ISSN > rhs.ISSN);
	}
	bool operator<(Book& rhs)
	{
		return (ISSN < rhs.ISSN);
	}
	int operator%(int rhs)
	{
		return (ISSN % rhs);
	}
	Book& operator=(Book& rhs)//Overloaded assignment operator
	{
		ISSN = rhs.ISSN;
		title = rhs.title;
		listOfAuthorsName = rhs.listOfAuthorsName;
		numberOfCopiesAsReferenceBook = rhs.numberOfCopiesAsReferenceBook;
		numberOfCopiesAsIssueableBook = rhs.numberOfCopiesAsIssueableBook;

		return *this;
	}
	friend ostream& operator<<(ostream& cout, Book& toPrint);//overloaded ostream operator
	int GetISSN()//Return ISSN of the book
	{
		return ISSN;
	}
};
ostream& operator<<(ostream& cout, Book& toPrint)//overloaded ostream operator to print item of book type
{
	cout << "ISSN: " << toPrint.ISSN << endl;
	cout << "Title: " << toPrint.title << endl;
	cout << "Authors: ";
	list<string>::iterator t;
	for (t = toPrint.listOfAuthorsName.begin(); t != toPrint.listOfAuthorsName.end(); t++)
		cout << *t << " ";
	cout << endl;
	cout << "Number of copies as Issueable Book: " << toPrint.numberOfCopiesAsIssueableBook << endl;
	cout << "Number of copies as Reference Book: " << toPrint.numberOfCopiesAsReferenceBook << endl;

	return cout;
}
template<typename T> //class definition
class hashmap {

	vector<list<T>> hash_table;
	int table_size;
	int total_elements;

public:
	hashmap()//default constructor
	{
		table_size = GetSize(10);
		hash_table.resize(table_size);
		total_elements = 0;
	}
	int hashFunction(T& value)//returns location based on issn of book
	{
		return value % table_size;
	}
	int hashFunction(int value)//returns location based on int issn passed
	{
		return value % table_size;
	}
	void rehash()//grows the table by size*=2 + i to get first prime and re enters items to their new locations
	{
		list<Book> temp;
		for (int i = 0; i < hash_table.size(); i++)//.size()  = returns vector size
			if (!hash_table[i].empty())
			{
				list<Book> ::iterator iter = hash_table[i].begin();
				for (; iter != hash_table[i].end(); iter++)
					temp.push_back(*iter);//stores item in temp list
			}

		while (!hash_table.empty())
			hash_table.pop_back();//empties vector

		total_elements = 0;//resets size
		table_size = GetSize(table_size);

		hash_table.resize(table_size);
		
		list<Book> ::iterator it = temp.begin();//refills the vector
		for (; it != temp.end(); it++)
		{
			Book b = *it;
			Add(b);
		}
	}
	bool Add(T& element)//adds elements
	{
		if (!Search(element))//checks if element is already present
		{
			int location = hashFunction(element);
			hash_table[location].push_back(element);
			total_elements++;
			if (float(total_elements / table_size) > 0.5)//checks is rehashing is required
				rehash();
			return true;
		}
		return false;
	}
	void Review()//prints the library record location wise
	{
		for (int i = 0; i < hash_table.size(); i++)
			if (!hash_table[i].empty())//checks if items are stored on location
			{
				cout << "Location: " << i << ": \n";
				list<T> temp = hash_table[i];
				list<Book> ::iterator iter = temp.begin();
				for (; iter != temp.end(); iter++)
					cout << *iter << endl;
			}
	}
	bool Search(T& element)//searchs for element when book type item is passed
	{
		int location = hashFunction(element);
		list<T> temp = hash_table[location];
		list<Book> ::iterator iter = temp.begin();
		for (; iter != temp.end(); iter++)//if element is found in list returns true
			if (*iter == element)
				return true;
		return false;
	}
	bool Search(int ISSN, list<Book>::iterator& toReturn)//searches based on issn and returns pointer to object
	{
		int location = hashFunction(ISSN);
		list<Book> ::iterator iter = hash_table[location].begin();
		for (; iter != hash_table[location].end(); iter++)
			if (*iter == ISSN)
			{
				toReturn = iter;
				return true;
			}
		return false;
	}
	void Remove(Book& toDel)//removes item from the record
	{
		int location = hashFunction(toDel);
		hash_table[location].remove(toDel);
		total_elements--;//decrements the toal no of elements
	}
};
class DataBaseManagementSystem//class definition
{
	hashmap<Book> data_table;

public:
	bool Add()//takes required data from user to creat book item and adds it to record
	{
		Book b;
		list<string> authors;

		int userInput;
		string names;

		cout << "Enter ISSN: ";
		cin >> userInput;
		if (userInput < 0)//makes sure issn is positive for hash function
			userInput = (-userInput);
		b.SetISSN(userInput);

		cout << "Enter title: ";
		cin.ignore();
		getline(cin, names);
		b.SetTitle(names);

		cout << "Enter names of author(s), enter \"null\" to stop: ";
		getline(cin, names);
		while (names != "null")
		{
			authors.push_back(names);
			getline(cin, names);
		}
		b.SetList(authors);

		cout << "Enter number of copies available as reference book: ";
		cin >> userInput;
		b.SetReference(userInput);

		cout << "Enter number of copies available as issueable book: ";
		cin >> userInput;
		b.SetIssue(userInput);

		return data_table.Add(b);
	}
	void Review()//displays entire record
	{
		data_table.Review();
	}
	bool Update(int ISSN)//takes suitable inputs from user to update record of already existing item
	{
		list<Book>::iterator bookAt;
		if (data_table.Search(ISSN, bookAt))//checks if item is in list
		{
			int userInput =0;
			string names;
			while (true)
			{
				int option = -1;
				system("cls");
				cout << "---------------------------------Current Data-------------------------\n";
				cout << *bookAt;
				cout << "------------------------------------Update----------------------------\n";
				cout << "Select your Option: \n";
				cout << "1) Update Title\n";
				cout << "2) Update List of Authors\n";
				cout << "3) Update number of copies available as issueable book\n";
				cout << "4) Update number of copies available as reference book\n";
				cout << "5) Exit\nOption(number): ";
				cin >> option;

				if (option == 1)
				{
					cout << "Enter Title: ";
					cin.ignore();
					getline(cin, names);
					(*bookAt).SetTitle(names);
				}
				else if (option == 2)
				{
					list<string> authors;
					cout << "Enter names of author(s), enter \"null\" to stop: ";
					cin.ignore();
					getline(cin, names);
					while (names != "null")
					{
						authors.push_back(names);
						getline(cin, names);
					}
					(*bookAt).SetList(authors);
				}
				else if (option == 4)
				{
					cout << "Enter number of copies available as reference book: ";
					cin >> option;
					(*bookAt).SetReference(option);
				}
				else if (option == 3)
				{
					cout << "Enter number of copies available as issueable book: ";
					cin >> option;
					(*bookAt).SetIssue(option);
				}
				else if (option == 5)
					break;
			}
			return true;
		}
		return false;//returns false if item was not in inventory
	}
	bool Remove(int ISSN)//removes item with given issn from list
	{
		list<Book>::iterator bookAt;
		if (data_table.Search(ISSN, bookAt))
		{
			Book temp = (*bookAt);
			data_table.Remove(temp);
			return true;
		}
		return false;
	}
};
void Menu()//menu for user to choose from
{
	DataBaseManagementSystem Library;

	while (true)
	{
		int option = -1;
		system("cls");
		cout << "------------------------------------LIBRARY DATABASE----------------------------------------\n";
		cout << "Select your Option: \n";
		cout << "1) Add new Item\n";
		cout << "2) Review Inventory\n";
		cout << "3) Edit Details\n";
		cout << "4) Remove Item\n";
		cout << "5) Exit\nOption(number): ";
		cin >> option;

		if (option == 1)
		{
			if (Library.Add())
				cout << "Successfully added\n";
			else
				cout << "Item with ISSN already exists\n";
			system("pause");
		}
		else if (option == 2)
		{
			Library.Review();
			system("pause");
		}
		else if (option == 3)
		{
			cout << "Please enter ISSN number: ";
			cin >> option;
			if (option < 0)
				option = (-option);
			if (!Library.Update(option))
				cout << "Item not found\n";
			system("pause");
		}
		else if (option == 4)
		{
			cout << "Please enter ISSN number: ";
			cin >> option;
			if (option < 0)
				option = (-option);
			if (!Library.Remove(option))
				cout << "Item not found\n";
			else
				cout << "Removed succesfully.\n";
			system("pause");
		}
		else if (option == 5)
			break;
	}
}
int main()//Main
{
	Menu();
	system("cls");
	cout << "Goodbye\n";
	return 0;
}
