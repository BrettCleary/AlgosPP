#pragma once

#include <string>

namespace algospp{
template<typename KEY> class TestClass {
public:
	/*std::string simple_lib_function() {
		return "Compiled in library";
	}*/

	std::string simple_lib_function();

	template<typename KEY> KEY simpleKey(KEY k) {
		++k;
		return k;
	}

};
}
#ifndef CPPINCLUDED
#define CPPINCLUDED
#include "simple_lib.cpp"
#endif // !CPPINCLUDED



/*namespace algospp {
	class TestClass {
	public:
		std::string simple_lib_function();

	};
}*/
