//
//  ofxModernOscReceiver.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include "ofxModernUDPReceiver.h"

namespace OSCPP {
    namespace Server {
        class Packet;
    };
};

/// OSC Receiver

class ofxModernOscReceiver : public ofxModernUDPReceiver {
    virtual void receive(const boost::system::error_code &error_code,
                         std::array<char, buf_size> &buf,
                         std::size_t len);
    void handle(const OSCPP::Server::Packet &packet);
public:
    using ofxModernUDPReceiver::setup;
};