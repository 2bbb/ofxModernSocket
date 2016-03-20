//
//  ofxModernOscThreadedProcessUtils.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include "../../detail/ofx_modern_socket_type_utils.h"
#include "../ofxModernOscMessage.h"

namespace ofx {
    namespace ModernOsc {
        template <typename Fn>
        constexpr bool is_argument_message() {
            return is_argument_same_to<Fn, ofxModernOscMessage>();
        };

        class AbstractThreadedCallback {
        public:
            virtual void process(ofxModernOscMessage &) = 0;
            virtual void call() = 0;
        };

        using AbstractThreadedCallbackRef = std::shared_ptr<AbstractThreadedCallback>;

        template <typename Prepared>
        using ThreadProcess = std::function<Prepared(ofxModernOscMessage &)>;
        template <typename Prepared>
        using PreparedCallback = std::function<void(Prepared &&)>;

        template <typename Prepared>
        class ThreadedCallback : public AbstractThreadedCallback {
            ofThreadChannel<Prepared> channel;
            ThreadProcess<Prepared> thread_process;
            PreparedCallback<Prepared> callback;
            
        public:
            ThreadedCallback(ThreadProcess<Prepared> thread_process,
                             PreparedCallback<Prepared> callback)
            : thread_process(thread_process)
            , callback(callback) {}
            
            virtual void process(ofxModernOscMessage &mess) {
                Prepared v(thread_process(mess));
                channel.send(std::move(v));
            }
            virtual void call() {
                Prepared v;
                while(channel.tryReceive(v)) {
                    callback(std::move(v));
                }
            }
        };

        template <typename Prepared>
        AbstractThreadedCallbackRef makeThreadedCallback(ThreadProcess<Prepared> thread_process, PreparedCallback<Prepared> callback)
        {
            return AbstractThreadedCallbackRef(new ThreadedCallback<Prepared>(thread_process, callback));
        }
    };
};