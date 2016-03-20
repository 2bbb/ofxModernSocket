//
//  macro.h
//  ofxModernSocket
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#ifndef __has_feature
#   define __has_feature(x) 0
#endif

#ifndef __has_extension
#   define __has_extension __has_feature
#endif

#ifndef __has_cpp_attribute
#   define __has_cpp_attribute(x) 0
#endif

#if __has_cpp_attribute(clang::fallthrough)
#   define FALLTHROUGH [[clang::fallthrough]]
#else
#   define FALLTHROUGH
#endif

#ifndef __has_attribute
#   define __has_attribute(x) 0
#endif

#if __has_cpp_attribute(nodiscard)
#   define NO_DISCARD [[ nodiscard ]]
#else
#   define NO_DISCARD
#endif