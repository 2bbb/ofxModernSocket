//
//  ofxModernUDPReceiver.cpp
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#include "ofxModernUDPReceiver.h"

#include <iostream>
#include <functional>
#include <array>

#include "ofLog.h"

using boost::asio::ip::udp;

ofxModernUDPReceiver::~ofxModernUDPReceiver() {
    socket.close();
}

void ofxModernUDPReceiver::receive(const boost::system::error_code &error_code,
                                        std::array<char, buf_size> &buf,
                                        std::size_t len) {
    std::cout.write(buf.data(), len);
}

NO_DISCARD bool ofxModernUDPReceiver::setup(int port) {
    try {
        socket = udp::socket(io_service, udp::endpoint(udp::v4(), port));
    } catch(std::exception &e) {
        ofLogError("ofxModernUDPReceiver") << e.what();
        return false;
    }
    
    thread = std::thread([=]() {
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        std::array<char, buf_size> recv_buf;
        std::size_t len = 0;
        while(this->socket.is_open()) {
            try {
                len = this->socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);
                if(error) {
                    ofLogError("ofxModernUDPReceiver") << error.message();
                } else {
                    this->receive(error, recv_buf, len);
                }
            } catch(exception &e) {
                ofLogError("ofxModernUDPReceiver") << e.what();
            }
        }
    });
    
    thread.detach();
    return true;
}
