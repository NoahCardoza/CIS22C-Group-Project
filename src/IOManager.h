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

void printTablePatient(Patient *p);
void visitPatient(Patient *patient, int level);
void printTableHeader();
void printTableDivider();

class IOManager
{
public:
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
	 * starts the main loop which displays the menu and collects the users input,
	 * then calls the appropriate function to handle the rest
	 */
	void startMainLoop();

	/**
	 * saves data to the save file
	 */
	void saveToFile();

	/**
	 * loads data from the save file
	 */
	bool loadFromFile(std::string);

	/**
	 * loads data from specified file from user
	 */
	void loadFromUserInput();

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
};

IOManager::IOManager()
{
	deletedStack = new std::stack<Patient *>();
}

void IOManager::startMainLoop()
{
	std::string studentOption;

	if (!database.isOpen())
	{
		std::cout << "No databse has been selected." << std::endl;
		database.create();
	}

	printMenue();

	while (true)
	{
		std::cout << "Enter an option (h for help) > ";
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
			database.displayDataIndented(visitPatient); // TODO: include in call stack
		}
		else if (studentOption == "t")
		{
			database.displayStatistics(); // TODO: include in call stack
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
		else if (studentOption == "e" || studentOption == "q")
		{
			saveToFile();
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
	std::cout << "│  (e)  - Exit                        │" << std::endl;
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
		delete deletedStack;
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
		delete deletedStack;
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
	std::getline(std::cin, name);

	std::cout << "Checkin time: ";
	std::cin >> checkin;
	std::cout << "Checkout time: ";
	std::cin >> checkout;
	std::cout << "Status (D, R (recovered), S (sick)): ";
	std::cin >> status;
	std::cout << "Age: ";
	std::cin >> age;
	std::cout << "Country: ";
	std::cin >> country;
	std::cout << "Gender (M, F, O): ";
	std::cin >> gender;

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
