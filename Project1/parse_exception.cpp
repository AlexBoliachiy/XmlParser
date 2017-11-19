#include "parse_exception.h"



const char * parse_exception::what() const noexcept
{
	return m.c_str();
}

parse_exception::parse_exception(const char* m) : m(m)
{

}


parse_exception::~parse_exception()
{
}
