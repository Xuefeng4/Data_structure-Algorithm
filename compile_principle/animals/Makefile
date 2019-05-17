dog_program : dog.o main.o
	clang++ dog.o main.o -o dog_program

main.o : 
	clang++ -c main.cpp

dog.o : 
	clang++ -c dog.cpp

clean :
	rm dog_program *.o