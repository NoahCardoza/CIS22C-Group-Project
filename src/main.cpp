#include "BinarySearchTree.h"
#include "HashTable.h"
#include "IOManager.h"
#include "Patient.h"

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
