#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Patient.h"

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
		void display();

		/**
		 * starts the main loop which displays the menu and collects the users input, then calls the appropriate function to handle the rest
		 */
		void startMainLoop();

		/**
		 * creates a new IO manager object with the hashtable DB and the BST DB
		 */
		IOManager(HashTable<Patient>&, BinarySearchTree<Patient>&);

	private:
		/**
		 * hashtable DB to store the patients
		 */
		HashTable<Patient> hashtableDB;

		/**
		 * BST DB to store the patients.
		 */
		BinarySearchTree<Patient> bstDB;

		/**
		 * stack used for the undoDelete() method.
		 * whenever a patient is deleted, it will be pushed onto this stack.
		 * Whenever the user saves everything to a file, this stack gets refreshed.
		 */
		std::stack<Patient> deletedStack;

};