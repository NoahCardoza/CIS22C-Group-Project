#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>

#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Patient.h"
#include "PatientDatabase.h"

/**
 * @author Aryan Garg and Noah Cardoza
 *
 * This class is responsible for the main structure of the program, and takes in the input from the user and handles it accordingly.
 * To start the program, call the startMainLoop() method
 */
class IOManager
{
public:
	/**
	 * loads data from the save file
	 */
	bool loadFromFile(std::string);

	/**
	 * starts the main loop which displays the menu and collects the users input,
	 * then calls the appropriate function to handle the rest
	 */
	void startMainLoop();

	/**
	* creates a new IO manager object with the hashtable DB and the BST DB
	*/
	IOManager();

private:
	/**
	 * class interface to manipulate / display the data
	 */
	PatientDatabase database;

	/**
	 * stack used for the undoDelete() method.
	 * whenever a patient is deleted, it will be pushed onto this stack.
	 * Whenever the user saves everything to a file, this stack gets refreshed.
	 */
	std::stack<Patient *> *deletedStack;

	/**
	 * deletes deletedStack and frees the memory of all of the Patients in deletedStack
	 * also creates a new Stack
	 */
	void deleteStack();

	/**
	 * saves data to the save file
	 */
	void saveToFile();

	/**
	 * loads data from specified file from user
	 */
	void loadFromUserInput();

	/**
	 * print out a menue to the user
	 */
	void printMenue();

	/**
	 * print the line divinding parts of the table
	 */
	void printTableDivider();

	/**
	 * prints out the header for the table when puting database
	 * information
	 */
	void printTableHeader();

	/**
	 * prints out a patient in table form
	 */
	static void printTablePatient(Patient *);

	/**
	 * prints out a patient information when displaying
	 * the indented tree
	 */
	static void visitPatient(Patient *, int);

	/**
	 * collects the input from the user and creates a new patient
	 */
	void createData();

	/**
	 * collects the input from the user and deletes a patient
	 */
	void deleteData();

	/**
	 * undoes a delete if a user has recently deletedData
	 * (gets information from deletedStack)
	 */
	void undoDelete();

	/**
	 * Collects input from the user, then finds the specified patient using it's
	 * primary key
	 */
	void findDataWithPrimaryKey();

	/**
	 * collects the input from the user then finds the specified patients using
	 * their secondary key
	 */
	void findDataWithSecondaryKey();

	/**
	 * displays all the current data
	 */
	void displayData();

	/**
	 * prints the project information and credits
	 */
	void printProjectInfo();
};

void IOManager::deleteStack()
{
	while (!deletedStack->empty())
	{
		Patient *p = deletedStack->top();
		deletedStack->pop();
		delete p;
	}

	delete deletedStack;
	deletedStack = new std::stack<Patient *>();
}

IOManager::IOManager()
{
	deletedStack = new std::stack<Patient *>();
}

void IOManager::startMainLoop()
{
	std::string studentOption;

	printProjectInfo();

	if (!database.isOpen())
	{
		std::cout << "No database has been selected." << std::endl;
		database.create();
	}

	printMenue();

	while (true)
	{
		std::cout << "Enter an option (h for help) > ";
		studentOption = "";
		std::cin >> studentOption;

		if (studentOption == "i")
		{
			createData();
		}
		else if (studentOption == "d")
		{
			deleteData();
		}
		else if (studentOption == "u")
		{
			undoDelete();
		}
		else if (studentOption == "fp")
		{
			findDataWithPrimaryKey();
		}
		else if (studentOption == "fs")
		{
			findDataWithSecondaryKey();
		}
		else if (studentOption == "l")
		{
			displayData();
		}
		else if (studentOption == "li")
		{
			printTableDivider();
			database.displayDataIndented(visitPatient);
			printTableDivider();
		}
		else if (studentOption == "t")
		{
			database.displayStatistics();
		}
		else if (studentOption == "s")
		{
			saveToFile();
		}
		else if (studentOption == "o")
		{
			loadFromUserInput();
		}
		else if (studentOption == "h" || studentOption == "?" || studentOption == "help")
		{
			printMenue();
		}
		else if (studentOption == "c" || studentOption == "credits")
		{
			printProjectInfo();
		}
		else if (studentOption == "q")
		{
			saveToFile();
			std::cout << "Exiting..." << std::endl;
			return;
		}
		else if (studentOption == "!q") // similar to vim (quit without saving)
		{
			std::cout << "Exiting..." << std::endl;
			return;
		}
		else
		{
			std::cout << "Invalid option. Please try again." << std::endl;
		}
	}
}

void IOManager::printMenue()
{
	std::cout << "┌=====================================┐" << std::endl;
	std::cout << "│                 MENU                │" << std::endl;
	std::cout << "│=====================================│" << std::endl;
	std::cout << "│  (i)  - Insert                      │" << std::endl;
	std::cout << "│  (d)  - Delete                      │" << std::endl;
	std::cout << "│  (u)  - Undo deletion               │" << std::endl;
	std::cout << "│  (fp) - Find by primary key         │" << std::endl;
	std::cout << "│  (fs) - Find all by secondary key   │" << std::endl;
	std::cout << "│  (l)  - List                        │" << std::endl;
	std::cout << "│  (t)  - Statistics                  │" << std::endl;
	std::cout << "│  (s)  - Save to CSV                 │" << std::endl;
	std::cout << "│  (o)  - Open database from CSV      │" << std::endl;
	std::cout << "│  (h)  - Help                        │" << std::endl;
	std::cout << "│  (q)  - Quit                        │" << std::endl;
	std::cout << "└─────────────────────────────────────┘" << std::endl;
}

void IOManager::findDataWithPrimaryKey()
{
	std::string primaryKey;
	std::cout << "Enter the primary key: ";
	std::cin >> primaryKey;

	Patient *patient = nullptr;
	Patient myPatient = Patient(primaryKey, "");

	if (!database.primarySearch(&myPatient, &patient))
	{
		std::cout << "No patient found with that primary key" << std::endl;
		return;
	}

	std::cout << "Patient found:" << std::endl;
	printTableHeader();
	printTablePatient(patient);
	printTableDivider();
}

void IOManager::findDataWithSecondaryKey()
{
	std::string secondaryKey;
	std::cout << "Enter the secondary key: ";
	std::cin.ignore();
	std::getline(std::cin, secondaryKey);

	Patient myPatient = Patient("", secondaryKey);
	std::vector<Patient *> patients;

	if (!database.secondarySearch(&myPatient, patients))
	{
		std::cout << "No patient found with that secondary key" << std::endl;
		return;
	}

	std::cout << "Patient(s) found:" << std::endl;

	printTableHeader();
	for (auto const &patient : patients)
	{
		printTablePatient(patient);
	}
	printTableDivider();
}

void IOManager::saveToFile()
{
	std::string fileName;
	std::cout << "Enter the file name to save to: ";
	std::cin >> fileName;

	if (database.save(fileName))
	{
		std::cout << "Successfully saved to file" << std::endl;
		deleteStack();
	}
	else
	{
		std::cout << "Failed to save to file" << std::endl;
	}
}

bool IOManager::loadFromFile(std::string fileName)
{
	if (database.isOpen())
	{
		database.close();
	}

	return database.open(fileName);
}

void IOManager::loadFromUserInput()
{
	std::string fileName;
	std::cout << "Enter the file name: ";
	std::cin >> fileName;

	if (loadFromFile(fileName))
	{
		std::cout << "Successfully loaded from file" << std::endl;
		deleteStack();
	}
	else
	{
		std::cout << "Failed to load from file" << std::endl;
	}
}

void IOManager::printTableDivider()
{
	std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
}

void IOManager::printTableHeader()
{
	printTableDivider();
	std::cout << left;
	std::cout << " " << setw(36) << "ID"
						<< "  ";
	std::cout << " " << setw(18) << "Name"
						<< "  ";
	std::cout << " " << setw(10) << "Check-in"
						<< "  ";
	std::cout << " " << setw(10) << "Check-out"
						<< "  ";
	std::cout << " Status  ";
	std::cout << " Age  ";
	std::cout << " Country  ";
	std::cout << " Gender  ";
	std::cout << std::endl;
	printTableDivider();
}

void IOManager::printTablePatient(Patient *p)
{
	std::cout << left;
	std::cout << " " << p->getId() << "  ";
	std::cout << " " << setw(18) << p->getName() << "  ";
	std::cout << " " << p->getCheckin() << "  ";
	std::cout << " " << p->getCheckout() << "  ";
	std::cout << " " << setw(6) << p->getStatus() << "  ";
	std::cout << " " << setw(3) << p->getAge() << "  ";
	std::cout << " " << setw(7) << p->getCountry() << "  ";
	std::cout << " " << setw(6) << p->getGender() << "  ";
	std::cout << std::endl;
}

void IOManager::visitPatient(Patient *p, int level)
{
	std::cout << std::setw(level * 4) << "";
	std::cout << p->getId() << "  " << p->getName() << std::endl;
}

void IOManager::displayData()
{
	printTableHeader();
	database.displayData(printTablePatient);
	printTableDivider();
}

void IOManager::createData()
{
	Patient query;
	Patient *dummy;

	string id;
	string name;
	int checkin;
	int checkout;
	char status;
	int age;
	string country;
	char gender;

	std::cout << "ID: ";
	std::cin >> id;

	query.setId(id);
	if (database.primarySearch(&query, &dummy))
	{
		std::cout << "Error: A patient with this ID already exists!" << std::endl;
		return;
	}

	std::cout << "Name: ";
	std::cin.ignore();
	// std::cin >> name;
	std::getline(std::cin, name);

	if (name.length() == 0)
	{
		std::cout << "Error: Name cannot be empty!" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	std::cout << "Checkin time: ";
	std::cin >> checkin;

	if (checkin < 1546300800)
	{
		std::cout << "Error: Invalid Checkin" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	std::cout << "Checkout time: ";
	std::cin >> checkout;

	if (checkout <= checkin)
	{
		std::cout << "Error: Invalid Checkout" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	std::cout << "Status (D, R (recovered), S (sick)): ";
	std::cin >> status;

	if (status != 'D' && status != 'R' && status != 'S')
	{
		std::cout << "Error: Invalid Status" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	std::cout << "Age: ";
	std::cin >> age;

	if (age <= 0)
	{
		std::cout << "Error: Invalid Age" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	std::cout << "Country: ";
	std::cin >> country;
	std::cout << "Gender (M, F, O): ";
	std::cin >> gender;

	if (gender != 'M' && gender != 'F' && gender != 'O')
	{
		std::cout << "Error: Invalid Gender" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}

	Patient *myPatient = new Patient(id, name, checkin, checkout, status, age, country, gender);
	if (database.insert(myPatient))
	{
		std::cout << "Successfully entered patient to database!" << std::endl;
	}
	else
	{
		std::cout << "Error entering patient to database!" << std::endl;
	}
}

void IOManager::deleteData()
{
	std::cout << "Enter the ID of the patient to delete:" << std::endl;

	string id;
	std::cin >> id;

	Patient patientKey = Patient(id, "");
	Patient *itemOut;

	if (database.remove(&patientKey, &itemOut))
	{
		std::cout << "Successfully deleted patient from database!" << std::endl;
	}
	else
	{
		std::cout << "Error deleting patient from database!" << std::endl;
	}

	deletedStack->push(itemOut);
}

void IOManager::undoDelete()
{
	if (deletedStack->empty())
	{
		std::cout << "No deleted items to undo." << std::endl;
		return;
	}

	Patient *itemOut = deletedStack->top();
	deletedStack->pop();

	if (database.insert(itemOut))
	{
		std::cout << "Successfully undeleted patient from database!" << std::endl;
	}
	else
	{
		std::cout << "Error undeleting patient from database!" << std::endl;
	}
}

void IOManager::printProjectInfo()
{
	cout << "GENERAL INFORMATION" << endl;
	cout << "====================" << endl;
	cout << "This program is a database to hold covid-19 patients information / status." << endl;
	cout << "It uses a Binary Search Tree and a Hashtable to store the data." << endl;
	cout << "The program is able to add, delete, search, and print the data." << endl;
	cout << "The program is able to save and load the data from a file." << endl;

	cout << endl;

	cout << "CREDITS" << endl;
	cout << "=======" << endl;
	cout << "This program was created by: " << endl;
	cout << "Noah Cardoza - Team Leader, Worked on Team Coordination (Unit 1) and File I/O (Unit 5)" << endl;
	cout << "Omar Hafud - Worked on Binary Search Tree (Unit 2)" << endl;
	cout << "Sarina Karki - Worked on Hashtable (Unit 3)" << endl;
	cout << "Aryan Garg - Worked on Screen I/O (Unit 4)" << endl;

	cout << endl;
}