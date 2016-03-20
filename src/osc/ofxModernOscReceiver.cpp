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
        
        ofxModernOscMessage mess(address);
        
        while(!args.atEnd()) {
            TagType tag = args.tag();
            switch(tag) {
                case OSCPP::Tag::True:
                case OSCPP::Tag::False:
                case OSCPP::Tag::IMPULSE:
                case OSCPP::Tag::NIL:
                    mess.addArgument(tag);
                    break;
                case OSCPP::Tag::Char:
                    mess.addArgument(tag, args.int8());
                    break;
                case OSCPP::Tag::Int32:
                    mess.addArgument(tag, args.int32());
                    break;
                case OSCPP::Tag::Int64:
                    mess.addArgument(tag, args.int64());
                    break;
                case OSCPP::Tag::Float:
                    mess.addArgument(tag, args.float32());
                    break;
                case OSCPP::Tag::Double:
                    mess.addArgument(tag, args.float64());
                    break;
                case OSCPP::Tag::String:
                    mess.addArgument(tag, args.string());
                    break;
                default:
                    break;
            }
        }
        messageChannel.send(std::move(mess));
    }
}

END_NAMESPACE_OFX_MODERN_OSC