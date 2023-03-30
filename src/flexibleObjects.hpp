#include <vector>
#include <cstdarg>
#include <map>
#include <iostream>
#include "logging.hpp"

namespace flexiobjects {
namespace properties {

using namespace logging;

template<typename TPropertyType>
struct iProperty {
    virtual ~iProperty() {}
    typedef TPropertyType PropertyType;
    typedef TPropertyType* PropertyTypePtr;
    virtual PropertyType* get() = 0 ;
    virtual void set(PropertyType* value) = 0 ;
    virtual PropertyType getValue() = 0 ;
    virtual void setValue(PropertyType value) = 0 ;

};

template<typename TPropertyType>
struct tPropertyImpl : public iProperty<TPropertyType> {

    typedef TPropertyType PropertyType;
    typedef TPropertyType* PropertyTypePtr;

    tPropertyImpl() : propertyPtr(new PropertyType()) {
        TRACE_FUNC_START
        TRACE_FUNC_END
    }

    ~tPropertyImpl() {
        TRACE_FUNC_START
        delete propertyPtr;
        TRACE_FUNC_END
    }

    virtual PropertyType* get() { return propertyPtr; }
    virtual void set(PropertyType* value) { propertyPtr = value; }

    virtual PropertyType getValue() { return *propertyPtr; }
    virtual void setValue(PropertyType value) { *propertyPtr = value; }

    protected:
        typename iProperty<TPropertyType>::PropertyTypePtr propertyPtr;
};

namespace traits {
    template<typename T>
    struct bind {};

#define DECLARE_BIND_TYPE(_type) \
    template<> \
    struct bind<_type> { \
        typedef tPropertyImpl<_type> PropertyImpl; \
    }; \

DECLARE_BIND_TYPE(char)
DECLARE_BIND_TYPE(unsigned char)
DECLARE_BIND_TYPE(short)
DECLARE_BIND_TYPE(unsigned short)
DECLARE_BIND_TYPE(int)
DECLARE_BIND_TYPE(unsigned int)
DECLARE_BIND_TYPE(long)
DECLARE_BIND_TYPE(unsigned long)
DECLARE_BIND_TYPE(float)
DECLARE_BIND_TYPE(double)

DECLARE_BIND_TYPE(std::string)

}

template<typename ...TPropertyTypes>
struct iPropertyContainer {
    static constexpr size_t NumberOfProperties = sizeof...(TPropertyTypes);
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
struct iSimilarPropertyContainer {
    static constexpr size_t NumberOfProperties = TNumOfProperties;
    typedef TPropertyImpl PropertyImpl;
    typedef typename TPropertyImpl::PropertyType PropertyType;
    typedef iProperty<TCommonPropertyType> Property;

    virtual void addProperty(Property* property) = 0;
    virtual Property* get(size_t index) = 0;
    virtual void set(size_t index, Property* property) = 0;
    virtual PropertyType getValue(size_t index) = 0;
    virtual void setValue(size_t index, PropertyType value) = 0;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
struct tSimilarPropertyContainerImpl : public iSimilarPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl> {
    typedef typename iSimilarPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property Property;
    static constexpr size_t numProperties = TNumOfProperties;
    typedef typename TPropertyImpl::PropertyType PropertyType;

    tSimilarPropertyContainerImpl() {
        TRACE_FUNC_START
        TRACE_FUNC_END
    }

    virtual void addProperty(Property* property) { this->properties.push_back(property); }
    virtual Property* get(size_t index) { return properties[index]; }
    virtual void set(size_t index, Property* property) { properties[index] = property; }
    virtual PropertyType getValue(size_t index) { return properties[index]->getValue(); }
    virtual void setValue(size_t index, PropertyType value) { properties[index]->setValue(value); }

    protected:
        std::vector<Property*> properties;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
struct NamedPropertyContainer : public tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl> {

    typedef tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl> Base;
    typedef typename tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property Property;
    typedef typename TPropertyImpl::PropertyType PropertyType;

    NamedPropertyContainer();

    void addProperty(std::string& propertyName) {
        TRACE_FUNC_START
        propertyNames.push_back(propertyName);
        auto empty = new TPropertyImpl();
        Base::addProperty(empty);
        TRACE_FUNC_END
    }

    Property* getProperty(std::string& propertyName) {
        TRACE_FUNC_START
        auto idx = getIndexOf(propertyName);
        if (idx >= 0 && idx < this->properties.size()) {
            TRACE_FUNC_END
            return this->properties[idx];
        }
        // should we add new property or just throw exception?
        // for now throwing excpetion.
        throw new std::exception();
        TRACE_FUNC_END
    }

    protected:
        size_t getIndexOf(std::string& name) {
            for(size_t index = 0; index < propertyNames.size(); index++) {
                if(propertyNames[index] == name) {
                    return index;
                }
            }
            return -1;
        }
        std::vector<std::string> propertyNames;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::NamedPropertyContainer() {
    TRACE_FUNC_START
    TRACE_FUNC_END
}


template<typename TPropertyContainer>
struct ValidatedPropertyContainer : public TPropertyContainer {
    protected:
        std::map<std::string, void*> validators;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename PropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
class NamedProperties: public NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, PropertyImpl> {
public:
    NamedProperties() {
        TRACE_FUNC_START
        TRACE_FUNC_END
    }
};

}
}
