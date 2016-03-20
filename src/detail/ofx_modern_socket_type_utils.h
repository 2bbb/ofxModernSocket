//
//  type_utils.h
//
//  Created by ISHII 2bit on 2016/03/20.
//
//

#pragma once

namespace ofx {
    namespace ModernOsc {
        namespace {
            template <typename T>
            using get_type = typename T::type;
            
            template <typename T>
            struct is_callable {
                template <typename U, decltype(&U::operator()) = &U::operator()>
                struct checker {};
                template <typename U> static std::true_type  test(checker<U> *);
                template <typename>   static std::false_type test(...);
                static constexpr bool value = decltype(test<T>(nullptr))::value;
            };
            
            template <typename R, typename ... Arguments>
            struct is_callable<R(*)(Arguments ...)> {
                static constexpr bool value = true;
            };
            
            template <typename R, typename ... Arguments>
            struct is_callable<R(*&)(Arguments ...)> {
                static constexpr bool value = true;
            };
            
            template <typename R, typename ... Arguments>
            struct is_callable<R(&)(Arguments ...)> {
                static constexpr bool value = true;
            };
            
            template <typename R, typename ... Arguments>
            struct is_callable<R(Arguments ...)> {
                static constexpr bool value = true;
            };
            
            template <typename R, typename ... Arguments>
            struct is_callable<std::function<R(Arguments ...)>> {
                static constexpr bool value = true;
            };
            
            template <typename T>
            struct function_info : public function_info<decltype(&T::operator())>  {};
            
            template <typename U, typename ret, typename ... arguments>
            struct function_info<ret(U::*)(arguments ...) const> {
                static constexpr bool is_function = true;
                static constexpr std::size_t arity = sizeof...(arguments);
                using result_type = ret;
                using arguments_types_tuple = std::tuple<arguments ...>;
                template <std::size_t index>
                using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
                using function_type = std::function<result_type(arguments ...)>;
            };
            
            template <typename U, typename ret, typename ... arguments>
            struct function_info<ret(U::*)(arguments ...)> {
                static constexpr bool is_function = true;
                static constexpr std::size_t arity = sizeof...(arguments);
                using result_type = ret;
                using arguments_types_tuple = std::tuple<arguments ...>;
                template <std::size_t index>
                using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
                using function_type = std::function<result_type(arguments ...)>;
            };
            
            template <typename ret, typename ... arguments>
            struct function_info<ret(*)(arguments ...)> {
                static constexpr bool is_function = true;
                static constexpr std::size_t arity = sizeof...(arguments);
                using result_type = ret;
                using arguments_types_tuple = std::tuple<arguments ...>;
                template <std::size_t index>
                using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
                using function_type = std::function<result_type(arguments ...)>;
            };
            
            template <typename ret, typename ... arguments>
            struct function_info<ret(arguments ...)> {
                static constexpr bool is_function = true;
                static constexpr std::size_t arity = sizeof...(arguments);
                using result_type = ret;
                using arguments_types_tuple = std::tuple<arguments ...>;
                template <std::size_t index>
                using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
                using function_type = std::function<result_type(arguments ...)>;
            };
            
            template <typename T>
            function_info<T> get_function_info(T &); // for decltype
            
            template <typename Fn, typename Type>
            constexpr bool is_argument_same_to() {
                return std::is_same<
                    typename std::remove_reference<typename function_info<Fn>::template argument_type<0>>::type,
                    Type
                >::value;
            }
            
            // A : ofxModernOscMessage -> T, B : T -> void
            template <typename A, typename B>
            constexpr bool composable() {
                return std::is_same<
                typename function_info<A>::result_type,
                typename std::remove_reference<typename function_info<B>::template argument_type<0>>::type
                >::value;
            }
        };
    };
};