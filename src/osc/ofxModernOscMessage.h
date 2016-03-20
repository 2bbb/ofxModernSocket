//
//  ofxModernOscMessage.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <iostream>
#include <vector>

#include "ofxModernOscArgument.h"

namespace ofx {
    namespace ModernOsc {
        class Message {
            std::vector<Argument> args;
        public:
            const std::string address;
            
            inline std::size_t size() const {
                return args.size();
            }
            inline Argument operator[](std::size_t index) {
                return args[index];
            }
            inline const Argument &operator[](std::size_t index) const {
                return args[index];
            }
            
            using iterator = std::vector<Argument>::iterator;
            using const_iterator = std::vector<Argument>::const_iterator;
            
            iterator begin() { return args.begin(); }
            iterator end() { return args.end(); }
            const_iterator begin() const { return args.cbegin(); }
            const_iterator end() const { return args.cend(); }
            const_iterator cbegin() const { return args.cbegin(); }
            const_iterator cend() const { return args.cend(); }
            
            using reverse_iterator = std::vector<Argument>::reverse_iterator;
            using const_reverse_iterator = std::vector<Argument>::const_reverse_iterator;
            
            reverse_iterator rbegin() { return args.rbegin(); }
            reverse_iterator rend() { return args.rend(); }
            const_reverse_iterator rbegin() const { return args.crbegin(); }
            const_reverse_iterator rend() const { return args.crend(); }
            const_reverse_iterator crbegin() const { return args.crbegin(); }
            const_reverse_iterator crend() const { return args.crend(); }
        };
    };
};

using ofxModernOscMessage = ofx::ModernOsc::Message;
std::ostream &operator<<(std::ostream &os, const ofxModernOscMessage &mess);
