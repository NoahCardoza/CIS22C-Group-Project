CFLAGS=-std=c++11 -Wall -Werror -Wextra

all:
	g++ src/Patient.cpp src/main.cpp  -std=c++11 -o database-cli

run:
	g++ src/Patient.cpp src/main.cpp  -std=c++11 -o database-cli && ./database-cli

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
	