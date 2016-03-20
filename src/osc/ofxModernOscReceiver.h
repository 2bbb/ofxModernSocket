//
//  ofxModernOscReceiver.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <unordered_map>
#include <queue>

#include "ofxModernUDPReceiver.h"
#include "ofxModernOscMessage.h"

#include "ofThreadChannel.h"
#include "ofEvent.h"
#include "ofEvents.h"

namespace OSCPP {
    namespace Server {
        class Packet;
    };
};

/// OSC Receiver

namespace ofx {
    namespace ModernOsc {
        using Callback = std::function<void(ofxModernOscMessage &mess)>;
        
        class Receiver : public ofxModernUDPReceiver {
            ofThreadChannel<ofxModernOscMessage> messageChannel;
            std::queue<ofxModernOscMessage> queues;
        protected:
            virtual void receive(const boost::system::error_code &error_code,
                                 std::array<char, buf_size> &buf,
                                 std::size_t len) override;
            void handle(const OSCPP::Server::Packet &packet);
            std::unordered_multimap<std::string, Callback> callbacks;
            void update(ofEventArgs &) {
                decltype(queues) empty_queue;
                queues.swap(empty_queue);
                ofxModernOscMessage mess;
                while(messageChannel.tryReceive(mess)) {
                    std::size_t num = callbacks.count(mess.address);
                    auto it = callbacks.find(mess.address);
                    if(it != callbacks.end()) for(std::size_t i = 0, num = callbacks.count(mess.address); i < num; it++, i++) {
                        it->second(mess);
                    } else {
                        queues.push(std::move(mess));
                    }
                }
            }
        public:
            Receiver() : ofxModernUDPReceiver() {
                ofAddListener(ofEvents().update, this, &Receiver::update, OF_EVENT_ORDER_BEFORE_APP);
            }
            virtual ~Receiver() {
                ofRemoveListener(ofEvents().update, this, &Receiver::update);
            }
            
            using ofxModernUDPReceiver::setup;
            
            void addCallback(const std::string &bindAddress, Callback callback) {
                callbacks.insert(std::make_pair(bindAddress, callback));
            }
        };
    };
};

using ofxModernOscReceiver = ofx::ModernOsc::Receiver;
