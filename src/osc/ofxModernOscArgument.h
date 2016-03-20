//
//  ofxModernOscArgument.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include "ofxModernOscTag.h"
#include <string>

namespace ofx {
    namespace ModernOsc {
        struct Argument {
            union number_value {
                bool b;
                std::int8_t c;
                std::int32_t i;
                std::int64_t l;
                float f;
                double d;
            } num;
            std::string str;
            
            const TagType tag;
            
            Argument(bool b)
            : tag(b ? Tag::True : Tag::False) { num.b = b; }
            Argument(std::int8_t c)
            : tag(Tag::Char) { num.c = c; }
            
            Argument(std::uint8_t i)
            : tag(Tag::Int32) { num.i = i; }
            Argument(std::int16_t i)
            : tag(Tag::Int32) { num.i = i; }
            Argument(std::uint16_t i)
            : tag(Tag::Int32) { num.i = i; }
            Argument(std::int32_t i)
            : tag(Tag::Int32) { num.i = i; }

            Argument(std::uint32_t l)
            : tag(Tag::Int64) { num.l = l; }
            Argument(std::int64_t l)
            : tag(Tag::Int64) { num.l = l; }
            Argument(std::uint64_t l)
            : tag(Tag::Int64) { num.l = l; }
            
            Argument(float f)
            : tag(Tag::Float) { num.f = f; }
            Argument(double d)
            : tag(Tag::Double) { num.d = d; }

            Argument(const std::string &str)
            : tag(Tag::String), str(str) {}
            
            Argument(TagType tag);
            Argument(TagType tag, std::int8_t c)
            : tag(tag) { num.c = c; }
            Argument(TagType tag, std::int32_t i)
            : tag(tag) { num.i = i; }
            Argument(TagType tag, std::int64_t l)
            : tag(tag) { num.l = l; }
            Argument(TagType tag, float f)
            : tag(tag) { num.f = f; }
            Argument(TagType tag, double d)
            : tag(tag) { num.d = d; }
            Argument(TagType tag, const std::string &str)
            : tag(tag), str(str) {}
            
            inline std::string stringValue() const {
                switch(tag) {
                    case OSCPP::Tag::String: return str;
                    case OSCPP::Tag::True:   return std::string("True");
                    case OSCPP::Tag::False:  return std::string("False");
                    case OSCPP::Tag::Char:   return std::to_string(num.c);
                    case OSCPP::Tag::Int32:  return std::to_string(num.i);
                    case OSCPP::Tag::Int64:  return std::to_string(num.l);
                    case OSCPP::Tag::Float:  return std::to_string(num.f);
                    case OSCPP::Tag::Double: return std::to_string(num.d);
                    default:                 return TagName(tag);
                }
            }
            
            operator bool() const;
            operator std::int8_t() const;
            operator std::int32_t() const;
            operator std::int64_t() const;
            operator float() const;
            operator double() const;
            operator std::string() const;
            
            template <typename type>
            type get() const {
                return operator type();
            }
        };
    };
};

using ofxModernOscArgument = ofx::ModernOsc::Argument;
std::ostream &operator<<(std::ostream &os, const ofxModernOscArgument &arg);
