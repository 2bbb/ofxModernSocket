//
//  ofxModernOscReceiver.cpp
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#include "ofxModernOscReceiver.h"
#include <oscpp/server.hpp>

#include <iostream>
#include <oscpp/print.hpp>

#define BEGIN_NAMESPACE_OFX_MODERN_OSC namespace ofx {\
    namespace ModernOsc {

#define END_NAMESPACE_OFX_MODERN_OSC\
    };\
};

BEGIN_NAMESPACE_OFX_MODERN_OSC

void Receiver::receive(const boost::system::error_code &error_code,
                                   std::array<char, buf_size> &buf,
                                   std::size_t len)
{
    handle(OSCPP::Server::Packet(buf.data(), len));
}

void Receiver::handle(const OSCPP::Server::Packet &packet) {
    if (packet.isBundle()) {
        // Convert to bundle
        OSCPP::Server::Bundle bundle(packet);
        // Get packet stream
        OSCPP::Server::PacketStream packets(bundle.packets());
        
        while(!packets.atEnd()) {
            handle(packets.next());
        }
    } else {
        // Convert to message
        OSCPP::Server::Message msg(packet);
        std::string address(msg.address());
        // Get argument stream
        OSCPP::Server::ArgStream args(msg.args());
        
        std::cout << address << std::endl;
        while(!args.atEnd()) {
            auto tag = args.tag();
            std::cout << tag << ": ";
            switch(tag) {
                case 's':
                    std::cout << args.string();
                    break;
                case 'b':
                    std::cout << "[blob]";
                    break;
                default:
                    std::cout << args.float32();
                    break;
            }
            std::cout << std::endl;
        }
    }
}

END_NAMESPACE_OFX_MODERN_OSC