#include "BinarySearchTree.h"
#include "HashTable.h"
#include "IOManager.h"
#include "Patient.h"

int main(void)
{
	HashTable<Patient> table;
	BinarySearchTree<Patient> bst;
	IOManager getIO = IOManager(table, bst);

	getIO.startMainLoop();
  	return 0;
}