//
//  ofxModernOscReceiver.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include "ofxModernUDPReceiver.h"
#include "ofxModernOscMessage.h"

namespace OSCPP {
    namespace Server {
        class Packet;
    };
};

/// OSC Receiver

namespace ofx {
    namespace ModernOsc {
        class Receiver : public ofxModernUDPReceiver {
        protected:
            virtual void receive(const boost::system::error_code &error_code,
                                 std::array<char, buf_size> &buf,
                                 std::size_t len) override;
            void handle(const OSCPP::Server::Packet &packet);
        public:
            Receiver() : ofxModernUDPReceiver() {}
            using ofxModernUDPReceiver::setup;
        };
    };
};

using ofxModernOscReceiver = ofx::ModernOsc::Receiver;
