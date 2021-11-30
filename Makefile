CFLAGS=-std=c++11 -Wall -Werror -Wextra

unit:
	@cd tests/unit &&\
	g++ -o BinarySearchTree.test BinarySearchTree.test.cpp ../../src/Patient.cpp $(CFLAGS) &&\
	g++ -o HashTable.test HashTable.test.cpp ../../src/Patient.cpp $(CFLAGS) &&\
	g++ -o PatientDatabase.test PatientDatabase.test.cpp ../../src/Patient.cpp $(CFLAGS) &&\
	./BinarySearchTree.test &&\
	./HashTable.test &&\
	./PatientDatabase.test &&\
	diff --text pd.test.csv pd.test.csv.diff 

clean:
	@cd tests/unit && rm -f *.test pd.test.csv
	