#include "XmlTools.hpp"
#include <cstdio>
int launch_In_thread(std::vector<Interval>& intervals)
{
	
	std::vector<std::thread> threads;
	for (auto &x : intervals)
	{
		threads.push_back(std::thread(&Interval::generatePrimes, x));
	}

	for (auto &x : threads)
	{
		x.join();
	}

	return 0;
}

struct A
{
	int a;
	void foo() {};
};

int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		std::cout << "USAGE: project1.exe input_xml output_xml" << std::endl;
		return 1;
	}

	std::vector<Interval> intervals;
	try
	{
		intervals = MyTinyXML::parseFile(argv[1]);
	}

	catch (parse_exception& e)
	{
		std::cout << e.what();
	}

	launch_In_thread(intervals);
	std::ofstream output("output.xml", std::ios::trunc);
	output << "<root>\r\n<primes>";

	for (auto& x : Interval::getPrimes())
	{
		output << x << " ";
	}
	output << "</primes>\r\n</root>\r\n";
	return 0;
}