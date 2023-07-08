#include<iostream>
#include<string>
using namespace std;

template <typename T> //Template with 'T' datatype
class LinkedList { //class of singly linked list

	class Node { // Nested Node class (private)
	public:
		T data; //each node holds data and pointer to next node
		Node* next;
	};
	Node* head; // pointers to start and end nodes
	Node* tail;
	int size; //size of list

public:

	LinkedList() // default constructor
	{
		head = tail = nullptr;
		size = 0;
	}
	LinkedList(LinkedList& toCopy) //Copy constructor to create copies of data on heap (Nodes)
	{
		head = toCopy.head;
		size = toCopy.size;
		if (toCopy.GetSize()) //Loop to deep copy Nodes
		{
			Iterator t = toCopy.begin();
			for (; t != nullptr; t.current = t.current->next)
				InsertAtHead(*t);
		}
		else
			head = tail = nullptr;
	}
	int GetSize() //Function to return size of list
	{
		return size;
	}
	class Iterator { //Nested Iterator class to iterate over list

		Node* current;
		Iterator(Node* toCopy)
		{
			current = toCopy;
		}
		friend class LinkedList; //Declared list as friend for access
	public:
		
		Iterator()// Default constructor
		{
			current = nullptr;
		}
		T& operator*() //overloaded dereferecing operator
		{
			return current->data;
		}
		Iterator& operator++() //overloaded increment operator 
		{
			current = current->next;
			return *this; //returns iterator pointing to the next node
		}
		Iterator& operator++(int) //Post increment operator
		{
			Iterator toReturn = this;
			current = current->next;
			return toReturn;
		}
		bool operator== (Iterator t) //returns true if data in Nodes where iterators are pointing is equal
		{
			return (current == t.current);
		}
		bool operator!= (Node* ptr)//return true if data in Nodes where iterators are pointing is NOT equal
		{
			return (current != ptr);
		}
	};
	Iterator begin() //returns iterator pointing to head of list
	{
		return (Iterator(head));
	}
	Iterator end()//returns iterator pointing to tail of list
	{
		return (Iterator(tail));
	}
	void InsertSorted(T element) //Inserts node in sorted order
	{
		size++;
		Node* temp = new Node;
		temp->data = element;
		if ((head == nullptr) && (tail == nullptr)) //check to see if list is empty
		{
			head = tail = temp;
			tail->next = nullptr;
			return;
		}
		else if (element < head->data) //Check to see if element is to be inserted at head
		{
			temp->next = head;
			head = temp;
			return;
		}
		else if (element >= tail->data) //Check to see if element is to be inserted at tail
		{
			tail->next = temp;
			tail = temp;
			temp->next = nullptr;
			return;
		}
		else
		{
			for (Node* i = head; i != nullptr; i = i->next) //Inserts at other sorted position
			{
				if (element < i->next->data)
				{
					temp->next = i->next;
					i->next = temp;
					return;
				}
			}
		}
	}
	void InsertBefore(T userData, Iterator i) //Inserts a node before the node at which iterator is pointing
	{
		size++;
		Node* temp = new Node;
		temp->data = userData;
		temp->next = i.current;
		for (Node* loopVar = head; loopVar != NULL; loopVar = loopVar->next)
			if (loopVar->next == temp->next)
			{
				loopVar->next = temp;
				return;
			}
	}
	void InsertAtHead(T userData) //Inserts node at head
	{
		size++;
		Node* temp = new Node;
		temp->data = userData;
		temp->next = head;
		if (head)
			head = tail = temp;
		else
			head = temp;
	}
	void InsertAtTail(T userData) //Inserts node at end of list
	{
		size++;
		Node* temp = new Node;
		temp->data = userData;
		temp->next = NULL;
		if ((head == NULL) && (tail == NULL))
			head = tail = temp;
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	void DeleteAtHead() //Deletes the first node
	{
		size--;
		if (head)
		{
			Node* del = head;
			head = head->next;
			delete del;
			if (!head)
				tail = NULL;
		}
		else
		{
			cout << "No elements left\n";
		}
	}
	void DeleteAtTail() //deletes the last node
	{
		size--;
		if (tail && (tail != head))
		{
			Node* del = tail;
			Node* i = head;
			for (; i->next != tail; i = i->next);
			tail = i;
			tail->next = NULL;
			delete del;
		}
		else if (tail && (tail == head))
		{
			delete head;
			head = tail = NULL;
		}
		else
		{
			cout << "No elements left\n";
		}
	}
	void DeleteBefore(Iterator t) //Deletes the node before the one where iterator is pointing
	{
		if (t.current == NULL) //check to see if the node to be deleted is at tail
		{
			DeleteAtTail();
		}
		else
		{
			size--;
			Node* temp = head;
			Node* del = head->next;
			if (del == t.current || head->next == NULL) //check to see if node is at head
				DeleteAtHead();
			else
			{
				for (; del->next != t.current; del = del->next, temp = temp->next);
				temp->next = t.current;
				if (del)
					delete del;
			}
		}
	}
	T ReturnDataAtHead() //returns the data of node at head
	{
		return (head->data);
	}
	void Print() //prints the list
	{
		for (Node* i = head; i != NULL; i = i->next)
			cout << (i->data);
	}
	~LinkedList() //destructor
	{
		while (head != NULL)
		{
			Node* del = head;
			head = head->next;
			delete del;
		}
	}
};

class Block { //class
	int start_byte_Id;
	int totalBytes;
public:
	Block() //default constructor
	{
		start_byte_Id = 0;
		totalBytes = 0;
	}
	Block(int userBytes, int userID) //overloaded constructor
	{
		start_byte_Id = userID;
		totalBytes = userBytes;
	}
	bool operator<(Block toCompare) //returns true is value of current block is less the rhs
	{
		return(start_byte_Id<toCompare.start_byte_Id);
	}
	bool operator>=(Block toCompare)//returns true is value of current block is greater or equal the rhs
	{
		return(start_byte_Id >= toCompare.start_byte_Id);
	}
	int GetStartByteID() //returns the ID saved in the block
	{
		return start_byte_Id;
	}
	int GetSize() //returns the totalBytes(size) saved in block
	{
		return totalBytes;
	}
	void SetSize( int updatedSize) //Updates the totalBytes saved in the block
	{
		totalBytes = updatedSize;
	}
	bool UpdatePool(int requiredSize) //Updates the pool block which calls this function
	{
		start_byte_Id += requiredSize;
		totalBytes -= requiredSize;
		return totalBytes;
	}
	
	friend ostream& operator<<(ostream & cout, Block& toPrint);
};
ostream& operator<< (ostream & cout, Block& toPrint) // overloaded stream insertion operator
{
	cout << toPrint.start_byte_Id << ", " << toPrint.totalBytes << " -> ";
	return cout;
}

class Program { //class program
	string ID;
	int size;
	LinkedList<Block> list;
public:
	Program() //default constructor
	{
		ID = '\0';
		size = 0;
	}
	Program(string userID, int userSize) //overloaded constructor
	{
		ID = userID;
		size = userSize;
	}
	bool CheckForContiguousCells() //Checks if for any 2 consecutive nodes (startID + size) of prev is = (startID) of next ie they are contiguous
	{
		LinkedList<Block>::Iterator t = list.begin();
		LinkedList<Block>::Iterator prevNode = list.begin();
		++t;
		for (; t != NULL; ++t)
		{
			if (((*prevNode).GetStartByteID() + (*prevNode).GetSize()) == ((*t).GetStartByteID()))
			{
				(*prevNode).SetSize((*prevNode).GetSize() + (*t).GetSize()); //updates value of prev if nodes are contiguous
				++t;
				list.DeleteBefore(t); //deletes the next one
				return false; //returns false if all changes havent been made yet
			}
		}
		return true; //returns true if NO contiguous cells were found
	}
	bool operator==(Program toCompare) //returns true if 2 programs are equal
	{
		return (ID == toCompare.ID);
	}
	bool operator==(string userID) //returns true if program ID matches user inserted string
	{
		return (ID == userID);
	}
	void AddBlock(Block toAdd) //Adds a block of memory to the program
	{
		list.InsertSorted(toAdd);
		bool clearedAllContiguousCells = false;
		while (!clearedAllContiguousCells) //checks for contiguous cells after memory is added
		{
			clearedAllContiguousCells = CheckForContiguousCells();
		}
	}
	bool ReturnMemory(Block& SaveData) //frees memory from program list
	{
		bool haveData = false;
		if (list.GetSize())
		{
			SaveData = list.ReturnDataAtHead();
			haveData = true;
			list.DeleteAtHead();
		}
		return haveData;
	}
	void ChangeSize(int enteredSize) //chenges the size of program total memory
	{
		size += enteredSize;
	}

	friend ostream& operator<<(ostream& cout, Program& toPrint);
};

ostream& operator<<(ostream& cout, Program& toPrint) //overloaded stream insertion operator
{
	cout << "ID: " << toPrint.ID << "\nsize: " << toPrint.size << "\n";
	toPrint.list.Print();
	cout << endl<<endl;
	return cout;
}

class MemoryManagementSystem { //MMS class
	
	LinkedList<Block> pool;
	LinkedList<Program> progs;
	long double sizeOfMemory;
	bool strategy;

public:
	MemoryManagementSystem(int userSize, bool userStrat) //overloaded constructor
	{
		pool.InsertSorted(Block (userSize, 0));
		sizeOfMemory = userSize;
		strategy = userStrat;
	}
	void PrintMemory() //prints pool and program config
	{
		cout << "---------------------  Free Pool -------------------------------\n";
		pool.Print();
		cout << endl << endl;
		cout << "--------------------- Program Pool -----------------------------\n";
		progs.Print();
		cout << endl;
		system("pause");
	}
	void FreeMemory(string progID, bool shouldPrint = true) //Deallocates memort of chosen program if it exists
	{
		bool present = false;
		LinkedList<Program>::Iterator it = progs.begin();
		bool exit = false;
		while ((!exit) && (progs.GetSize())) //checks if program is present
		{
			if (it == progs.end())
				exit = true;
			if ((*it) == progID)
			{
				present = true;
				break;
			}
			++it;
		}
		if (!present)
		{
			if (shouldPrint)
			{
				cout << "Program not Found in Memory\n";
				system("pause");
			}
			return; //returns if program wasnt found
		}
		if (it == progs.begin())  //returns memory space to pool and deletes program pool
		{
			Block SaveData;
			while ((*it).ReturnMemory(SaveData))
				pool.InsertSorted(SaveData);
			progs.DeleteAtHead();
			bool clearedAllContiguousCells = false;
			while (!clearedAllContiguousCells) //checks memory cells for contiguency
			{
				clearedAllContiguousCells = CheckForContiguousCells();
			}
		}
		else if (it == progs.end())//returns memory space to pool and deletes program pool
		{
			Block SaveData;
			while ((*it).ReturnMemory(SaveData))
				pool.InsertSorted(SaveData);
			progs.DeleteAtTail();
			bool clearedAllContiguousCells = false;
			while (!clearedAllContiguousCells)
			{
				clearedAllContiguousCells = CheckForContiguousCells();//checks memory cells for contiguency
			}
		}
		else // returns memory space to pool and deletes program pool
		{
			Block SaveData;
			while ((*it).ReturnMemory(SaveData))
				pool.InsertSorted(SaveData);
			++it;
			progs.DeleteBefore(it);
			bool clearedAllContiguousCells = false;
			while (!clearedAllContiguousCells)
			{
				clearedAllContiguousCells = CheckForContiguousCells();//checks memory cells for contiguency
			}
		}

	}
	int PoolExists() //Checks if any space is left in pool
	{
		return pool.GetSize();
	}
	void GetMemory(string progID, int progSize) //Allocates memory to program
	{
		bool present = false;
		if ((PoolExists() != -1) && (PoolExists() != 0))
		{
			LinkedList<Program>::Iterator it = progs.begin();
			bool exit = false;
			while ((!exit) && (progs.GetSize())) //checks if program is already present
			{
				if (it == progs.end())
					exit = true;
				if ((*it) == progID)
				{
					present = true;
					break;
				}
				++it;
			}
			if (!present) //creates new program if it wasnt already present
			{
				Program temp(progID, 0);
				progs.InsertAtTail(temp);
				it = progs.end();
			}
			int ID = GetMemory(progSize); //Gets memory for required size
			if (ID != -1)
			{
				(*it).AddBlock(Block(progSize, ID)); //adds block in program pool
				(*it).ChangeSize(progSize); //changes size of program accordingly
			}
			else
			{
				cout << "No Memory Available.\n";
				system("pause");
				if(!present)
					FreeMemory(progID, false); //if program didnt exist and memory not avalable then clears the new program 
			}
		}
		else
		{
			cout << "No Memory Available.\n";
			system("pause");
		}
		return;
	}
	bool CheckForContiguousCells() //checks for coniguous cells
	{
		LinkedList<Block>::Iterator t = pool.begin();
		LinkedList<Block>::Iterator prevNode = pool.begin();
		++t;
		for (; t != NULL; ++t)
		{
			if (((*prevNode).GetStartByteID() + (*prevNode).GetSize()) == ((*t).GetStartByteID()))
			{
				(*prevNode).SetSize((*prevNode).GetSize() + (*t).GetSize());
				++t;
				pool.DeleteBefore(t);
				return false;
			}
		}
		return true;
	}
	int GetMemory(int requiredSize) //gets memory from pool
	{
		if (strategy)
		{
			int thisIndex = -1;
			LinkedList<Block> :: Iterator it;
			it = pool.begin();
			bool exit = false;
			while (!exit)
			{
				if (it == pool.end())
					exit = true;
				if ((*it).GetSize() >= requiredSize) //reads pool for FIRST block where memory is available
				{
					cout << (*it).GetSize() << endl;
					thisIndex = (*it).GetStartByteID();
					if (!((*it).UpdatePool(requiredSize)))
					{
						++it;
						pool.DeleteBefore(it);
					}
					return thisIndex;
				}
				++it;
			}
			return thisIndex;
		}
		else
		{
			int thisIndex = -1;

			LinkedList<Block> ::Iterator it;
			LinkedList<Block> ::Iterator bestLocation;
			it = pool.begin();
			bool exit = false;
			int bestsize = INT_MAX;
			while (!exit)
			{
				if (it == pool.end())
					exit = true;
				if (((*it).GetSize() >= requiredSize) && ((*it).GetSize() < bestsize)) //reads ENTIRE pool for block where BESTSIZE of bytes are available
				{
					bestLocation = it;
					thisIndex = (*it).GetStartByteID();
					bestsize = (*it).GetSize();
				}
				++it;
			}
			if(thisIndex != -1)
				if (!((*bestLocation).UpdatePool(requiredSize)))
					pool.DeleteBefore(bestLocation);
			return thisIndex;
		}
	}
};

int main() //driver code
{
	int RAM_size; //to initialize values of RAM size and strategy
	bool allocationStrategy;
	cout << "----------------- Memory Management System --------------------\n";
	cout << "Please enter total number of bytes in memory: ";
	cin >> RAM_size;
	while (RAM_size <= 0)
	{
		cout << "Enter again: ";
		cin >> RAM_size;
	}
	cout << "Now select whether you like \"first fit\" or \"best fit\". \nPress 0 for best fit and 1 for first fit: ";
	cin >> allocationStrategy;
	MemoryManagementSystem MMS(RAM_size, allocationStrategy);

	int i = 3;
	while (i != 4) //repeats till user decides to exit (4)
	{
		system("cls");
		cout << "---------------------- User Menu ------------------------------\n";
		cout << "1. Create New Program\n";
		cout << "2. Terminate Program\n";
		cout << "3. View RAM Configuration\n";
		cout << "4. Exit\n\n\n";
		cout << "Please enter the number of your choice: ";
		cin >> i;
		system("cls");
		if (i == 1)
		{
			string userID;
			int userSize;
			cout << "Please enter the ID of the Program: ";
			cin >> userID;
			cout << "Please enter the size of memory required: ";
			cin >> userSize;
			while (userSize <= 0)
			{
				cout << "Enter again: ";
				cin >> userSize;
			}
			MMS.GetMemory(userID, userSize);

		}
		else if (i == 2)
		{
			string ID;
			cout << "Which Program do you want to terminate? ";
			cin >> ID;
			MMS.FreeMemory(ID);
		}
		else if (i == 3)
			MMS.PrintMemory();
	}
	cout << "GoodBye!\n";
	return 0;
}