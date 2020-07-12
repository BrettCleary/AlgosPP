#include <string>
#include "simple_lib.h"

namespace algospp {
    template<typename KEY> std::string TestClass<KEY>::simple_lib_function() {
        return "Compiled in library";
    }
}

/*namespace algospp {
    std::string TestClass::simple_lib_function() {
        return "Compiled in library";
    }
}*/
