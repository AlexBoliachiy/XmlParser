#pragma once
#include <exception>
#include <string>

class parse_exception :
	public std::exception
{
	std::string m;
public:
	const char * what() const noexcept;

	parse_exception(const char* m);
	~parse_exception();
};

