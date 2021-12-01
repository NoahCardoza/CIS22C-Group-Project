#include "IOManager.h"

int main(int argc, char *argv[])
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

	IOManager getIO = IOManager();

	if (argc > 2)
	{
		cout << "usage: " << argv[0] << " path-to-database" << endl;
		return 1;
	}
	else if (argc == 2)
	{
		if (!getIO.loadFromFile(argv[1]))
		{
			cout << "error: failed to load database \"" << argv[1] << '"' << endl;
			return 1;
		}
	}

	getIO.startMainLoop();

	return 0;
}
