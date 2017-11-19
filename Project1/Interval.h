#pragma once

#include <set>
#include <mutex>
#include <atomic>
#include <future>
#include <memory>

class Interval
{
private:
	int low;
	int high;
	static std::set<int> primes;
	static std::recursive_mutex lock;

	bool isInPrimes(int number);
	void addPrime(int number);

public:
	Interval(int low, int high);
	static const std::set<int>& getPrimes();
	bool generatePrimes();
	const bool operator==(const Interval& other);
	
	~Interval();
};

