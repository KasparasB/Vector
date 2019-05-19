make:
	g++ -c Vector.cpp
	g++ -std=c++11 Vector.o -o Test
	./Test
valymas:
rm *.o Test 
