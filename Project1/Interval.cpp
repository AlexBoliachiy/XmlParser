#include "Interval.h"

std::recursive_mutex Interval::lock;
std::set<int> Interval::primes;


Interval::Interval(int low, int high) : low(low), high(high)
{
}

const std::set<int>& Interval::getPrimes()
{
	return primes;
}



bool Interval::generatePrimes()
{
	
	for (int i = low + 1; i < high; i++) //not strict
	{
		bool flag = false;
		for (int j = 2; j <= i - 1; j++)
		{
			if (i % j == 0)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			addPrime(i);
		}
	}
	return true;
}

const bool Interval::operator==(const Interval & other)
{
	if (low == other.low && high == other.high)
		return true;
	return false;
}

bool Interval::isInPrimes(int number)
{
	std::lock_guard<std::recursive_mutex> guard(lock);
	if (Interval::primes.find(number) == primes.end())
		return false;
	return true;
}

void Interval::addPrime(int number)
{
	std::lock_guard<std::recursive_mutex> guard(lock);
	if (!isInPrimes(number))
		Interval::primes.insert(number);
}


Interval::~Interval()
{
}
