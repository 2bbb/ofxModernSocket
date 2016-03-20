//
//  ofxModernUDPReceiver.hpp
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include "ofxModernUDPSocket.h"
#include <thread>

static constexpr std::size_t buf_size{65536};

/// UDP Receiver

class ofxModernUDPReceiver : public ofxModernUDPSocket {
    std::thread thread;
protected:
    virtual void receive(const boost::system::error_code &error_code,
                         std::array<char, buf_size> &buf,
                         std::size_t len);
public:
    ofxModernUDPReceiver() : ofxModernUDPSocket() {}
    bool setup(int port);
};