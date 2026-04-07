#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>

#include "concepts.h"

template <CopiableMoveableAssignable T>
class Set
{
public:

    // Aliases
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    // TODO: iterator + const iterator + diff

    // Constructors

    Set() = default;

    // Constructor from initializer list
    template <ConvertibleTo<T> U>
    Set(std::initializer_list<U> ilist);

    // Constructor from array (C style)
    template <ConvertibleTo<T> U>
    Set(size_type size, const U *array);

    // Copy constructor
    Set(const Set &other);

    // Move constructor
    Set(Set &&other) noexcept;

    // Constructor from container lvalue
    template <ConvertibleContainer<T> C>
    explicit Set(const C& container);

    // Constructor from container rvalue
    template <ConvertibleContainer<T> C>
    explicit Set(C&& container);

    // Constructor from range lvalue
    template <ConvertibleRange<T> R>
    explicit Set(const R& range);

    // Constructor from range rvalue
    template <ConvertibleRange<T> R>
    explicit Set(R&& range);

    // Constructors from iterator
    template <ConvertibleInputIterator<T> It, Sentinel<It> S>
    explicit Set(const It& begin, const S& end);

    // Destructor

    ~Set();

    // Assignment operators and functions

    // Copy assignment from another Set
    template <Convertible<T> U>
    Set<T>& operator=(const Set<T>& other);
    template <Convertible<T> U>
    Set<T>& assign(const Set<T>& other);

    // Move assignment from another Set
    template <Convertible<T> U>
    Set<T>& operator=(const Set<T>&& other) noexcept;
    template <Convertible<T> U>
    Set<T>& assign(const Set<T>&& other) noexcept;

    // Copy assignment from initializer list
    template <Convertible<T> U>
    Set<T>& operator=(std::initializer_list<U> ilist);
    template <Convertible<T> U>
    Set<T>& assign(std::initializer_list<U> ilist);
    
    // Copy assignment from container
    template <ConvertibleContainer<T> C>
    Set<T>& operator=(const C& container);
    template <ConvertibleContainer<T> C>
    Set<T>& assign(const C& container);

    // Move assignment from container
    template <ConvertibleContainer<T> C>
    Set<T>& operator=(C&& container);
    template <ConvertibleContainer<T> C>
    Set<T>& assign(C&& container);

    // Copy assignment from range
    template <ConvertibleRange<T> R>
    Set<T>& operator=(const R& range);
    template <ConvertibleRange<T> R>
    Set<T>& assign(const R& range);

    // Move assignment from range
    template <ConvertibleRange<T> R>
    Set<T>& operator=(R&& range);
    template <ConvertibleRange<T> R>
    Set<T>& assign(R&& range);
};
