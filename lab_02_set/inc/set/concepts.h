#pragma once

#include <concepts>
#include <type_traits>
#include <ranges>

template <typename T>
concept Assignable = requires(T& lv, T& rv) { lv = rv; };

template <typename T>
concept CopiableMoveableAssignable = std::copy_constructible<T> && std::move_constructible<T> && Assignable<T>;

template <typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

template <CopiableMoveableAssignable T>
class Set;

template <typename C>
concept isSet = requires {
    typename std::remove_cvref_t<C>::value_type;
} && std::same_as<Set<typename std::remove_cvref_t<C>::value_type>, std::remove_cvref_t<C>>;

template <typename C>
concept Container = 
    std::copy_constructible<C> && std::move_constructible<C> && std::destructible<C> && requires(C c) {
        typename std::remove_reference_t<C>::value_type;
        typename std::remove_reference_t<C>::reference;
        typename std::remove_reference_t<C>::const_reference;
        typename std::remove_reference_t<C>::size_type;
        typename std::remove_reference_t<C>::const_iterator;
        typename std::remove_reference_t<C>::difference_type;
        
        { c.cbegin() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;
        { c.cend() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;
        { c.size() } noexcept -> std::same_as<typename std::remove_reference_t<C>::size_type>;
        { c.empty() } noexcept -> std::same_as<bool>; 
    };

template <typename C, typename T>
concept ConvertibleContainer =
    !isSet<C> && Container<C> && ConvertibleTo<typename std::remove_reference_t<C>::value_type, T>;

template <typename R>
concept Range = std::ranges::input_range<R>;

template <typename R, typename T>
concept ConvertibleRange =
    !isSet<R> && Range<R> && ConvertibleTo<std::ranges::range_value_t<R>, T>;

template <typename It>
concept InputIterator = std::input_iterator<It>;

template <typename It, typename T>
concept ConvertibleInputIterator = InputIterator<It> && ConvertibleTo<typename It::value_type, T>;

template <typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;