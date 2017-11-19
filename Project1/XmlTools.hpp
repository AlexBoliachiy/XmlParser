#pragma once

#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>

#include "Interval.h"
#include "parse_exception.h"

namespace MyTinyXML
{

	std::string getElemValue(const std::string &xmlNodeName, const std::string &xml)
	{
		// No exceptions possible, just precaution
		std::string openTag = "<" + xmlNodeName + ">";
		std::string endTag = "</" + xmlNodeName + ">";

		int pos_start = xml.find(openTag);
		if (pos_start == std::string::npos)
			throw parse_exception("No tag with such name");
		int pos_end = xml.find(endTag);
		if (pos_end == std::string::npos)
			throw parse_exception("No end tag with such name");

		return xml.substr(pos_start + openTag.length(), pos_end -  pos_start - openTag.length());


	}


	std::vector<Interval> parse(const std::string &xml)
	{


		/*Defines basic structure of xml document from root to interval*/
		std::string low_high_rule = 
			R"((\s*(<low>\s*\d+\s*<\/low>\s*<high>\s*\d+\s*<\/high>)|(<high>\s*\d+\s*<\/high>\s*<low>\s*\d+\s*<\/low>)\s*))";

		/*Defines basic structure of content interval element. Allow only one low and high element for each interval element*/
		std::string general_dom_rule =
			std::string(R"(^\s*<root>\s*(<intervals>\s*(\s*<interval>\s*)") 
			+ 
			low_high_rule 
			+ 
			std::string(R"(\s*<\/interval>\s*)*\s*<\/intervals>)\s*<\/root>\s*$)");
		

		std::regex low_high_regex { low_high_rule };
		std::regex general_dom_regex { general_dom_rule };
		if (std::regex_match(xml, general_dom_regex))
		{
			// std::cout << "it's all ok" << std::endl;
		}
		else
		{
			throw parse_exception("Invalid DOM of incoming XML");
		}
		

		std::smatch m;
		std::vector<std::string> all_intervals;
		std::string str = xml;
		while (std::regex_search(str, m, low_high_regex))
		{
			all_intervals.push_back(m[0]);
			str = m.suffix();
		}
		std::vector<Interval> intervals;
		for (auto x : all_intervals)
		{
			int high = std::stoi(getElemValue("high", x));
			int low = std::stoi(getElemValue("low", x));
			if (low > high)
			{
				throw parse_exception("Low more than high ");
			}
			intervals.push_back(Interval(low, high));
		}
		return intervals;
	}


	std::vector<Interval> parseFile(const std::string &fileName)
	{
		std::ifstream xml_file(fileName);
		if (!xml_file.is_open())
			throw parse_exception("No such input file");
		std::stringstream sstream;
		sstream << xml_file.rdbuf();
		std::string xml_string = sstream.str();
		
		return parse(xml_string);
	}

}
