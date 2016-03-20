//
//  ofxModernOscArgument.cpp
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#include "ofxModernOscArgument.h"
#include "ofLog.h"

#define BEGIN_NAMESPACE_OFX_MODERN_OSC namespace ofx {\
    namespace ModernOsc {

#define END_NAMESPACE_OFX_MODERN_OSC \
    };\
};

BEGIN_NAMESPACE_OFX_MODERN_OSC

Argument::Argument(TagType tag)
: tag(tag) {
    switch(tag) {
        case Tag::True:
            num.b = true;
            break;
        case Tag::False:
            num.b = false;
            break;
        case Tag::NIL:
        case Tag::IMPULSE:
            break;
        default:
            ofLogWarning("ofxModernOscMessage") << "invalid message: tag is " << tag << " [" << TagName(tag) << "]. but argument is not given.";
    }
}

#define cast_num(type, name) static_cast<type>(num.name)

#define define_num_cast_operator(type)\
Argument::operator type() const {\
    switch(tag) {\
        case OSCPP::Tag::True:\
        case OSCPP::Tag::False:\
            return cast_num(type, b);\
        case OSCPP::Tag::Char:   return cast_num(type, c);\
        case OSCPP::Tag::Int32:  return cast_num(type, i);\
        case OSCPP::Tag::Int64:  return cast_num(type, l);\
        case OSCPP::Tag::Float:  return cast_num(type, f);\
        case OSCPP::Tag::Double: return cast_num(type, d);\
        case OSCPP::Tag::String: return static_cast<type>(std::stol(str));\
        default:\
            ofLogWarning("ofxModernOscMessage") << ("argument is not " #type ": ") << OSCPP::TagName(tag);\
            return static_cast<type>(0);\
    }\
}

define_num_cast_operator(bool);
define_num_cast_operator(std::int8_t);
define_num_cast_operator(std::int32_t);
define_num_cast_operator(std::int64_t);
define_num_cast_operator(float);
define_num_cast_operator(double);

#undef cast_num
#undef define_num_cast_operator

Argument::operator std::string() const {
    if(tag != OSCPP::Tag::String) {
        ofLogWarning("ofxModernOscMessage") << ("argument is not string: ") << OSCPP::TagName(tag);
    }
    return stringValue();
}

END_NAMESPACE_OFX_MODERN_OSC

std::ostream &operator<<(std::ostream &os, const ofxModernOscArgument &arg) {
    return os << arg.tag << ": " << arg.stringValue();
}
