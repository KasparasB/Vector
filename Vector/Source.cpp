#include <iostream>
#include <vector>
#include "Vector.h"
#include <chrono>
#include <string>
#include <iomanip>

using std::vector;
using std::cout;
using std::endl;
using std::string;

struct Stopwatch {
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<float> duration;

	void Start();
	void End(string operation);
};

void Stopwatch::Start() {
	start = std::chrono::high_resolution_clock::now();
}

void Stopwatch::End(string action) {
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	cout << action << std::fixed << std::setprecision(7) << duration.count() << "s" << endl;
}


int main()
{
	Stopwatch a, b;

	unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
	
	/*
	a.Start();
	std::vector<int> v1;
	for (int i = 1; i <= sz; ++i)
		v1.push_back(i);
	a.End("std::vector 10 000 " );
	*/
	b.Start();
	Vector<int> v2;
	
	for (int i = 1; i <= sz; ++i)
		v2.push_back(i);
	b.End("Vector 10 000 ");

	int bbz = 10;


}