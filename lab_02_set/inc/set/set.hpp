#pragma once

#include "set.h"
#include <ranges>
#include <algorithm>

// Constructors
template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>::Set(std::initializer_list<U> ilist) : Set()
{
    std::for_each(ilist.begin(), ilist.end(), [this](const U& el){ this->add(el); });
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>::Set(size_type size, const U *array) : Set()
{
    std::for_each(array, array + size, [this](const U&el){ this->add(el); });
}

template <CopiableMoveableAssignable T>
Set<T>::Set(const Set &other) : Set()
{
    std::for_each(other.begin(), other.end(), [this](const T& el){ this->add(el); });
}

template <CopiableMoveableAssignable T>
Set<T>::Set(Set &&other) noexcept
{
    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);
    other._size = 0;
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(const C& container)
{
    static_assert(ConvertibleContainer<C, T>, 
                  "Container elements must be convertible to Set value_type");
    std::for_each(container.begin(), container.end(), [this](const T& value){ this->add(value); });
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(C&& container)
{
    static_assert(ConvertibleContainer<C, T>, 
                  "Container elements must be convertible to Set value_type");
    std::for_each(container.begin(), container.end(), [this](const T& value){ this->add(std::move(value)); });
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(const R& range)
{
    std::for_each(range.begin(), range.end(), [this](const T& value){ this->add(value); });
}   

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(R&& range)
{
    std::for_each(range.begin(), range.end(), [this](const T& value){ this->add(std::move(value)); });
}   

template <CopiableMoveableAssignable T>
template <ConvertibleInputIterator<T> It, Sentinel<It> S>
Set<T>::Set(const It& begin, const S& end)
{
    std::for_each(begin, end, [this](const T& value){ this->add(value); });
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>::Set(const Set<U>& other) : Set()
{
    std::for_each(other.begin(), other.end(), [this](const U& el){ this->add(el); });
}

// Destructor
template <CopiableMoveableAssignable T>
Set<T>::~Set() noexcept
{
    this->clear();
}

// Assignment operators and functions
template <CopiableMoveableAssignable T>
Set<T>& Set<T>::assign(const Set<T>& other)
{
    if (this == &other)
        return *this;

    this->clear();
    std::for_each(other.begin(), other.end(), [this](const T& el){ this->add(el); });

    return *this;
}

template <CopiableMoveableAssignable T>
Set<T>& Set<T>::operator=(const Set<T>& other)
{
    return this->assign(other);
}

template <CopiableMoveableAssignable T>
Set<T>& Set<T>::assign(Set<T>&& other) noexcept
{
    if (this == &other)
        return *this;

    this->clear();
    this->size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);
    other._size = 0;

    return *this;
}

template <CopiableMoveableAssignable T>
Set<T>& Set<T>::operator=(Set<T>&& other) noexcept
{    
    return this->assign(std::move(other));
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>& Set<T>::assign(std::initializer_list<U> ilist)
{
    this->clear();
    std::for_each(ilist.begin(), ilist.end(), [this](const T& el){ this->add(el); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>& Set<T>::operator=(std::initializer_list<U> ilist)
{    
    return this->assign(ilist);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>& Set<T>::assign(const C& container)
{
    this->clear();
    std::for_each(container.begin(), container.end(), [this](const T& el){ this->add(el); });
    return *this;
}   

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>        
Set<T>& Set<T>::operator=(const C& container)
{
    return this->assign(container);
}   

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>& Set<T>::assign(C&& container)
{
    this->clear();
    std::for_each(container.begin(), container.end(), [this](const T& el){ this->add(std::move(el)); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>& Set<T>::operator=(C&& container)
{    
    return this->assign(std::move(container));
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>& Set<T>::assign(const R& range)
{
    this->clear();
    std::for_each(range.begin(), range.end(), [this](const T& el){ this->add(el); });
    return *this;      
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>& Set<T>::operator=(const R& range)
{    
    return this->assign(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>& Set<T>::assign(R&& range)
{
    this->clear();
    std::for_each(range.begin(), range.end(), [this](const T& el){ this->add(std::move(el)); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>& Set<T>::operator=(R&& range)
{
    return this->assign(std::move(range));
}

// Add element to the set

template <CopiableMoveableAssignable T>
bool Set<T>::add(const std::shared_ptr<typename Set<T>::SetNode>& node)
{
    if (this->in(node->value()))
        return false;

    if (this->empty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        this->tail->setNext(node);
        this->tail = node;
    }
    this->_size++;

    return true;
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
bool Set<T>::add(const U& value)
{
    if (this->in(value))
        return false;
    std::shared_ptr<typename Set<T>::SetNode> newNode;
    try
    {
        newNode = Set<T>::SetNode::create(value);
    }
    catch(const std::bad_alloc& e)
    {
        throw MemoryException("Failed to allocate memory for new node.");
    }
    return add(newNode);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
bool Set<T>::add(U&& value)
{
    if (this->in(value))
        return false;
    std::shared_ptr<typename Set<T>::SetNode> newNode;
    try
    {
        newNode = Set<T>::SetNode::create(std::move(value));
    }
    catch(const std::bad_alloc& e)
    {
        throw MemoryException("Failed to allocate memory for new node.");
    }
    return add(newNode);
}

// Delete element from the set

template <CopiableMoveableAssignable T>
template <EqualityComparableInputIterator<T> It>
bool Set<T>::erase(It& pos) noexcept
{
    if (this->head == this->tail)
    {
        this->clear();
        return true;
    }

    if (pos == this->cend())
        return false;

    auto it_copy = pos + 1;
    auto temp = this->head;

    if (pos == this->cbegin())
    {
        this->head = this->head->getNext();
        temp.reset();
    }
    else
    {
        auto current_node = pos.curr.lock();
        while (temp && temp->getNext())
        {
            if (temp->getNext() == current_node)
            {
                temp->setNext(current_node->getNext());
                temp.reset();
                break;
            }
            temp = temp->getNext();
        }
    }
    pos = it_copy;
    --this->_size;

    return true;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::erase(const U& value) noexcept
{
    
    ConstIterator<T> it = this->find(value);
    if (it == this->cend())
        return false;

    this->erase(it);
    return true;
}

// Check if element is in the set
template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::in(const U& value) const noexcept
{
    return this->find(value) != this->cend();
}

template <CopiableMoveableAssignable T>
template <EqualityComparableInputIterator<T> It>
bool Set<T>::in(const It& pos) const noexcept
{
    return this->in(*pos);
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
ConstIterator<T> Set<T>::find(const U& value) const noexcept
{
    auto it = std::find(this->cbegin(), this->cend(), value);
    return it != this->cend() ? it : ConstIterator<T>();
}

// Get set info
template <CopiableMoveableAssignable T>
bool Set<T>::empty() const noexcept
{
    return this->_size == 0;
}   

template <CopiableMoveableAssignable T>
typename Set<T>::size_type Set<T>::size() const noexcept
{
    return this->_size;
}

// Clear the set
template <CopiableMoveableAssignable T>
void Set<T>::clear() noexcept
{
    while (this->head)
    {
        auto temp = this->head;
        this->head = this->head->getNext();
        temp->setNextNull();
        temp.reset();
    }

    this->tail.reset();
    this->_size = 0;
}

// Iterators
template <CopiableMoveableAssignable T>
ConstIterator<T> Set<T>::cbegin() const noexcept
{
    return ConstIterator<T>(this->head);
}

template <CopiableMoveableAssignable T>
ConstIterator<T> Set<T>::cend() const noexcept
{
    return this->tail ? ConstIterator<T>(this->tail->getNext()) : ConstIterator<T>();
}

template <CopiableMoveableAssignable T>
ConstIterator<T> Set<T>::begin() const noexcept
{
    return this->cbegin();
}

template <CopiableMoveableAssignable T>
ConstIterator<T> Set<T>::end() const noexcept
{
    return this->cend();
}

// Union funcs
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_union(const Set<U>& other) const
{   
    Set<std::common_type_t<T, U>> set_union(*this);
    set_union.unite(other);
    return set_union;
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> C>
Set<T>& Set<T>::unite(const Set<C>& other)
{
    std::for_each(other.begin(), other.end(), [this](const C& el){ this->add(el); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_union(const C& container) const
{
    Set<std::common_type_t<T, typename C::value_type>> set_union(*this);
    set_union.unite(container);
    return set_union;
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T>& Set<T>::unite(const C& container)
{    
    std::for_each(container.begin(), container.end(), [this](const T& el){ this->add(el); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_union(const R& range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> set_union(*this);
    set_union.unite(range);
    return set_union;
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T>& Set<T>::unite(const R& range)
{
    std::for_each(range.begin(), range.end(), [this](const T& el){ this->add(el); });
    return *this;
}   

// Intersection funcs
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_intersection(const Set<U>& other) const
{
    Set<std::common_type_t<T, U>> set_intersection;
    auto filtered = *this | std::views::filter([&other](const T& el){ return other.in(el); });
    std::for_each(filtered.begin(), filtered.end(), [&set_intersection](const auto& el){ set_intersection.add(el); });
    return set_intersection;
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T>& Set<T>::intersect(const Set<U>& other) noexcept
{
    // impossible to do it with std::ranges::remove_if, because operation is mutating
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (!other.in(*it))
            this->erase(it);
        else
            ++it;
    }
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_intersection(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> copy;
    auto filtered = *this
                  | std::views::filter([&](const auto &el)
                                       { return std::ranges::find(container, el) != container.cend(); });
    std::for_each(filtered.begin(), filtered.end(), [&](const auto &el) { copy.add(el); });

    return copy;
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::intersect(const C &container) noexcept
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (std::ranges::find(container, *it) == container.cend())
            this->erase(it);
        else
            ++it;
    }

    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_intersection(
    const R &range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> copy;
    auto filtered =
        *this
        | std::views::filter([&](const auto &el) { return std::ranges::find(range, el) != range.cend(); });
    std::for_each(filtered.begin(), filtered.end(), [&](const auto &el) { copy.add(el); });

    return copy;
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::intersect(const R &range) noexcept
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (std::ranges::find(range, *it) == range.cend())
            this->erase(it);
        else
            ++it;
    }

    return *this;
}

// Difference funcs
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_difference(const Set<U> &other) const
{
    Set<std::common_type_t<T, U>> copy(*this);
    std::for_each(other.begin(), other.end(), [&](const U &el) { copy.erase(el); });

    return copy;
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::subtract(const Set<U> &other) noexcept
{    
    std::for_each(other.begin(), other.end(), [this](const U &el) { this->erase(el); });
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_difference(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> copy(*this);
    std::for_each(container.begin(), container.end(), [&](const auto &el) { copy.erase(el); });

    return copy;
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::subtract(const C &container) noexcept
{
    std::for_each(container.begin(), container.end(), [this](const auto &el) { this->erase(el); });

    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_difference(
    const R &range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> copy(*this);
    std::for_each(range.begin(), range.end(), [&](const auto &el) { copy.erase(el); });

    return copy;
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::subtract(const R &range) noexcept
{
    std::for_each(range.begin(), range.end(), [this](const auto &el) { this->erase(el); });

    return *this;
}

// Symmetric difference funcs
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_symm_difference(const Set<U> &other) const
{
    return *this + other - (*this & other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::symm_subtract(const Set<U> &other)
{
    Set<T> intersection = *this & other;
    *this += other;
    *this -= intersection;
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_symm_difference(const C &container) const
{
    return *this + container - (*this & container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::symm_subtract(const C &container)
{
    Set<T> intersection = *this & container;
    *this += container;
    *this -= intersection;
    return *this;
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_symm_difference(
    const R &range) const
{
    return *this + range - (*this & range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::symm_subtract(const R &range)
{
    Set<T> intersection = *this & range;
    *this += range;
    *this -= intersection;
    return *this;
}

// Union operators
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator|(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator|(const C &container) const
{
    return this->make_union(container);
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator|(const R &range) const
{
    return this->make_union(range);
}

template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator+(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator+(const C &container) const
{
    return this->make_union(container);
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator+(const R &range) const
{
    return this->make_union(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::operator|=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator|=(const C &container)
{
    return this->unite(container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator|=(const R &range)
{
    return this->unite(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::operator+=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator+=(const C &container)
{
    return this->unite(container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator+=(const R &range)
{
    return this->unite(range);
}

// Intersection operators
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator&(const Set<U> &other) const
{
    return this->make_intersection(other);
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator&(const C &container) const
{
    return this->make_intersection(container);
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator&(const R &range) const
{
    return this->make_intersection(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::operator&=(const Set<U> &other) noexcept
{
    return this->intersect(other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator&=(const C &container) noexcept
{
    return this->intersect(container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator&=(const R &range) noexcept
{
    return this->intersect(range);
}

// Difference operators
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator-(const Set<U> &other) const
{
    return this->make_difference(other);
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator-(const C &container) const
{
    return this->make_difference(container);
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator-(const R &range) const
{
    return this->make_difference(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::operator-=(const Set<U> &other) noexcept
{
    return this->subtract(other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator-=(const C &container) noexcept
{
    return this->subtract(container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator-=(const R &range) noexcept
{
    return this->subtract(range);
}

// Symmetric difference operators
template <CopiableMoveableAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator^(const Set<U> &other) const
{
    return this->make_symm_difference(other);
}

template <CopiableMoveableAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator^(const C &container) const
{
    return this->make_symm_difference(container);
}

template <CopiableMoveableAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator^(const R &range) const
{
    return this->make_symm_difference(range);
}

template <CopiableMoveableAssignable T>
template <ConvertibleTo<T> U>
Set<T> &Set<T>::operator^=(const Set<U> &other)
{
    return this->symm_subtract(other);
}

template <CopiableMoveableAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator^=(const C &container)
{
    return this->symm_subtract(container);
}

template <CopiableMoveableAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator^=(const R &range)
{
    return this->symm_subtract(range);
}

// Comparison operators
template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
std::partial_ordering Set<T>::operator<=>(const Set<U> &other) const noexcept
{
    if (this->equal(other))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(other))
        return std::partial_ordering::less;

    if (this->supersetOf(other))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
std::partial_ordering Set<T>::operator<=>(const C &container) const noexcept
{
    if (this->equal(container))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(container))
        return std::partial_ordering::less;

    if (this->supersetOf(container))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
std::partial_ordering Set<T>::operator<=>(const R &range) const noexcept
{
    if (this->equal(range))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(range))
        return std::partial_ordering::less;

    if (this->supersetOf(range))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator==(const Set<U> &other) const noexcept
{
    return this->equal(other);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::operator==(const C &container) const noexcept
{
    return this->equal(container);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::operator==(const R &range) const noexcept
{
    return this->equal(range);
}

// Comparison funs
template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::comparable(const Set<U> &other) const noexcept
{
    return (*this <=> other) != std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::comparable(const C &container) const noexcept
{
    return (*this <=> container) != std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::comparable(const R &range) const noexcept
{
    return (*this <=> range) != std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::nonComparable(const Set<U> &other) const noexcept
{
    return (*this <=> other) == std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::nonComparable(const C &container) const noexcept
{
    return (*this <=> container) == std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::nonComparable(const R &range) const noexcept
{
    return (*this <=> range) == std::partial_ordering::unordered;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::subsetOf(const Set<U> &other) const noexcept
{
    return std::all_of(this->cbegin(), this->cend(), [&](const T &el) { return other.in(el); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::subsetOf(const C &container) const noexcept
{
    return std::all_of(this->cbegin(), this->cend(), [&](const T &el) { return std::ranges::find(container, el) != container.cend(); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::subsetOf(const R &range) const noexcept
{
    return std::all_of(this->cbegin(), this->cend(), [&](const T &el) { return std::ranges::find(range, el) != range.cend(); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::supersetOf(const Set<U> &other) const noexcept
{
    return other.subsetOf(*this);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::supersetOf(const C &container) const noexcept
{
    return std::all_of(container.begin(), container.end(), [this](const T &el) { return this->in(el); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::supersetOf(const R &range) const noexcept
{
    return std::all_of(range.begin(), range.end(), [this](const T &el) { return this->in(el); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::equal(const Set<U> &other) const noexcept
{
    if (this->_size != other._size)
        return false;

    return this->subsetOf(other) && other.subsetOf(*this);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::equal(const C &container) const noexcept
{
    return this->subsetOf(container)
        && std::all_of(container.begin(), container.end(), [this](const T &el) { return this->in(el); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::equal(const R &range) const noexcept
{
    return this->subsetOf(range)
        && std::all_of(range.begin(), range.end(), [this](const T &el) { return this->in(el); });
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::notEqual(const Set<U> &other) const noexcept
{
    return !this->equal(other);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::notEqual(const C &container) const noexcept
{
    return !this->equal(container);
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::notEqual(const R &range) const noexcept
{
    return !this->equal(range);
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::less(const Set<U> &other) const noexcept
{
    return *this < other;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::less(const C &container) const noexcept
{
    return *this < container;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::less(const R &range) const noexcept
{
    return *this < range;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::lessOrEqual(const Set<U> &other) const noexcept
{
    return *this <= other;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::lessOrEqual(const C &container) const noexcept
{
    return *this <= container;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::lessOrEqual(const R &range) const noexcept
{
    return *this <= range;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greater(const Set<U> &other) const noexcept
{
    return *this > other;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::greater(const C &container) const noexcept
{
    return *this > container;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::greater(const R &range) const noexcept
{
    return *this > range;
}

template <CopiableMoveableAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greaterOrEqual(const Set<U> &other) const noexcept
{
    return *this >= other;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::greaterOrEqual(const C &container) const noexcept
{
    return *this >= container;
}

template <CopiableMoveableAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::greaterOrEqual(const R &range) const noexcept
{
    return *this >= range;
}

// Output 
template <typename T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set)
{
    os << "{";

    std::for_each(set.begin(), set.end(), [&](const T &el) { os << el << ", "; });

    os << "}";
    os << " (" << set.size() << ")";

    return os;
}