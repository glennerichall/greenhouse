//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_TRAITS_H
#define GREENHOUSE_TRAITS_H

// --- Custom type traits (STL-free) ---

// true_type and false_type
struct true_type  { enum { value = 1 }; };
struct false_type { enum { value = 0 }; };

// is_same
template<typename T, typename U>
struct is_same { enum { value = 0 }; };

template<typename T>
struct is_same<T, T> { enum { value = 1 }; };

// enable_if
template<bool cond, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<1, T> { typedef T type; };

// --- Check if type T exists in Ts...

template<typename T, typename... Ts>
struct contains;

template<typename T>
struct contains<T> : false_type {};

template<typename T, typename U, typename... Ts>
struct contains<T, U, Ts...> {
    enum { value = is_same<T, U>::value || contains<T, Ts...>::value };
};

// --- Ensure all types are unique

template<typename...>
struct are_unique { enum { value = 1 }; };

template<typename T, typename... Ts>
struct are_unique<T, Ts...> {
    enum { value = !contains<T, Ts...>::value && are_unique<Ts...>::value };
};


#endif //GREENHOUSE_TRAITS_H
