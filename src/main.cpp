/**
 * @author Noah Cardoza
 * Section: 1
 * 
 * The main.cpp file starts the whole project. Here we collect any
 * arguments sent to the program and either preload a database, or
 * continue with an empty database.
 * 
 * We abstracts most of the screen related logic to the IOManager.h file.
 */

#include "IOManager.h"

/**
 * @author Noah Cardoza
 * 
 * Accepts one argument: a path to a database to open.
 * 
 * Passes the user interface handling to getIO::startMainLoop.
 */
int main(int argc, char *argv[])
{
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
