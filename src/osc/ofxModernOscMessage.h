//
//  ofxModernOscMessage.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ofxModernOscArgument.h"

namespace ofx {
    namespace ModernOsc {
        class Message {
            std::vector<Argument> args;
        public:
            std::string address;
            template <typename ... ArgumentTypes>
            
            Message(std::string &address)
            : address(address) {}
            
            template <typename ArgumentType, typename ... ArgumentTypes>
            Message(std::string &address, ArgumentType &&argument, ArgumentTypes && ... arguments)
            : address(address) {
                addArguments(std::forward<ArgumentType>(argument), std::forward<ArgumentTypes>(arguments) ...);
            }
            
            void addArgument(TagType tag) {
                args.emplace_back(tag);
            }

            template <typename ArgumentType>
            void addArgument(TagType tag, ArgumentType &&arg) {
                args.emplace_back(tag, std::forward<ArgumentType>(arg));
            }
            
            template <typename ArgumentType, typename ... ArgumentTypes>
            void addArguments(ArgumentType &&argument, ArgumentTypes && ... arguments) {
                args.emplace_back(std::forward<ArgumentType>(argument));
                if(sizeof...(arguments)) addArguments(std::forward<ArgumentTypes>(arguments) ...);
            }
            
            template <typename ArgumentType>
            Message &operator<<(ArgumentType &&arg) {
                args.emplace_back(arg);
                return *this;
            }
            
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
