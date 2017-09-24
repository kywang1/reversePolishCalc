rpn: rpn.o
	g++ -std=c++11 -o rpn rpn.o

rpn.o : rpn.cpp 
	g++ -std=c++11 -c rpn.cpp
clean : 
	rm -f rpn rpn.o
