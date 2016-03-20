//
//  ofxModernOscMessage.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <iostream>
#include <vector>

#include "ofxModernOscArgument.h"

namespace ofx {
    namespace ModernOsc {
        class Message {
            std::string address;
            std::vector<Argument> args;
        public:
            
        };
    };
};

using ofxModernOscMessage = ofx::ModernOsc::Message;
std::ostream &operator<<(std::ostream &os, const ofxModernOscMessage &mess);
