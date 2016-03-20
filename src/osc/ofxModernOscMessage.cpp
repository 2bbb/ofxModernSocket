//
//  ofxModernOscMessage.cpp
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#include "ofxModernOscMessage.h"
#include "ofLog.h"

#define BEGIN_NAMESPACE_OFX_MODERN_OSC namespace ofx {\
    namespace ModernOsc {

#define END_NAMESPACE_OFX_MODERN_OSC\
    };\
};

BEGIN_NAMESPACE_OFX_MODERN_OSC

#define cast_num(type, name) static_cast<type>(num.name)

#define define_num_cast_operator(type)\
Argument::operator type() const {\
    switch(tag) {\
        case OSCPP::Tag::Char:   return cast_num(type, c);\
        case OSCPP::Tag::Int32:  return cast_num(type, i);\
        case OSCPP::Tag::Int64:  return cast_num(type, l);\
        case OSCPP::Tag::Float:  return cast_num(type, f);\
        case OSCPP::Tag::Double: return cast_num(type, d);\
        case OSCPP::Tag::String: return static_cast<type>(std::stol(str));\
        default:\
            ofLogError("ofxModernOscMessage") << ("argument is not " #type ": ") << OSCPP::TagName(tag);\
            return static_cast<type>(0);\
    }\
}

define_num_cast_operator(std::int8_t);
define_num_cast_operator(std::int32_t);
define_num_cast_operator(std::int64_t);
define_num_cast_operator(float);
define_num_cast_operator(double);

#undef cast_num
END_NAMESPACE_OFX_MODERN_OSC
