#include "example.h"

namespace example {

PersonAttributes::PersonAttributes() :
    NamedProperties(),
    NamePropertyName("Name"),
    TitlePropertyName("Title")
    {
        TRACE_FUNC_START
        addProperty(NamePropertyName);
        addProperty(TitlePropertyName);
        TRACE_FUNC_END
    }

}
