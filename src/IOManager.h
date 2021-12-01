#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Patient.h"
#include "PatientDatabase.h"

//TODO There are still some compiler errors I believe
//
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

	bool loadFromFile(std::string);
	void loadFromUserInput();

	/**
	* creates a new IO manager object with the hashtable DB and the BST DB
	*/
	IOManager();

private:
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
	int studentOption;

	while (true)
	{
		if (database.isOpen())
		{
			std::cout << "Choose an option from the menu" << std::endl;
			std::cout << "\t1. Add Patient" << std::endl;
			std::cout << "\t2. Delete Patient" << std::endl;
			std::cout << "\t3. Undo Delete Of Patient" << std::endl;
			std::cout << "\t4. Find Patient with Primary Key" << std::endl;
			std::cout << "\t5. Find Patient with Secondary Key" << std::endl;
			std::cout << "\t6. Display All Data" << std::endl;
			std::cout << "\t7. Save to file" << std::endl;
			std::cout << "\t8. Load from file" << std::endl;
			std::cout << "\t9. Exit\n"
								<< std::endl;
			std::cin >> studentOption;

			switch (studentOption)
			{
			case 1:
				createData();
				break;
			case 2:
				deleteData();
				break;
			case 3:
				undoDelete();
				break;
			case 4:
				findDataWithPrimaryKey();
				break;
			case 5:
				findDataWithSecondaryKey();
				break;
			case 6:
				displayData();
				break;
			case 7:
				saveToFile();
				break;
			case 8:
				loadFromUserInput();
				break;
			case 9:
				std::cout << "Exiting..." << std::endl;
				return;
			default:
				std::cout << "Please choose one of the options above" << std::endl;
			}
		}
		else
		{
			std::cout << "Please choose a database to open." << std::endl;
			loadFromUserInput();
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
	patient->toStream(&std::cout);
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

	for (auto const &patient : patients)
	{
		patient->toStream(&std::cout);
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
		delete &deletedStack;
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

void visitPatient(Patient *patient)
{
	patient->toStream(&std::cout);
}

void IOManager::displayData()
{
	std::cout << "Displaying all data" << std::endl;
	database.displayData(visitPatient);
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
		delete deletedStack;
		deletedStack = new std::stack<Patient *>();
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
