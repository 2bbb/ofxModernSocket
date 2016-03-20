//
//  ofxModernOscReceiver.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <type_traits>

#include "ofThreadChannel.h"
#include "ofEvent.h"
#include "ofEvents.h"

#include "ofxModernUDPReceiver.h"
#include "ofxModernOscMessage.h"

#include "../detail/ofx_modern_socket_type_utils.h"
#include "./detail/ofxModernOscThreadedProcessUtils.h"

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
            std::vector<ofxModernOscMessage> leakedMessages;
            std::unordered_multimap<std::string, Callback> callbacks;
            std::unordered_multimap<std::string, AbstractThreadedCallbackRef> thread_processes;
            
            virtual void receive(const boost::system::error_code &error_code,
                                 std::array<char, buf_size> &buf,
                                 std::size_t len) override;
            void handle(const OSCPP::Server::Packet &packet);
            void update(ofEventArgs &);
            
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
            
            using iterator = std::vector<ofxModernOscMessage>::iterator;
            using const_iterator = std::vector<ofxModernOscMessage>::const_iterator;
            
            iterator begin() { return leakedMessages.begin(); }
            iterator end() { return leakedMessages.end(); }
            const_iterator begin() const { return leakedMessages.cbegin(); }
            const_iterator end() const { return leakedMessages.cend(); }
            const_iterator cbegin() const { return leakedMessages.cbegin(); }
            const_iterator cend() const { return leakedMessages.cend(); }
            
            template <typename Prepared>
            void addThreadCallback(const std::string &bindAddress,
                                   ThreadProcess<Prepared> thread_process,
                                   PreparedCallback<Prepared> callback)
            {
                thread_processes.insert(std::make_pair(bindAddress, makeThreadedCallback(thread_process, callback)));
            }
            
            template <typename ThreadProcess, typename Callback>
            void addThreadCallback(const std::string &bindAddress, ThreadProcess tp, Callback cb) {
                static_assert(is_argument_message<ThreadProcess>(), "argument of ThreadProcess is not ofxModernOscMessage.");
                static_assert(is_callable<ThreadProcess>::value, "ThreadProcess is not function.");
                static_assert(is_callable<Callback>::value, "Callback is not function.");
                static_assert(composable<ThreadProcess, Callback>(), "result of ThreadProcess is not argument of Callback.");
                
                addThreadCallback(bindAddress,
                                  static_cast<typename function_info<ThreadProcess>::function_type>(tp),
                                  static_cast<typename function_info<Callback>::function_type>(cb));
            }
        };
    };
};

using ofxModernOscReceiver = ofx::ModernOsc::Receiver;
