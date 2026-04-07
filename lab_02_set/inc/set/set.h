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

    // Add element to the set

    template <Convertible<T> U>
    bool add(const U& value);

    template <Convertible<T> U>
    bool add(U&& value);

    // Delete element from the set

    template <EqualityComparable<T> U>
    bool erase(const U& value) noexcept;

    template <EqualityComparableInputIterator<T> It>
    bool erase(It& pos) noexcept;

    // Check if element is in the set
    template <EqualityComparable<T> U>
    bool in(const U& value) const noexcept;

    template <EqualityComparableInputIterator<T> It>
    bool in(const It& pos) const noexcept;

    // TODO: find (using const iter)

    // Get set info

    size_type size() const noexcept;

    bool empty() const noexcept;

    // Clear the set

    void clear() noexcept;

    // TODO: iters getting funcs

    // Union funcs (make new one)
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_union(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_union(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_union(const R& range) const;

    // Union funcs (unite with this)
    template <Convertible<T> U>
    Set<T>& unite(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& unite(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& unite(const R& range);

    // Intersection funcs (make new one)
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_intersection(const Set<U>& other) const;
    template <CommonContainer<T> C> 
    Set<std::common_type_t<T, typename C::value_type>> make_intersection(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_intersection(const R& range) const;

    // Intersection funcs (intersect with this)
    template <Convertible<T> U>
    Set<T>& intersect(const Set<U>& other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T>& intersect(const C& container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T>& intersect(const R& range) noexcept;

    // Difference funcs (make new one)
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_difference(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_difference(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_difference(const R& range) const;   

    // Difference funcs (subtract from this)
    template <Convertible<T> U>
    Set<T>& subtract(const Set<U>& other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T>& subtract(const C& container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T>& subtract(const R& range) noexcept;

    // Symmetric difference funcs (make new one)
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_symm_difference(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_symm_difference(const C& container) const;
    template <CommonRange<T> R> 
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_symm_difference(const R& range) const;

    // Symmetric difference funcs (symm_subtract from this)
    template <Convertible<T> U>
    Set<T>& symm_subtract(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& symm_subtract(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& symm_subtract(const R& range);

    // Union operator +
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator+(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator+(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator+(const R& range) const; 

    // Union operator +=
    template <Convertible<T> U>
    Set<T>& operator+=(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& operator+=(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& operator+=(const R& range);

    // Union operator |
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator|(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator|(const C& container) const;
    template <CommonRange<T> R>  
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator|(const R& range) const; 

    // Union operator |=
    template <Convertible<T> U>
    Set<T>& operator|=(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& operator|=(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& operator|=(const R& range);

    // Intersection operator &
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator&(const Set<U>& other) const;
    template <CommonContainer<T> C> 
    Set<std::common_type_t<T, typename C::value_type>> operator&(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator&(const R& range) const; 

    // Intersection operator &=
    template <Convertible<T> U>
    Set<T>& operator&=(const Set<U>& other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T>& operator&=(const C& container) noexcept;
    template <ConvertibleRange<T> R>    
    Set<T>& operator&=(const R& range) noexcept;

    // Difference operator -
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator-(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator-(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator-(const R& range) const; 

    // Difference operator -=
    template <Convertible<T> U>
    Set<T>& operator-=(const Set<U>& other) noexcept;   
    template <ConvertibleContainer<T> C>
    Set<T>& operator-=(const C& container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T>& operator-=(const R& range) noexcept;

    // Symmetric difference operator ^
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator^(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator^(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator^(const R& range) const; 

    // Symmetric difference operator ^=
    template <Convertible<T> U>
    Set<T>& operator^=(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& operator^=(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& operator^=(const R& range);

    // Comparable / non-comparable funcs
    template <EqualityComparable<T> U>
    bool comparable(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool comparable(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool comparable(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool nonComparable(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool nonComparable(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool nonComparable(const R &range) const noexcept;

    // Subset / superset funcs
    template <EqualityComparable<T> U>
    bool subsetOf(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool subsetOf(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool subsetOf(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool supersetOf(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool supersetOf(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool supersetOf(const R &range) const noexcept;

    // Less / lessOrEqual / greater / greaterOrEqual funcs
    template <EqualityComparable<T> U>
    bool less(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool less(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool less(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool lessOrEqual(const Set<U> &other) const noexcept;   
    template <EqualityComparableContainer<T> C>
    bool lessOrEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool lessOrEqual(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool greater(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool greater(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool greater(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool greaterOrEqual(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool greaterOrEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool greaterOrEqual(const R &range) const noexcept;

    // Equal / not equal funcs
    template <EqualityComparable<T> U>
    bool equal(const Set<U> &other) const noexcept; 
    template <EqualityComparableContainer<T> C>
    bool equal(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool equal(const R &range) const noexcept;

    template <EqualityComparable<T> U>
    bool notEqual(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool notEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool notEqual(const R &range) const noexcept;

protected:
    // TODO: node class + friends

private:
    // TODO: head + tail
};

// TODO: includes