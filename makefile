proj5: hgupta20Proj5.o proj5Tokens.o
	g++ -o proj5 hgupta20Proj5.o proj5Tokens.o 

hgupta20Proj5.o: hgupta20Proj5.cpp proj5Tokens.h proj5Array.h
	g++ -c hgupta20Proj5.cpp 

proj5Tokens.o: proj5Tokens.cpp proj5Tokens.h
	g++ -c proj5Tokens.cpp

clean:
	rm proj5 hgupta20Proj5.o proj5Tokens.o
