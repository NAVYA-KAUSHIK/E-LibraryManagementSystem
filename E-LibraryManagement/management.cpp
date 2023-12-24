#include<iostream>
#include<conio.h> // to use getch function
#include<fstream>
using namespace std;
void Homepage();
class Student
{
private:
	int sid;
	string sname, sissued;
	float sfine;
	struct User
	{
		int userid;
		string username, issuedbooks;
		float fine;
		User* next_stud;
	};

	User* Mergestudent(User* left, User* right)
	{
		User* Res = nullptr;
		if (left == nullptr)
		{
			return right;
		}
		if (right == nullptr)
		{
			return left;
		}

		if (left->userid <= right->userid)
		{
			Res = left;
			Res->next_stud = Mergestudent(left->next_stud, right);

		}
		else
		{
			Res = right;
			Res->next_stud = Mergestudent(left, right->next_stud);

		}
		return Res;
	}

	User* Sortstudent(User* headstud)
	{
		if (headstud == nullptr || headstud->next_stud == nullptr)

		{
			return headstud;
		}
		User* ptr = headstud;
		User* temp = headstud->next_stud;
		while (temp != nullptr && temp->next_stud != nullptr)
		{
			ptr = ptr->next_stud;
			temp = temp->next_stud->next_stud;
		}
		User* mid = ptr->next_stud;
		ptr->next_stud = nullptr;

		User* left = Sortstudent(headstud);
		User* right = Sortstudent(mid);
		return Mergestudent(left, right);
	}

public:
	User* headstud = NULL;
	void Info();
	void insertstudent();
	void searchstudent();
	void updatestudent();
	void deletestudent();
	void studentsorting();
	void Showstudents();
	void Savestudents();
	void Readstudents();
};

bool existing = false;

void Student::Info()
{
	ifstream file("Students.txt");
	if (file)
	{
		existing = true;
	}
	file.close();
	if (existing)
	{
		Readstudents();
	}
	while (true) {
		system("cls");


		int choice;
		cout << "\n\n\n\t\t\t|==============================================|";
		cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
		cout << "\t\t\t|==============================================|";
		cout << "\n\n\t\t\t 1.INSERT NEW STUDENT's RECORD";
		cout << "\n\n\t\t\t 2.SEARCH STUDENT'S RECORD";
		cout << "\n\n\t\t\t 3.UPDATE  STUDENT'S RECORD ";
		cout << "\n\n\t\t\t 4.DELETE STUDENT'S RECORD";
		cout << "\n\n\t\t\t 5.SHOW ALL STUDENTS RECORDS";
		cout << "\n\n\t\t\t 6.GO BACK TO HOMEPAGE";
		cout << "\n\n\t\t\t 7.EXIT THE SYSTEM";
		cout << "\n\n\t\t\t ENTER YOUR CHOICE: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			insertstudent();
			break;
		}
		case 2:
		{
			searchstudent();
			break;
		}
		case 3:
		{
			updatestudent();
			break;
		}
		case 4:
		{
			deletestudent();
			break;
		}
		case 5:
		{
			studentsorting();
			Showstudents();
			break;
		}
		case 6:
		{
			Homepage();
			break;
		}
		case 7:
		{exit(1); }
		default:
		{cout << "\n\n INVALID CHOICE . PLEASE TRY AGAIN "; }
		}
		cin.ignore();
		cout << "\n\n Press ENTER to go back to Menu Page...";
		cin.get();
	}
}

void Student::insertstudent()
{
	system("cls");
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	User* new_user = new User;
	cout << "\n\n STUDENT'S ID(please enter in numerical format only ): ";
	cin >> new_user->userid;
	cout << "\n\n STUDENT'S NAME: ";
	cin >> new_user->username;
	cout << "\n\n BOOKS ISSUED: ";
	cin >> new_user->issuedbooks;
	cout << " FINE TO BE DEPOSITED(in numerical format only):  ";
	cin >> new_user->fine;

	new_user->next_stud = NULL;
	if (headstud == NULL)
	{
		headstud = new_user;
	}

	else
	{
		User* ptr = headstud;
		while (ptr->next_stud != NULL)
		{
			ptr = ptr->next_stud;
		}
		ptr->next_stud = new_user;
	}
	cout << "\n\t\t\t NEW STUDENT'S RECORD  INSERTED SUCCESSFULLY!";
}

void Student::searchstudent()
{
	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (headstud == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}

	else
	{
		cout << "\n\n ENTER ID OF THE STUDENT(please enter in numerical format only): ";
		cin >> test;
		User* ptr = headstud;
		while (ptr != NULL)
		{
			if (test == ptr->userid)
			{
				system("cls");
				cout << "\n\n\n\t\t\t |==============================================| ";
				cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
				cout << "\t\t\t|==============================================|";
				cout << "\n\n STUDENT'S ID :  " << ptr->userid;
				cout << "\n\n STUDENT'S NAME: " << ptr->username;
				cout << "\n\n BOOKS ISSUED: " << ptr->issuedbooks;
				cout << "\n\n FINE TO BE DEPOSITED: " << ptr->fine;
				found++;
			}
			ptr = ptr->next_stud;
		}
		if (found == 0)
		{
			cout << "\n\n YOUR SEARCH DID NOT MATCH ANY RECORD " << endl;
		}
	}
}

void Student::updatestudent()
{
	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (headstud == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}
	else
	{
		cout << "\n\n ENTER STUDENT'S ID(please enter in numerical format only): ";
		cin >> test;
		User* ptr = headstud;
		while (ptr != NULL)
		{
			if (test == ptr->userid)
			{
				system("cls");
				cout << "\n\n\n\t\t\t |==============================================| ";
				cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
				cout << "\t\t\t|==============================================|";
				cout << "\n\n STUDENT'S ID(please enter in numerical format only) :  ";
				cin >> ptr->userid;
				cout << "\n\n STUDENT'S NAME: ";
				cin >> ptr->username;
				cout << "\n\n  BOOKS ISSUED : ";
				cin >> ptr->issuedbooks;
				cout << "\n\n FINE TO BE DEPOSITED(in numerical format only): ";
				cin >> ptr->fine;
				found++;
				cout << "\n\n STUDENT'S RECORD  IS UPDATED SUCCESSFULLY! ";
			}
			ptr = ptr->next_stud;
		}
		if (found == 0)
		{
			cout << "\n\n YOUR SEARCH DID NOT MATCH ANY RECORD " << endl;
		}
	}
}

void Student::deletestudent()
{
	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (headstud == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}
	else
	{
		cout << "\n\n ENTER STUDENT'S ID (please enter in numerical format only): ";
		cin >> test;
		// when book that is to be deleted is the head of the linked list

		if (test == headstud->userid)
		{
			User* ptr = headstud;
			headstud = headstud->next_stud;
			delete ptr;
			cout << "\n\n STUDENT'S RECORD IS DELETED SUCCESSFULLY";
			found++;
		}
		else
		{
			User* prev = headstud;
			User* ptr = headstud;
			while (ptr != NULL)
			{
				if (test == ptr->userid)
				{
					prev->next_stud = ptr->next_stud;
					delete ptr;
					cout << "\n\n STUDENT'S RECORD  IS DELETED SUCCESSFULLY";
					found++;
					break;
				}
				prev = ptr;
				ptr = ptr->next_stud;
			}
		}
		if (found == 0)
		{
			cout << "\n\n STUDENT'S ID IS INVALID OR NOT FOUND";
		}
	}
}

void Student::studentsorting()
{
	if (headstud == NULL)
	{
		cout << "\n\n\n\t\t\t|==============================================|";
		cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
		cout << "\t\t\t|==============================================|";

		cout << "\n\n THE RECORD LIST IS EMPTY...";
		cin.ignore();
		cout << "\n\n Press ENTER to go back to Menu Page...";

		cin.get();
		Info();
	}
	headstud = Sortstudent(headstud);
}
void Student::Showstudents()
{
	system("cls");
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";

	User* ptr = headstud;
	while (ptr != NULL)
	{

		cout << "\n\n\t\t\t STUDENT'S ID :  " << ptr->userid;
		cout << "\n\n\t\t\t STUDENT'S NAME: " << ptr->username;
		cout << "\n\n\t\t\t  BOOKS ISSUED: " << ptr->issuedbooks;
		cout << "\n\n\t\t\t FINE TO BE DEPOSITED: " << ptr->fine;
		cout << "\n\n\t\t\t -------------------------------------------------";

		ptr = ptr->next_stud;
	}
}
void Student::Savestudents()
{
	ofstream file("Books.txt", ios::out);
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";

	cout << "\n\n STUDENT'S ID: ";
	cin >> sid;
	cout << "\n\n STUDENT'S NAME: ";
	cin >> sname;
	cout << "\n\n BOOKS ISSUED: ";
	cin >> sissued;
	cout << " FINE TO BE DEPOSITED:  ";
	cin >> sfine;
	file << sid << " " << sname << " " << sissued << " " << sfine << endl;
	file.close();
}
void Student::Readstudents()
{
	ifstream file("Students.txt");
	if (file.is_open())
	{
		while (file >> sid >> sname >> sissued >> sfine)
		{
			insertstudent();
		}
		file.close();
	}
	else
	{
		cout << "\n\n the server file is not open" << endl;
	}
}

class Library
{
private:
	int bid;
	string bname, bauthor, bpublisher;
	struct Node
	{
		int id;
		string name, author, publisher;
		Node* next_add; //pointer that points to next data .// Node is a datatype
	};

	Node* Merge(Node* left, Node* right)
	{
		Node* R = nullptr;
		if (left == nullptr)
		{
			return right;
		}
		if (right == nullptr)
		{
			return left;
		}

		if (left->id <= right->id)
		{
			R = left;
			R->next_add = Merge(left->next_add, right);
		}
		else
		{
			R = right;
			R->next_add = Merge(left, right->next_add);
		}
		return R;
	}

	Node* Sort(Node* head)
	{
		if (head == nullptr || head->next_add == nullptr)
		{
			return head;
		}
		Node* ptr = head;
		Node* temp = head->next_add;
		while (temp != nullptr && temp->next_add != nullptr)
		{
			ptr = ptr->next_add;
			temp = temp->next_add->next_add;
		}
		Node* mid = ptr->next_add;
		ptr->next_add = nullptr;

		Node* left = Sort(head);
		Node* right = Sort(mid);
		return Merge(left, right);
	}

public:
	Node* head = NULL; // first element of linked list
	void Menu();
	void Insert();
	void Search();
	void Update();
	void Delete();
	void Sorting();
	void Show();
	void Save();
	void Read();

};

bool exists = false;

void Library::Menu()
{
	ifstream file("Books.txt");
	if (file)
	{
		exists = true;
	}
	file.close();
	if (exists)
	{
		Read();
	}
	while (true) {
		system("cls");


		int choice;
		cout << "\n\n\n\t\t\t|==============================================|";
		cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
		cout << "\t\t\t|==============================================|";
		cout << "\n\n\t\t\t 1.INSERT NEW BOOK RECORD";
		cout << "\n\n\t\t\t 2.SEARCH BOOK";
		cout << "\n\n\t\t\t 3.UPDATE  BOOK RECORD ";
		cout << "\n\n\t\t\t 4.DELETE BOOK RECORD";
		cout << "\n\n\t\t\t 5.SHOW ALL BOOK RECORDS";
		cout << "\n\n\t\t\t 6.GO BACK TO HOMEPAGE";
		cout << "\n\n\t\t\t 7.EXIT THE SYSTEM";
		cout << "\n\n\t\t\t ENTER YOUR CHOICE: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Insert();
			break;
		}
		case 2:
		{
			Search();
			break;
		}
		case 3:
		{
			Update();
			break;
		}
		case 4:
		{
			Delete();
			break;
		}
		case 5:
		{
			Sorting();
			Show();
			break;
		}
		case 6:
		{
			Homepage();
			break;
		}
		case 7:
		{exit(1); }
		default:
		{cout << "\n\n INVALID CHOICE . PLEASE TRY AGAIN "; }
		}
		cin.ignore();
		cout << "\n\n Press ENTER to go back to Menu Page...";
		cin.get();
	}
}

void Library::Insert()
{
	system("cls");
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";

	Node* new_node = new Node;

	cout << "\n\n BOOK ID(please enter in numerical format only ): ";
	cin >> new_node->id;
	cout << "\n\n NAME: ";
	cin >> new_node->name;
	cout << "\n\n AUTHOR'S NAME: ";
	cin >> new_node->author;
	cout << " PUBLISHER'S NAME:  ";
	cin >> new_node->publisher;

	new_node->next_add = NULL;
	if (head == NULL)
	{
		head = new_node;
	}

	else
	{
		Node* ptr = head;
		while (ptr->next_add != NULL)
		{
			ptr = ptr->next_add;
		}
		ptr->next_add = new_node;
	}
	cout << "\n\t\t\t NEW BOOK INSERTED SUCCESSFULLY!";
}

void Library::Search()
{
	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (head == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}

	else
	{
		cout << "\n\n ENTER ID OF THE BOOK(please enter in numerical format only): ";
		cin >> test;
		Node* ptr = head;
		while (ptr != NULL)
		{
			if (test == ptr->id)
			{
				system("cls");
				cout << "\n\n\n\t\t\t |==============================================| ";
				cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
				cout << "\t\t\t|==============================================|";
				cout << "\n\n BOOK ID :  " << ptr->id;
				cout << "\n\n BOOK NAME: " << ptr->name;
				cout << "\n\n AUTHOR'S NAME: " << ptr->author;
				cout << "\n\n PUBLISHER'S NAME: " << ptr->publisher;
				found++;
			}
			ptr = ptr->next_add;
		}
		if (found == 0)
		{
			cout << "\n\n YOUR SEARCH DID NOT MATCH ANY BOOK " << endl;
		}
	}
}

void Library::Update()
{


	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (head == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}
	else
	{
		cout << "\n\n ENTER ID OF THE BOOK(please enter in numerical format only): ";
		cin >> test;
		Node* ptr = head;
		while (ptr != NULL)
		{
			if (test == ptr->id)
			{
				system("cls");
				cout << "\n\n\n\t\t\t |==============================================| ";
				cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
				cout << "\t\t\t|==============================================|";
				cout << "\n\n BOOK ID(please enter in numerical format only) :  ";
				cin >> ptr->id;
				cout << "\n\n BOOK NAME: ";
				cin >> ptr->name;
				cout << "\n\n AUTHOR'S NAME: ";
				cin >> ptr->author;
				cout << "\n\n PUBLISHER'S NAME: ";
				cin >> ptr->publisher;
				found++;
				cout << "\n\n BOOK IS UPDATED SUCCESSFULLY! ";
			}
			ptr = ptr->next_add;
		}
		if (found == 0)
		{
			cout << "\n\n YOUR SEARCH DID NOT MATCH ANY BOOK " << endl;
		}
	}
}

void Library::Delete()
{
	system("cls");
	int test;
	int found = 0;
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	if (head == NULL)
	{
		cout << "\n\n THE RECORD LIST IS EMPTY";
	}

	else
	{
		cout << "\n\n ENTER ID OF THE BOOK(please enter in numerical format only): ";
		cin >> test;
		// when book that is to be deleted is the head of the linked list

		if (test == head->id)
		{
			Node* ptr = head;
			head = head->next_add;
			delete ptr;
			cout << "\n\n BOOK IS DELETED SUCCESSFULLY";
			found++;
		}
		else
		{
			Node* prev = head;
			Node* ptr = head;
			while (ptr != NULL)
			{
				if (test == ptr->id)
				{
					prev->next_add = ptr->next_add;
					delete ptr;
					cout << "\n\n BOOK IS DELETED SUCCESSFULLY";
					found++;
					break;
				}
				prev = ptr;
				ptr = ptr->next_add;
			}
		}
		if (found == 0)
		{
			cout << "\n\n BOOK ID IS INVALID OR NOT FOUND";
		}
	}
}

void Library::Sorting()
{
	if (head == NULL)
	{
		cout << "\n\n\n\t\t\t|==============================================|";
		cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
		cout << "\t\t\t|==============================================|";

		cout << "\n\n THE RECORD LIST IS EMPTY...";
		cin.ignore();
		cout << "\n\n Press ENTER to go back to Menu Page...";

		cin.get();
		Menu();
	}
	head = Sort(head);
}
void Library::Show()
{
	system("cls");
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	Node* ptr = head;
	while (ptr != NULL)
	{

		cout << "\n\n\t\t\t BOOK ID :  " << ptr->id;
		cout << "\n\n\t\t\t BOOK NAME: " << ptr->name;
		cout << "\n\n\t\t\t AUTHOR'S NAME: " << ptr->author;
		cout << "\n\n\t\t\t PUBLISHER'S NAME: " << ptr->publisher;
		cout << "\n\n\t\t\t -------------------------------------------------";
		ptr = ptr->next_add;
	}
}

void Library::Save()
{
	ofstream file("Books.txt", ios::out);
	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";

	cout << "\n\n BOOK ID: ";
	cin >> bid;
	cout << "\n\n NAME: ";
	cin >> bname;
	cout << "\n\n AUTHOR'S NAME: ";
	cin >> bauthor;
	cout << " PUBLISHER'S NAME:  ";
	cin >> bpublisher;

	file << bid << " " << bname << " " << bauthor << " " << bpublisher << endl;
	file.close();
}
void Library::Read()
{
	ifstream file("Books.txt");
	if (file.is_open())
	{
		while (file >> bid >> bname >> bauthor >> bpublisher)
		{
			Insert();
		}
		file.close();
	}
	else
	{
		cout << "\n\n the server file is not open" << endl;
	}
}

void Homepage()
{
	system("cls");
	int option;

	Library data;
	Student stud;

	cout << "\n\n\n\t\t\t|==============================================|";
	cout << "\n\t\t\t|===========LIBRARY MANAGEMENT SYSTEM==========|" << endl;
	cout << "\t\t\t|==============================================|";
	cout << "\n\n\t\t\t\tWELCOME TO THE E_ LIBRARY, ADMIN";
	cout << "\n\t\t\t\tTO ENTER BOOK MODULE , PRESS 1";
	cout << "\n\t\t\t\tTO ENTER STUDENT MODULE , PRESS 2";
	cout << "\n\t\t\t\tTO EXIT THE SYSTEM, PRESS 3" << endl;

	cin >> option;
	switch (option) {
	case 1:
	{data.Menu(); }
	case 2:
	{stud.Info(); }
	case 3:
	{exit(1); }
	default:
	{cout << "\n\n INVALID CHOICE.PLEASE TRY AGAIN"; }
	}
}


int main()
{
	Homepage();

	return 0;
}
