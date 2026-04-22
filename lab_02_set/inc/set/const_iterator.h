#pragma once

#include "base_iterator.h"
#include "concepts.h"

#include <iterator>
#include <memory>

template <CopiableMoveableAssignable T>
class Set;

template <CopiableMoveableAssignable T>
class ConstIterator : public BaseIterator<T>
{    
    static_assert(EqualityComparable<T, T>, "T must be equality comparable with itself");

public:
    using pointer = const T*;
    using reference = const T&;
    using value_type = T;
    using iterator_category = std::forward_iterator_tag; // for list
    using difference_type = std::ptrdiff_t;

    // Constructors
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<typename Set<T>::SetNode> &pnode) noexcept;
    ConstIterator(const ConstIterator<T> &other);

    // Destructor
    ~ConstIterator() override = default;

    // Change iterator
    void next() noexcept;

    // Check iterator
    explicit operator bool() const noexcept;
    void checkExpired() const;

    // Operators
    bool operator==(const ConstIterator<T> &other) const noexcept;
    bool operator!=(const ConstIterator<T> &other) const noexcept;

    ConstIterator<T> &operator=(const ConstIterator<T> &other) noexcept;
    ConstIterator<T> &operator=(ConstIterator<T> &&other) noexcept;

    reference operator*() const;
    pointer operator->() const;

    ConstIterator<T> operator+(difference_type n) const noexcept;
    ConstIterator<T> &operator++() noexcept;
    ConstIterator<T> operator++(int) noexcept;

private:
    // Getters
    typename Set<T>::SetNode &getCurr() const;
};

#include "const_iterator.hpp"
