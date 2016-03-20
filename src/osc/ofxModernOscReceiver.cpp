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
        OSCPP::Server::Message msg(packet);
        
        std::string address(msg.address());
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
        
        auto it = thread_processes.find(address);
        if(it != thread_processes.end()) for(std::size_t i = 0, num = thread_processes.count(address); i < num; ++it, i++) {
            it->second->process(mess);
        }
    }
}

void Receiver::update(ofEventArgs &) {
    leakedMessages.clear();
    ofxModernOscMessage mess;
    while(messageChannel.tryReceive(mess)) {
        std::size_t num = callbacks.count(mess.address);
        auto it = callbacks.find(mess.address);
        if(it != callbacks.end()) for(std::size_t i = 0, num = callbacks.count(mess.address); i < num; ++it, i++) {
            it->second(mess);
        } else {
            if(!thread_processes.count(mess.address)) {
                leakedMessages.push_back(std::move(mess));
            }
        }
    }
    for(auto process : thread_processes) process.second->call();
}

template <typename Prepared>
void Receiver::addThreadCallback(const std::string &bindAddress,
                       ThreadProcess<Prepared> thread_process,
                       PreparedCallback<Prepared> callback)
{
    thread_processes.insert(std::make_pair(bindAddress, makeThreadedCallback(thread_process, callback)));
}

template <typename ThreadProcess, typename Callback>
void Receiver::addThreadCallback(const std::string &bindAddress, ThreadProcess tp, Callback cb) {
    static_assert(is_argument_message<ThreadProcess>(), "argument of ThreadProcess is not ofxModernOscMessage.");
    static_assert(is_callable<ThreadProcess>::value, "ThreadProcess is not function.");
    static_assert(is_callable<Callback>::value, "Callback is not function.");
    static_assert(composable<ThreadProcess, Callback>(), "result of ThreadProcess is not argument of Callback.");
    
    addThreadCallback(bindAddress,
                      static_cast<typename function_info<ThreadProcess>::function_type>(tp),
                      static_cast<typename function_info<Callback>::function_type>(cb));
}


END_NAMESPACE_OFX_MODERN_OSC