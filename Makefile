all: compile

test: compile run

compile:
	g++  Front-End.cpp File.cpp 

clean:
	del *.o

run:	
	./a.out
