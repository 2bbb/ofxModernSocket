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
    return os;
}
