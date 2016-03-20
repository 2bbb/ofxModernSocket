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


END_NAMESPACE_OFX_MODERN_OSC

std::ostream &operator<<(std::ostream &os, const ofxModernOscMessage &mess) {
    os << mess.address << " :[" << std::endl;
    for(std::size_t i = 0; i < mess.size(); i++) {
        os << "  " << i << ": " << mess[i] << std::endl;
    }
    return os << "]";
}
