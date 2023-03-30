#include "example.h"
#include <iostream>
#include <string>

using namespace example;
using namespace flexiobjects;

int main() {
    PersonAttributes pa;
    auto name = std::string("Name");
    auto nameProp = pa.getProperty(name);
    nameProp->setValue(std::string("Abhishek"));
    std::cout << pa.getProperty(name)->getValue() << std::endl;
    return 0;
}
