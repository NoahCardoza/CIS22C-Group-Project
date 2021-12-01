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

void printPatient(Patient *p);
void visitPatient(Patient *patient, int level);
void printHeader();

class IOManager
{
public:
	/**
	 * collects the input from the user and creates a new patient
	 */
	void createData();

	/**
	 * collects the input from the user and deletes a patient
	 */
	void deleteData();

	/**
	 * undoes a delete if a user has recently deletedData (gets information from deletedStack)
	 */
	void undoDelete();

	/**
	 * Collects input from the user, then finds the specified patient using it's primary key
	 */
	void findDataWithPrimaryKey();

	/**
	 * collects the input from the user then finds the specified patients using their secondary key
	 */
	void findDataWithSecondaryKey();

	/**
	 * displays all the current data
	 */
	void displayData();

	/**
	 * starts the main loop which displays the menu and collects the users input, then calls the appropriate function to handle the rest
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
		std::cout << "Please choose a database to open." << std::endl;
		loadFromUserInput();
	}

	std::cout << "Choose an option from the menu" << std::endl;
	std::cout << "\t(a)  - Add Patient" << std::endl;
	std::cout << "\t(d)  - Delete Patient" << std::endl;
	std::cout << "\t(u)  - Undo Delete Of Patient" << std::endl;
	std::cout << "\t(fp) - Patient with Primary Key" << std::endl;
	std::cout << "\t(fs) - Find Patient with Secondary Key" << std::endl;
	std::cout << "\t(l)  - Display All Data" << std::endl;
	std::cout << "\t(s)  - Save to file" << std::endl;
	std::cout << "\t(o)  - Load from file" << std::endl;
	std::cout << "\t(h)  - Displays this menu again" << std::endl;
	std::cout << "\t(e)  - Exit\n"
						<< std::endl;

	while (true)
	{
		std::cout << "> ";
		std::cin >> studentOption;

		if (studentOption == "a")
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
			database.displayDataIndented(visitPatient);
		}
		else if (studentOption == "a")
		{
			saveToFile();
		}
		else if (studentOption == "o")
		{
			loadFromUserInput();
		}
		else if (studentOption == "h")
		{
			std::cout << "Choose an option from the menu" << std::endl;
			std::cout << "\t(add) - Add Patient" << std::endl;
			std::cout << "\t(delete) - Delete Patient" << std::endl;
			std::cout << "\t(undo) - Undo Delete Of Patient" << std::endl;
			std::cout << "\t(find_primary) - Patient with Primary Key" << std::endl;
			std::cout << "\t(find_secondary) - Find Patient with Secondary Key" << std::endl;
			std::cout << "\t(display) - Display All Data" << std::endl;
			std::cout << "\t(save) - Save to file" << std::endl;
			std::cout << "\t(load) - Load from file" << std::endl;
			std::cout << "\t(help) - Displays this menu again" << std::endl;
			std::cout << "\t(exit) - Exit\n"
								<< std::endl;
		}
		else if (studentOption == "q")
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
	printHeader();
	printPatient(patient);
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

	printHeader();
	for (auto const &patient : patients)
	{
		printPatient(patient);
	}
}

void IOManager::saveToFile()
{
	std::string fileName;
	std::cout << "Enter the file name: ";
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

void printHeader()
{
	std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
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
	std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
}

void printPatient(Patient *p)
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

void visitPatient(Patient *p, int level)
{
	std::cout << std::setw(level * 4) << "";
	std::cout << p->getId() << "  " << p->getName() << std::endl;
}

void IOManager::displayData()
{
	std::cout << "Displaying all data" << std::endl;
	database.displayStatistics();
	printHeader();
	database.displayData(printPatient);
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

	std::cout << "Enter a patient id: " << std::endl;
	std::cin >> id;

	query.setId(id);
	if (database.primarySearch(&query, &dummy))
	{
		std::cout << "Error: A patient with this ID already exists!" << std::endl;
		return;
	}

	std::cout << "Enter a patient name: " << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);

	std::cout << "Enter a patient checkin time: " << std::endl;
	std::cin >> checkin;
	std::cout << "Enter a patient checkout time: " << std::endl;
	std::cin >> checkout;
	std::cout << "Enter a patient status (D, R (recovered), S (sick)): " << std::endl;
	std::cin >> status;
	std::cout << "Enter a patient age: " << std::endl;
	std::cin >> age;
	std::cout << "Enter a patient country: " << std::endl;
	std::cin >> country;
	std::cout << "Enter a patient gender (M, F, O): " << std::endl;
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
