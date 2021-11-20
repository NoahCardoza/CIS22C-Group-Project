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
	* creates a new IO manager object with the hashtable DB and the BST DB
	*/
	IOManager(HashTable<Patient> &, BinarySearchTree<Patient> &);

private:
	/**
	 * hashtable DB to store the patients
	 */
	HashTable<Patient> hashtableDB;

	/**
	 * BST DB to store the patients.
	 */
	BinarySearchTree<Patient> bstDB;

	PatientDatabase database;

	/**
	 * stack used for the undoDelete() method.
	 * whenever a patient is deleted, it will be pushed onto this stack.
	 * Whenever the user saves everything to a file, this stack gets refreshed.
	 */
	std::stack<Patient> deletedStack;
};

IOManager::IOManager(HashTable<Patient> &hashTable, BinarySearchTree<Patient> &bst)
{
	this->bstDB = bst;
	this->hashtableDB = hashTable;
}

void IOManager::startMainLoop()
{
	while (true)
	{
		std::cout << "Choose an option from the menu" << std::endl;
		std::cout << "\t1. Add Patient" << std::endl;
		std::cout << "\t2. Delete Patient" << std::endl;
		std::cout << "\t3. Undo Delete Of Patient" << std::endl;
		std::cout << "\t4. Find Patient with Primary Key" << std::endl;
		std::cout << "\t5. Find Patient with Secondary Key" << std::endl;
		std::cout << "\t6. Display All Data" << std::endl;
		std::cout << "\t7. Save to file" << std::endl;
		std::cout << "\t8. Exit\n"
				  << std::endl;

		int studentOption;
		cin >> studentOption;

		if (studentOption < 1 || studentOption > 8)
		{
			std::cout << "Please choose one of the options above" << std::endl;
			continue;
		}

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
			std::cout << "Exiting..." << std::endl;
			return;
		}
	}
}

void IOManager::findDataWithPrimaryKey()
{
	std::string primaryKey;
	std::cout << "Enter the primary key: ";
	std::cin >> primaryKey;

	Patient *patient = database.primarySearch(&Patient(primaryKey, ""));
	//TODO: this should be a vector / array not a pointer

	if (patient == nullptr)
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
	std::cin >> secondaryKey;

	Patient *patient = database.secondarySearch(&Patient("", secondaryKey));

	if (patient == nullptr)
	{
		std::cout << "No patient found with that secondary key" << std::endl;
		return;
	}

	std::cout << "Patient found:" << std::endl;
	patient->toStream(&std::cout);
}

void IOManager::saveToFile()
{
	std::string fileName;
	std::cout << "Enter the file name: ";
	std::cin >> fileName;

	database.save(fileName); //todo add err handling
}