#include<iostream>
#include<fstream>
#include<string>
#include <ctime>
#include <conio.h> 
#include <cstdlib>  
#include"myconsole.h"
#include "windows.h" 
using namespace std;
int RandomGenerator()
{
	srand(time(NULL));
	return (rand());
}

class point
{

public:
	point() { x = 0; y = 0; }
	point(int a, int b) { x = a; y = b; }
	int getX() { return x; }
	int getY() { return y; }
	void set(int a, int b) { x = a; y = b; }
	void setX(int a) { x = a; }
	void setY(int b) { y = b; }
	//increment x-coordinate.  If max limit is reached then increment y and set x to zero
	//return false if max limit for x and y is reached
	bool incrementX(point);
	//increment y-coordinate.  If max limit is reached return false
	bool incrementY(point);
	//decrement x-coordinate.  If x is already at 0 then go to line above at last x (decrement y)
	//return false if both x and y are at 0
	bool decrementX();
	//decrement y-coordinate.  If y is already at 0 then return false
	bool decrementY();
	bool operator != (point rhs)
	{
		return (!((x == rhs.x) && (y == rhs.y)));
	}

	friend ostream& operator<< (ostream& print, point toPrint);

private:
	int x;
	int y;
};
ostream& operator<< (ostream& print, point toPrint)
{
	print << toPrint.x << "," << toPrint.y;
	return print;
}
bool point::incrementX(point MaxPoint)
{
	bool returnValue = true;
	if (x < MaxPoint.x - 1)
		x++;
	else
		returnValue = false;

	return returnValue;
}
bool point::incrementY(point MaxPoint)
{
	bool returnValue = true;
	if (y < MaxPoint.y - 1)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}


template <class T>
class Stack
{
	class Node
	{
	public:
		T data;
		Node* next;
	};
	Node* head;
	Node* tail;
	int size = 0;

public:
	Stack()
	{
		head = tail = 0;
		size = 0;
	}
	void Push(T Udata)
	{
		size++;
		Node* temp = new Node;
		temp->data = Udata;
		if ((head == 0) && (tail == 0))
		{
			head = tail = temp;
			temp->next = 0;
		}
		else
		{
			temp->next = 0;
			tail->next = temp;
			tail = temp;
		}
	}
	void PrintAndPopRev()
	{
		if (Empty())
			return;
		else
		{
			T data;
			pop(data);
			PrintAndPopRev();
			cout << data << " --> ";
		}
	}
	void PrintAndPopForward()
	{
		T data;
		while (!Empty())
		{
			pop(data);
			cout << data << " --> ";
		}
		cout << "End\n";
	}
	bool Search(T Udata)
	{
		for (Node* i = head; i != 0; i = i->next)
			if (Udata == i->data)
				return true;
		return false;
	}
	bool Empty()
	{
		return ((head == 0) && (tail == 0));
	}
	bool pop()
	{
		size--;
		if (!Empty())
		{
			if (!size)
			{
				delete head;
				head = tail = NULL;
			}
			Node* i = head;
			for (; i->next != tail; i = i->next);
			tail = i;
			i = i->next;
			delete i;
			tail->next = NULL;
			return true;
		}
		return false;
	}
	bool pop(T& saveData)
	{
		size--;
		if (!Empty())
		{
			if (!size)
			{
				saveData = head->data;
				delete head;
				head = tail = NULL;
			}
			else
			{
				Node* i = head;
				for (; i->next != tail; i = i->next);
				tail = i;
				i = i->next;
				saveData = i->data;
				delete i;
				tail->next = NULL;
			}
			return true;
		}
		return false;
	}
	void Print()
	{
		point check(-1, -1);
		for (Node* i = head; i != nullptr; i = i->next)
		{
			if (i->data != check)
				cout << i->data << " --> ";
			else
				cout << "\n\n";
		}
	}
	bool top(T& saveData)
	{
		if (!Empty())
		{
			saveData = tail->data;
			return true;
		}
		return false;
	}
	~Stack()
	{
		Node* i = head;
		while (i != 0)
		{
			Node* del = i;
			i = i->next;
			delete del;
		}
	}
};

class Room {
	point startPoint;
	point currentPosition;
	point maxpoint;
	point gasper;
	point devil;
	point portal;
	point treasure;
	char** roomArray;
	int roomNo;

public:
	Room()
	{
		roomNo = 0;
		roomArray = nullptr;
		gasper.set(-1, -1);
		portal.set(-1, -1);
		devil.set(-1, -1);
		treasure.set(-1, -1);
	}

	Room& operator = (Room& rhs)
	{
		roomNo = rhs.roomNo;
		startPoint = rhs.startPoint;
		currentPosition = rhs.currentPosition;
		maxpoint = rhs.maxpoint;
		gasper = rhs.gasper;
		portal = rhs.portal;
		devil = rhs.devil;
		treasure = rhs.treasure;

		if (roomArray)
		{
			for (int i = 0; i < maxpoint.getX(); i++)
				delete[] roomArray[i];
			delete roomArray;
		}

		roomArray = new char* [maxpoint.getX()];
		for (int i = 0; i < maxpoint.getX(); i++)
		{
			roomArray[i] = new char[maxpoint.getY()];
			for (int j = 0; j < maxpoint.getY(); j++)
			{
				roomArray[i][j] = rhs.roomArray[i][j];
			}
		}
	}

	void PrintRoom()
	{
		system("cls");
		int max_X = maxpoint.getX();
		cout << "\n\n------------------------------------------------------------------------------------------------------------\n\t\t\t\t\t     You are in Room No: "<< GetRoomNo() <<"\n\n";
		for (int i = 0; i < max_X; i++)
		{
			int k = 0;
			for (; k < 35 - max_X; k++)
				cout << "  ";
			for (int j = 0; j < maxpoint.getY(); j++)
			{
				if ((i == currentPosition.getX()) && (j == currentPosition.getY()))
					cout << "@";
				else
					cout << roomArray[i][j];
			}
			cout << endl;
			SetColorAtPoint(currentPosition.getX() +k, currentPosition.getY() + 5, 0x0A | 0x0A);
		}
		cout << "\n\n------------------------------------------------------------------------------------------------------------";
	}

	int GetRoomNo()
	{
		return roomNo;
	}

	void LoadRoom(string fileName, bool& thisRoomHasTreasure, int number)
	{
		int xPoint = 0, yPoint = 0;
		char roomSetup = '\0';

		roomNo = number;

		ifstream roomFile;
		roomFile.open(fileName);

		roomFile >> xPoint;
		roomFile >> yPoint;
		maxpoint.set(xPoint, yPoint);
		
		roomFile >> xPoint;
		roomFile >> yPoint;
		startPoint.set(xPoint, yPoint);
		currentPosition.set(xPoint, yPoint);

		roomArray = new char* [maxpoint.getX()];
		for (int i = 0; i < maxpoint.getX(); i++)
		{
			roomArray[i] = new char[maxpoint.getY()];
			for (int j = 0; j < maxpoint.getY(); j++)
			{
				roomFile >> roomSetup;

				switch (roomSetup)
				{
					case 'X':
					{
						roomArray[i][j] = (char)219u;
						break; 
					}
					case '0':
					{
						roomArray[i][j] = ' ';
						break;
					}
					case 'P':
					{
						roomArray[i][j] = 'X';
						portal.set(i,j);
						break;
					}
					case 'G':
					{
						roomArray[i][j] = 'X';
						gasper.set(i, j);
						break;
					}
					case 'T':
					{
						roomArray[i][j] = 'X';
						treasure.set(i, j);
						thisRoomHasTreasure = true;
						break;
					}
					case 'b':
					{
						roomArray[i][j] = (char)219u;
						break;
					}
					case 'D':
					{
						roomArray[i][j] = 'X';
						devil.set(i, j);
						break;
					}
					default:
						break;
				}
			}
		}
		roomFile.close();
	}
	point GetCurrentPosition()
	{
		return currentPosition;
	}
	point GetStartPosition()
	{
		return startPoint;
	}
	void SetCurrentPosition(bool moveToStart, int enteredx = 0, int enteredy = 0)
	{
		if (moveToStart)
			currentPosition.set(startPoint.getX(),startPoint.getY());
		else
			currentPosition.set(enteredx, enteredy);
	}
	bool Move(const char direction)
	{
		bool moveSuccessfull = false;
		point temp = currentPosition;

		if (direction == UPKEY)
			moveSuccessfull = currentPosition.decrementX();
		else if (direction == DOWNKEY)
			moveSuccessfull = currentPosition.incrementX(maxpoint);
		else if (direction == RIGHTKEY)
			moveSuccessfull = currentPosition.incrementY(maxpoint);
		else if (direction == LEFTKEY)
			moveSuccessfull = currentPosition.decrementY();

		if (moveSuccessfull)
			if (roomArray[currentPosition.getX()][currentPosition.getY()] == (char)219u)
			{
				currentPosition = temp;
				moveSuccessfull = false;
			}
		PrintRoom();
		return moveSuccessfull;
	}
	char CheckForSpecial()
	{
		if ((currentPosition.getX() == portal.getX()) && currentPosition.getY() == portal.getY())
			return 'P';
		else if ((currentPosition.getX() == devil.getX()) && currentPosition.getY() == devil.getY())
		{
			system("cls");
			cout << "\n\n\n\t\t\tYou Ran into the Devil. Game Over. Bohoo :(\n";
			return 'Q';
		}
		else if ((currentPosition.getX() == gasper.getX()) && currentPosition.getY() == gasper.getY())
			return 'G';
		else if ((currentPosition.getX() == treasure.getX()) && currentPosition.getY() == treasure.getY())
			return 'T';
	}
};
class HauntedHouseMaze {

	int numberOfRooms;
	Room* arrOfRooms;
	int indxOfTreasureRoom;
	bool treasureFound = false;
	Stack<int> roomRecord;
	Stack<point> stepRecord;

public:
	HauntedHouseMaze(string fileName)
	{
		ifstream mainFile;
		string RoomName;
		indxOfTreasureRoom = -1;

		mainFile.open(fileName);
		mainFile >> numberOfRooms;
		arrOfRooms = new Room[numberOfRooms];
		for (int i = 0; i < numberOfRooms; i++)
		{
			mainFile >> RoomName;
			arrOfRooms[i].LoadRoom(RoomName, treasureFound, i+1);
			if (treasureFound)
			{
				indxOfTreasureRoom = i;
				treasureFound = false;
			}
		}
		mainFile.close();
	}
	void RunGame()
	{
		if (numberOfRooms)
		{
			char userInput = '\0';
			int currentRoom = -1, nextRoom = -1;
			bool loadNextRoom = true, specialkey = true;

			while ((userInput != 'Q') && (userInput != 'q'))
			{
				if (loadNextRoom)
				{
					LoadNextRoom(currentRoom, nextRoom);
					roomRecord.Push(currentRoom);
					stepRecord.Push(arrOfRooms[currentRoom].GetCurrentPosition());
					loadNextRoom = false;
				}
				userInput = CheckWhichKeyPressed(specialkey);
				if ((userInput == LEFTKEY) || (userInput == RIGHTKEY) || (userInput == UPKEY) || (userInput == DOWNKEY))
				{
					if(arrOfRooms[currentRoom].Move(userInput))
						stepRecord.Push(arrOfRooms[currentRoom].GetCurrentPosition());
					userInput = arrOfRooms[currentRoom].CheckForSpecial();
				}
				if (userInput == 'P')
				{
					if (CoinFlip())
						loadNextRoom = true;
					else
						if (!(BackTrack(currentRoom, nextRoom)))
							userInput = 'Q';
				}
				else if (userInput == 'G')
				{
					arrOfRooms[indxOfTreasureRoom].SetCurrentPosition(true);
					roomRecord.Push(indxOfTreasureRoom);
					arrOfRooms[indxOfTreasureRoom].PrintRoom();
					nextRoom = currentRoom = indxOfTreasureRoom;
					stepRecord.Push(arrOfRooms[currentRoom].GetCurrentPosition());
				}
				else if (userInput == 'T')
				{
					system("cls");
					cout << "\n\n\n\\t\t\t\t";
					cout << "You found the treasure. Wohoo :)\n";
					userInput = 'Q';
				}
			}
			cout << endl;
			cout << "\n\n\n--------------------------------------------------";
			cout << " The step track ";
			cout << "--------------------------------------------------\n";
			PrintAndPop();
			cout << "--------------------------------------------------";
			cout << "--------------------------------------------------\n";
			cout << endl << endl;
		}
	}
	void LoadNextRoom(int& curr, int& next)
	{
		next = (RandomGenerator() % numberOfRooms);
		if (curr == next)
			if(next != 0)
				next--;
			else
				next++;
		curr = next;
		arrOfRooms[curr].SetCurrentPosition(true);
		arrOfRooms[curr].PrintRoom();
	}
	bool BackTrack(int& curr, int& next)
	{ 
		point temp;
		
		stepRecord.pop(temp);
		while (temp != arrOfRooms[curr].GetStartPosition()) //pops steps till u reach start pos of curr room
			stepRecord.pop(temp);

		
		stepRecord.pop(temp);// pops the start pos and the portal pos
		if (stepRecord.Empty())
			return false;
		stepRecord.pop(temp);

		roomRecord.pop();//pops the curr room
		if (roomRecord.Empty())
			return false;
		roomRecord.top(curr);//moves prev room as curr room
		next = curr;//to keep the loadnextroom function in order

		arrOfRooms[curr].SetCurrentPosition(false, temp.getX(), temp.getY());//sets the curr pos at step behind portal
		arrOfRooms[curr].PrintRoom();
		return true;
	}
	bool BackTrackRecursive(int& curr)
	{
		point temp;
		stepRecord.pop(temp);
		while (temp != arrOfRooms[curr].GetStartPosition()) //pops steps till u reach start pos of curr room
			stepRecord.pop(temp);


		stepRecord.pop(temp);
		stepRecord.pop(temp);

		if (stepRecord.Empty())
			return false;
		return true;
	}
	void PrintAndPop()
	{
		int i = 0;
		point topPoint;
		Stack<point> temp;

		if ((roomRecord.Empty()))
			return;
		else
		{
			roomRecord.pop(i);
			if (!(stepRecord.Empty()))
			{
				bool roomCompleted = false;
				while (!roomCompleted)
				{
					stepRecord.pop(topPoint);
					if (!(topPoint != arrOfRooms[i].GetStartPosition()))
						roomCompleted = true;
					temp.Push(topPoint);
				}
			}

			PrintAndPop();

			cout << "Room Number: " << arrOfRooms[i].GetRoomNo() << endl;
			temp.PrintAndPopForward();
			cout << endl;
		}
	}
	bool CoinFlip()
	{
		for (int i = 0; i < 3; i++)
		{
			system("cls");
			cout << "\n\n\n\n\n\t\t\t\t\t\t";
			cout << "Tossing coin ";
			for (int j = 0; j < 3; j++)
			{
				cout << ". ";
				Sleep(360);
			}
		}
		cout << endl;
		bool value = (RandomGenerator() % 2);
		if (value)
			cout << "\t\t\t\t\t\tYou Won the toss!\n";
		else
			cout << "\t\t\t\t\t\tYou Lost the toss!\n";
		system("pause");
		return value;
	}
	void RunInRecursive()
	{
		bool End = false, Won = false, Gasper = false;
		RunInRecursive(End, Won, Gasper);
		if (Won)
		{
			system("cls");
			cout << "\n\n\n\t\t\t\tYou found the treasure. Wohoo :)\n";
		}
		cout << endl;
		cout << "\n\n\n-------------------------------";
		cout << " The step track ";
		cout << "---------------------------------------------\n";
		stepRecord.Print();
		cout << "\n---------------------------------------------";
		cout << "---------------------------------------------\n";
		cout << endl << endl;
	}
	void RunInRecursive(bool& GameEnded, bool& Won, bool& GasperFound, int lastRoom = -1)
	{
		if (GameEnded || Won)
			return;
		else
		{
			char userInput = '\0'; //variable declaration
			bool specialkey = true;
			int currentRoom;

			if (GasperFound) //sets room to treasure room if gasper is found
			{
				currentRoom = indxOfTreasureRoom;
				GasperFound = false;
			}
			else
			{
				currentRoom = (RandomGenerator() % numberOfRooms); //takes the new room to go into
				while (currentRoom == lastRoom)
					currentRoom = (RandomGenerator() % numberOfRooms);
			}


			arrOfRooms[currentRoom].SetCurrentPosition(true); //places player at starting position
			stepRecord.Push(arrOfRooms[currentRoom].GetStartPosition()); //pushes the position in stack

			while (!GameEnded && !Won) // loop to run operations in current function
			{
				arrOfRooms[currentRoom].PrintRoom();
				userInput = CheckWhichKeyPressed(specialkey, 3600);
				if ((userInput == LEFTKEY) || (userInput == RIGHTKEY) || (userInput == UPKEY) || (userInput == DOWNKEY))
				{
					if (arrOfRooms[currentRoom].Move(userInput))
						stepRecord.Push(arrOfRooms[currentRoom].GetCurrentPosition());
					userInput = arrOfRooms[currentRoom].CheckForSpecial();
				}
				if (userInput == 'P')
				{
					if (CoinFlip())
					{
						point dummy(-1, -1);
						stepRecord.Push(dummy);
						RunInRecursive(GameEnded, Won, GasperFound, currentRoom); //calls recursively till game ends on winning toss
						point temp;
						stepRecord.top(temp);
						arrOfRooms[currentRoom].SetCurrentPosition(false,temp.getX(), temp.getY());
					}
					else
					{	
						if (!(BackTrackRecursive(currentRoom)))
							GameEnded = true;
						return;
					}
				}
				else if (userInput == 'G')
				{
					GasperFound = true;
					point dummy(-1, -1);
					stepRecord.Push(dummy);
					RunInRecursive(GameEnded, Won, GasperFound, currentRoom);
					point temp;
					stepRecord.top(temp);
					arrOfRooms[currentRoom].SetCurrentPosition(false, temp.getX(), temp.getY());
					GasperFound = false;
				}
				else if (userInput == 'T')
				{
					Won = true;
					return;
				}
				else if (userInput == 'Q')
				{
					system("cls");
					cout << "\n\n\n\t\t\tYou Ran into the Devil. Game Over. Bohoo :(\n";
					GameEnded = true;
					return;
				}
			}
		}
	}
	void startScreen()
	{
		bool rules = false;
		cout << "\n\n\n------------------------Welcome to Haunted House Maze------------------------\n\n\n\n";

		cout <<"\t\t\t\t  "<< char(219u)<< endl;
		cout <<"\t\t\t\t " << char(219u) << char(219u) << char(219u) << endl;
		cout <<"\t\t\t\t" << char(219u) << char(219) << char(219u) << char(219u) << char(219u)<< endl;
		cout <<"\t\t\t\t" << char(219u)<< " " << char(219u)<< " " << char(219u)<< endl;
		cout <<"\t\t\t\t" << char(219u) << char(219) << char(219u) << char(219u) << char(219u) << endl;
		cout <<"\t\t\t\t" << char(219u) << char(219) << " " << char(219u) << char(219u)<< "   " << char(219u) << endl;
		cout <<"\t\t\t\t " << char(219u) << char(219u) << char(219u) << char(219u)<<"  " << char(219u) << char(219u) << char(219u)<< endl;
		cout <<"\t\t\t\t" << char(219u) << char(219u) << char(219u) << char(219u) << char(219u) << char(219u) << char(219u) << char(219u) << char(219u)<< endl;
		cout <<"\t\t\t\t" << char(219u) << "  " << char(219u) << char(219u) << char(219u) << char(219u) << char(219u) << endl;
		cout <<"\t\t\t\t    " << char(219u) << char(219u) << char(219u)<<endl;
		cout <<"\t\t\t\t     " << char(219u) << endl;

		cout << "\n\n\n";
		cout << "\t\t      Press 1 for rules press 0 to skip : ";
		cin >> rules;
		if (rules)
		{
			system("cls");
			cout << "\n\n\n----------------------------------------Rules--------------------------------------\n\n\n";
			cout << "1) traverse the maze using up down left right arrow keys\n";
			cout << "2) X are special positions in map which may be the treasure, devil, gasper or portal\n";
			cout << "3) Finding the TREASURE wins you the game\n";
			cout << "4) GASPER will lead you to the room with the treasure\n";
			cout << "5) DEVIL will eat you and you will lose\n";
			cout << "6) PORTAL will initiate coin flip. If you win you move to a random room. If you lose the flip you will travel back in time to the last room. If last room does not exist you will lose.\n";
			cout << "\n\n\n-----------------------------------------------------------------------------------\n";
			system("pause");

		}
		for (int i = 3; i != 0; i--)
		{
			system("cls");
			cout << "\n\n\n\n\n\t\t\t\t\t\t";
			cout << "Game starting in " << i<< "...";
			Sleep(720);
		}
	}
};
void start()
{
	HauntedHouseMaze house1("hauntedhouse.txt");
	house1.startScreen();
	house1.RunGame();
	//house1.RunInRecursive();
}
int main()
{
	start();
}