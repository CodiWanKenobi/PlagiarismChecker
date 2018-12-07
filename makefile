# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary. 

plagiarismCatcher: plagiarismCatcher_Driver.o
	g++ -oplagiarismCatcher  plagiarismCatcher_Driver.o
	rm plagiarismCatcher_Driver.o
	clear
plagiarismCatcher_Driver.o: plagiarismCatcher_Driver.cpp HashTable.h
	g++ -std=c++0x -c plagiarismCatcher_Driver.cpp