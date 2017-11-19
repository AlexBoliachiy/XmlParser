#include "stdafx.h"
#include "CppUnitTest.h"
#include "Interval.h"
#include "XmlTools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectOneUnitTests
{		
	TEST_CLASS(TestOfInterval)
	{
	public:
		
		TEST_METHOD(CheckOnIntervals)
		{
			//strict so, output must be empty
			Interval a(3559, 3571);
			a.generatePrime();
			Assert::IsTrue(a.getPrimes().empty());
		}


		TEST_METHOD(CheckFromOneToHundred)
		{
			//strict so, output must be empty
			Interval a(1, 100);
			std::vector<int> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
			a.generatePrime();
			std::vector<int> my_primes(a.getPrimes().begin(), a.getPrimes().end());
			Assert::AreEqual(my_primes.size(), primes.size());
			for (auto i = 0; i < primes.size(); i++)
			{
				Assert::AreEqual(primes[i], my_primes[i]);
			}

		}

	};

	TEST_CLASS(TestOfMyTinyXML)
	{
	public:

		TEST_METHOD(CheckDifferentCombination)
		{
			auto inters = MyTinyXML::parse(R"(<root>
									<intervals>

									<interval>
									<low>1</low>
									<high> 100 </high>
									</interval>
									<interval>
									<low>150</low>
									<high> 200 </high>
									</interval>
									<interval>
									<low>5</low>
									<high> 10 </high>




									</interval>

									</intervals>
									</root>)");
			std::vector<Interval> right{ { 1, 100 },{ 150, 200 },{ 5, 10 } };
			Assert::AreEqual(right.size(), inters.size());
			for (auto i = 0; i < inters.size(); i++)
			{
				Assert::IsTrue(right[i] == inters[i]);
			}
		}


		TEST_METHOD(GetXmlValue)
		{
			std::string xml = "<a> 1</a>2 <b> </b> <c>3</c>";
			Assert::AreEqual(MyTinyXML::getElemValue("c", xml), std::string("3"));
		}
	};
}