//
//  tag.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

#include <string>

// cite: https://github.com/openframeworks/openFrameworks/blob/0.9.3/addons/ofxOsc/src/ofxOscMessage.h#L70-L87
/*
	OSC 1.1 specifications types:
 i - 32bit integer
 h - 64bit integer
 f - 32bit floating point number
 d - 64bit (double) floating point number
 s - string
 S - symbol
 c - char
 m - 4 byte midi packet (8 digits hexadecimal)
 T - TRUE (no value required)
 F - FALSE (no value required)
 N - NIL (no value required)
 I - IMPULSE, act as a trigger (no value required), previously named INFINITUM
 t - TIMETAG, an OSC timetag in NTP format, encoded in the data section
	See : http://cnmat.berkeley.edu/system/files/attachments/Nime09OSCfinal.pdf
	*/

namespace OSCPP {
#define TagCase(Name) case Tag::Name: return #Name;
    namespace Tag {
        static constexpr char Int32 = 'i';
        static constexpr char Int64 = 'h';
        static constexpr char Float = 'f';
        static constexpr char Double = 'd';
        static constexpr char String = 's';
        static constexpr char Symbol = 'S';
        static constexpr char Char = 'c';
        static constexpr char Midi4 = 'm';
        static constexpr char True = 'T';
        static constexpr char False = 'F';
        static constexpr char NIL = 'N';
        static constexpr char IMPULSE = 'I';
        static constexpr char Timetag = 't';
    };
    using TagType = char;
    static std::string TagName(TagType tag) {
        switch(tag) {
                TagCase(Int32);
                TagCase(Int64);
                TagCase(Float);
                TagCase(Double);
                TagCase(String);
                TagCase(Symbol);
                TagCase(Char);
                TagCase(Midi4);
                TagCase(True);
                TagCase(False);
                TagCase(NIL);
                TagCase(IMPULSE);
                TagCase(Timetag);
            default: return "unknown tag";
        }
    }
#undef TagCase
};
