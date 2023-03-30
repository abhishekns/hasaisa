#include <flexibleObjects.hpp>
#include <string>

namespace example {

using namespace flexiobjects::properties;



class PersonAttributes : public NamedProperties <std::string, 2> {
    ::std::string NamePropertyName;
    ::std::string TitlePropertyName;
public:
    PersonAttributes();
};


}
