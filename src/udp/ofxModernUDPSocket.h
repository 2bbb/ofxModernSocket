//
//  ofxModernUDPSocket.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <boost/asio.hpp>
#include "./detail/macro.h"

/// UDP Base Class

class ofxModernUDPSocket {
protected:
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;
public:
    ofxModernUDPSocket()
    : socket(io_service) {}
};