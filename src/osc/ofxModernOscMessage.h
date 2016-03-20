//
//  ofxModernOscMessage.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <vector>
#include <string>

#include <oscpp/detail/tag.h>

namespace ofx {
    namespace ModernOsc {
        struct Argument {
            union number_value {
                std::int8_t c;
                std::int32_t i;
                std::int64_t l;
                float f;
                double d;
            } num;
            std::string str;
            
            const OSCPP::TagType tag;
            
            Argument(OSCPP::TagType tag);
            Argument(OSCPP::TagType tag, std::int8_t c)
            : tag(tag) { num.c = c; }
            Argument(OSCPP::TagType tag, std::int32_t i)
            : tag(tag) { num.i = i; }
            Argument(OSCPP::TagType tag, std::int64_t l)
            : tag(tag) { num.l = l; }
            Argument(OSCPP::TagType tag, float f)
            : tag(tag) { num.f = f; }
            Argument(OSCPP::TagType tag, double d)
            : tag(tag) { num.d = d; }
            
            operator std::int8_t() const;
            operator std::int32_t() const;
            operator std::int64_t() const;
            operator float() const;
            operator double() const;
        };

        class Message {
            std::string address;
            std::vector<Argument> args;
        public:
            
        };
    };
};

using ofxModernOscArgument = ofx::ModernOsc::Argument;
using ofxModernOscMessage = ofx::ModernOsc::Message;