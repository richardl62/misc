// threading-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

int main()
{
	auto start = std::chrono::steady_clock::now();
	std::cout << "Hello World\n";
	auto end = std::chrono::steady_clock::now();
	std::cout << "Printing took "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< "us.\n";
	return 0;
}

