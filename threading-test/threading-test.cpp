#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <vector>
#include <atomic>


double do_test(size_t n_threads)
{
	std::atomic<size_t> number = 0;
	size_t loop_count = 100000000;
	auto thread_func =[=,&number]()
	{
		double s = 1.0;
		double local = 0;
		for (size_t i = 0; i < loop_count; i++)
		{
			local = sqrt(local/2+1);
		}
		number += size_t(local);
	};

	std::vector<std::thread> threads(n_threads);

	auto start = std::chrono::steady_clock::now();

	for (auto &t : threads)
	{
		t = std::thread(thread_func);
	}

	for (auto &t : threads)
	{
		t.join();
	}

	auto end = std::chrono::steady_clock::now();

	double secs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1e6;
	
	std::cout << "n_threads=" << n_threads << " number=" << number << 
		": " << secs << " secs\n";

	return secs;
}

int main()
{
	double test_time = 0;
	auto start = std::chrono::steady_clock::now();
	for (size_t nt = 1; nt <= 8; ++nt)
	{
		test_time += do_test(nt);
	}
	auto end = std::chrono::steady_clock::now();

	auto secs = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "test time = " << test_time << " total time=" << secs.count() << "\n";
}
