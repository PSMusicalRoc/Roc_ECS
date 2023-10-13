#ifndef _ROC_COMPONENT_H_
#define _ROC_COMPONENT_H_

#include <cstdint>
#include <bitset>

#include <any>
#include <map>
#include <functional>

#include <cassert>

#include <boost/preprocessor.hpp>

// z, data, elem
#define PRINT_TO_SETTER(z, data, elem) BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(0, elem),\
/*noraw*/ void BOOST_PP_CAT(__set_, BOOST_PP_TUPLE_ELEM(3, elem))(Property p)\
{BOOST_PP_TUPLE_ELEM(3, elem) = std::any_cast<BOOST_PP_TUPLE_ELEM(2, elem)>(p); }, \
/*rawinput*/ )

#define PRINT_TO_COPYSTATEMENT(z, data, elem) BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(0, elem),\
/*noraw*/ BOOST_PP_TUPLE_ELEM(3, elem) = cpy.BOOST_PP_TUPLE_ELEM(3, elem);, \
/*rawinput*/ )

#define PRINT_TO_PROPERTY_PT1(z, data, elem) BOOST_PP_IF(  BOOST_PP_TUPLE_ELEM( 0 , elem ),\
/*notraw  */ BOOST_PP_IF(  BOOST_PP_EQUAL(  BOOST_PP_TUPLE_SIZE( elem ), 5  ),\
/*true*/ (BOOST_PP_TUPLE_ELEM(1, elem): BOOST_PP_TUPLE_ELEM(2, elem) BOOST_PP_TUPLE_ELEM(3, elem) = BOOST_PP_TUPLE_ELEM(4, elem);),\
/*false*/ (BOOST_PP_TUPLE_ELEM(1, elem): BOOST_PP_TUPLE_ELEM(2, elem) BOOST_PP_TUPLE_ELEM(3, elem);)),\
/*rawinput*/ BOOST_PP_TUPLE_ELEM(1, elem)\
)

#define PRINT_TO_PROPERTY(z, data, elem) BOOST_PP_EXPAND(BOOST_PP_TUPLE_REM()PRINT_TO_PROPERTY_PT1(z, data, elem))

#define LAMBDA(elem) _setters[BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, elem))] = [=](Property p){\
BOOST_PP_CAT(__set_, BOOST_PP_TUPLE_ELEM(3, elem))(p); };

#define PRINT_TO_LAMBDA(z, data, elem) BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(0, elem),\
/*notraw  */ LAMBDA(elem), \
/*rawinput*/ )

#define ROCKET_PROPERTY(qualifier, type, name) (1, qualifier, type, name)
#define ROCKET_PROPERTY_DEFVAL(qualifier, type, name, defval) (1, qualifier, type, name, defval)

// Random things in macro expansion to make tuple size > 3... screw off boost_pp :(
#define ROCKET_RAW(...) (0, (__VA_ARGS__), 1, 2)

#define ROCKET_COMPONENT(cname, ...) class cname : public Component {\
public: \
static std::string name() { return #cname; }\
BOOST_PP_SEQ_FOR_EACH(PRINT_TO_SETTER, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
BOOST_PP_SEQ_FOR_EACH(PRINT_TO_PROPERTY, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
\
public: cname() {\
    BOOST_PP_SEQ_FOR_EACH(PRINT_TO_LAMBDA, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
}\
\
public: cname(const cname & cpy) {\
    BOOST_PP_SEQ_FOR_EACH(PRINT_TO_COPYSTATEMENT, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
    BOOST_PP_SEQ_FOR_EACH(PRINT_TO_LAMBDA, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
} \
\
public: cname & operator=(const cname & cpy) {\
    BOOST_PP_SEQ_FOR_EACH(PRINT_TO_COPYSTATEMENT, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
    BOOST_PP_SEQ_FOR_EACH(PRINT_TO_LAMBDA, _, BOOST_PP_VARIADIC_SEQ_TO_SEQ(__VA_ARGS__)) \
    return *this;\
}\
}

using Property = std::any;

using ComponentType = std::uint16_t;

const ComponentType MAX_COMPONENTS = 64;

using Signature = std::bitset<MAX_COMPONENTS>;

#include "RocLogger/RocLogger.hpp"

/**
 * A quick base class, just so that any components
 * created all implement certain Constructors and have
 * a public "isNull" boolean.
*/
class Component
{
private:
    bool mIsNull;

public:
    std::map<std::string, std::function<void(Property)>> _setters;
    Component(bool null = false) {mIsNull = null;}
    bool isNull() {return mIsNull;}

    virtual void DestroyComponent() {}
};

#endif