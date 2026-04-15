#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>

#include "concepts.h"
#include "exception.h"
#include "const_iterator.h"
#include "base_iterator.h"

template <CopiableMoveableAssignable T>
class Set
{
public:

    // Aliases
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;
    using iterator = ConstIterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    using difference_type = std::ptrdiff_t;

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
    Set<T>& operator=(const Set<T>& other);
    Set<T>& assign(const Set<T>& other);

    // Move assignment from another Set
    Set<T>& operator=(Set<T>&& other) noexcept;
    Set<T>& assign(Set<T>&& other) noexcept;

    // Copy assignment from initializer list
    template <ConvertibleTo<T> U>
    Set<T>& operator=(std::initializer_list<U> ilist);
    template <ConvertibleTo<T> U>
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

    template <ConvertibleTo<T> U>
    bool add(const U& value);

    template <ConvertibleTo<T> U>
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

    template <EqualityComparable<T> U>
    ConstIterator<T> find(const U &value) const noexcept;

    // Get set info

    size_type size() const noexcept;

    bool empty() const noexcept;

    // Clear the set

    void clear() noexcept;

    // Iterators getting funcs
    ConstIterator<T> begin() const noexcept;  
    ConstIterator<T> end() const noexcept;     
    ConstIterator<T> cbegin() const noexcept;  
    ConstIterator<T> cend() const noexcept;    

    // Union funcs (make new one)
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_union(const Set<U>& other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_union(const C& container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_union(const R& range) const;

    // Union funcs (unite with this)
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
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
    template <ConvertibleTo<T> U>
    Set<T>& operator^=(const Set<U>& other);
    template <ConvertibleContainer<T> C>
    Set<T>& operator^=(const C& container);
    template <ConvertibleRange<T> R>
    Set<T>& operator^=(const R& range);

    // Comparison operators
    template <EqualityComparable<T> U>
    std::partial_ordering operator<=>(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    std::partial_ordering operator<=>(const C &container) const noexcept; 
    template <EqualityComparableRange<T> R>
    std::partial_ordering operator<=>(const R &range) const noexcept; 

    template <EqualityComparable<T> U>
    bool operator==(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool operator==(const C &container) const noexcept; 
    template <EqualityComparableRange<T> R>
    bool operator==(const R &range) const noexcept; 

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
    class SetNode : public std::enable_shared_from_this<SetNode>
    {
        private:
            T data;
            std::shared_ptr<SetNode> next;

            // Private constructors for SetNode
            explicit SetNode(const T& data) noexcept;
            explicit SetNode(T&& data) noexcept;
            SetNode(const std::shared_ptr<SetNode> current_node, const T& data) noexcept;
        public:
            // To forbid default, copy and move constructors
            SetNode() = delete;
            SetNode(const SetNode& other) = delete;
            SetNode(SetNode&& other) = delete;

            // Static factory method to create a new SetNode
            template <typename... Args>
            static std::shared_ptr<SetNode> create(Args &&... args);

            // Destructor
            ~SetNode() = default;

            // Getters
            const T& value() const noexcept;
            std::shared_ptr<T> get();
            std::shared_ptr<SetNode> getNext() const noexcept;

            // Setters
            void set(const T& value) noexcept;
            void setNull() noexcept;
            void setNext(const SetNode& node);
            void setNext(const std::shared_ptr<SetNode>& pnode) noexcept;
            void setNextNull() noexcept;

            // Operators
            bool operator==(const std::shared_ptr<SetNode>& other) const noexcept;
            bool operator!=(const std::shared_ptr<SetNode>& other) const noexcept;
    };

    // Friends
    friend class BaseIterator<T>;
    friend class ConstIterator<T>;

private:
    std::shared_ptr<SetNode> head = nullptr;
    std::shared_ptr<SetNode> tail = nullptr;

    bool add(const std::shared_ptr<SetNode> &node);
};

#include "set.hpp"
#include "set_node.hpp"