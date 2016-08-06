#ifndef _TO_STRING_
#define _TO_STRING_

#include <string>
#include <sstream>
#include <iostream>

// from:
// http://forums.codeguru.com/showthread.php?231056-C-String-How-to-convert-a-numeric-type-to-a-string&s=

template <class T>
std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
{
	// the second parameter of to_string() should be one of 
	// std::hex, std::dec or std::oct
		// examples:
		// to_string<long>(123456, std::hex)
		// to_string<long>(123456, std::oct)
		// output:
		// 1e240
		// 361100
	std::ostringstream oss;
	oss << f << t;
	return oss.str();
}

#endif